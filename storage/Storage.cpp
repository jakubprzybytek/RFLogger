#include "Storage.hpp"

template <class Archive>
void ReadSignature::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & sdrDevice & bandwidth & sampleRate & frequency & fftWindow;
}

template <class Archive>
void Timestamped::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & ms & samples;
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

void Storage::collect(Timestamped timestampedSamples) {
	waitingQueue.push_back(timestampedSamples);

	if (waitingQueue.size() >= 4) {
		archive();
	}
}

Storage& operator<< (Storage& storage, Timestamped timestampedSamples) {
	storage.collect(timestampedSamples);
	return storage;
}
