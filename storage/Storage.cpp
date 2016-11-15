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
	ar & readSignature & timestampedSamples;
}

void Storage::setReadSignature(string sdrDevice, double bandwidth, double sampleRate, double frequency, unsigned int fftWindow) {
	readSignature = ReadSignature(sdrDevice, bandwidth, sampleRate, frequency, fftWindow);
}

void Storage::archive(Timestamped timestampedSamples) {
	ofstream ofs(fileNamePrefix + "Samples.bin");
	binary_oarchive archive(ofs);

	SamplesCollection samplesCollection(readSignature, timestampedSamples);

	archive << samplesCollection;
}

Storage& operator << (Storage& storage, Timestamped timestampedSamples) {
	storage.archive(timestampedSamples);
	return storage;
}
