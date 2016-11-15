#include "Storage.hpp"

template <class Archive>
void ReadSignature::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & sdrDevice & bandwidth & sampleRate & frequency & fftWindow;
}

template <class Archive>
void SamplesCollection::serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & readSignature & samples;
}

void Storage::setReadSignature(string sdrDevice, double bandwidth, double sampleRate, double frequency, unsigned int fftWindow) {
	readSignature = ReadSignature(sdrDevice, bandwidth, sampleRate, frequency, fftWindow);
}

void Storage::archive(Samples samples) {
	ofstream ofs(fileNamePrefix + "Samples.bin");
	binary_oarchive archive(ofs);

	SamplesCollection samplesCollection(readSignature, samples);

	archive << samplesCollection;
}

Storage& operator << (Storage& storage, Samples& samples) {
	storage.archive(samples);
	return storage;
}
