#include "Storage.hpp"

namespace boost {
	namespace serialization {
	
		template <class Archive>
		void serialize (Archive & ar, Timestamped& t, __attribute__((unused))  const unsigned int version) {
			ar & t.ms & t.samples;
		}
	}
}

template <class Archive>
void ReadSignature::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & sdrDevice & bandwidth & sampleRate & frequency & fftWindow;
}

template <class Archive>
void SamplesCollection::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & readSignature & timestampedSamplesList;
}

Storage::~Storage() {
	if (!waitingQueue.empty()) {
		archive();
	}
}
	
void Storage::setReadSignature(string sdrDevice, double bandwidth, double sampleRate, double frequency, unsigned int fftWindow) {
	readSignature = ReadSignature(sdrDevice, bandwidth, sampleRate, frequency, fftWindow);
}

void Storage::archive() {

	cout << "Archiving " << waitingQueue.size() << endl;

	SamplesCollection samplesCollection(readSignature, waitingQueue);

	unsigned long long ms = waitingQueue.front().ms;

	ofstream ofs(fileNamePrefix + to_string(ms) + ".bin");
	binary_oarchive archive(ofs);
	archive << samplesCollection;

	waitingQueue.clear();
}

void Storage::restore(SamplesCollection& samplesCollection) {

	string fileName = fileNamePrefix + "7" + ".bin";

	cout << "Restoring from: " << fileName << endl;
	ifstream ifs(fileName);
	binary_iarchive archive(ifs);
	archive >> samplesCollection;
}

void Storage::collect(Timestamped timestampedSamples) {
	waitingQueue.push_back(timestampedSamples);

	if (waitingQueue.size() >= 100) {
		archive();
	}
}

Storage& operator<< (Storage& storage, Timestamped timestampedSamples) {
	storage.collect(timestampedSamples);
	return storage;
}

Storage& operator>> (Storage& storage, SamplesCollection& samplesCollection) {
	storage.restore(samplesCollection);
	return storage;
}
