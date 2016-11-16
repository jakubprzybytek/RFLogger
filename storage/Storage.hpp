#include <list>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/complex.hpp>

#include "../sdr/SDR.hpp"

using namespace std;
using namespace boost::archive;

class ReadSignature {

private:
	string sdrDevice;
	double bandwidth;
	double sampleRate;
	double frequency;
	unsigned int fftWindow;

public:
	ReadSignature(ReadSignature&) = default;
	ReadSignature()
		: sdrDevice(""), bandwidth(0.0), sampleRate(0.0), frequency(0.0), fftWindow(0) {}
	ReadSignature(string sdrDevice, double bandwidth, double sampleRate, double frequency, unsigned int fftWindow)
		: sdrDevice(sdrDevice), bandwidth(bandwidth), sampleRate(sampleRate), frequency(frequency), fftWindow(fftWindow) {}

	template <class Archive>
	void serialize (Archive&, const unsigned int);
};

class Timestamped {

public:
	unsigned long long ms;
	Samples samples;

	Timestamped(unsigned long long ms, Samples samples) : ms(ms), samples(samples) {}

	template <class Archive>
	void serialize(Archive&, const unsigned int);
};

class SamplesCollection {

private:
	ReadSignature readSignature;
	list<Timestamped> timestampedSamplesList;

public:
	SamplesCollection(ReadSignature readSignature, list<Timestamped> timestampedSamplesList)
		: readSignature(readSignature), timestampedSamplesList(timestampedSamplesList) {}

	template <class Archive>
	void serialize(Archive&, const unsigned int);
};

class Storage {

private:
	string fileNamePrefix;
	ReadSignature readSignature;

	list<Timestamped> waitingQueue;

	void archive();
	void collect(Timestamped);

public:
	Storage(string fileNamePrefix) : fileNamePrefix(fileNamePrefix) {}
	~Storage();
	void setReadSignature(string, double, double, double, unsigned int);

	friend Storage& operator<< (Storage&, Timestamped);
};

Storage& operator<< (Storage&, Timestamped);
