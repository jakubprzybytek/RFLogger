#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
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

public:
    ReadSignature(ReadSignature&) = default;
    ReadSignature()
	: sdrDevice(""), bandwidth(0.0), sampleRate(0.0), frequency(0.0) {}
    ReadSignature(string sdrDevice, double bandwidth, double sampleRate, double frequency)
	: sdrDevice(sdrDevice), bandwidth(bandwidth), sampleRate(sampleRate), frequency(frequency) {}

    template <class Archive>
    void serialize (Archive& ar, __attribute__((unused)) const unsigned int version);
};

class SamplesCollection {

private:
    ReadSignature readSignature;
    Samples samples;

public:
    SamplesCollection (ReadSignature readSignature, Samples samples)
	: readSignature (readSignature), samples(samples) {}

    template <class Archive>
    void serialize (Archive& ar, __attribute__((unused)) const unsigned int version);
};

class Storage {

private:
    string fileNamePrefix;
    ReadSignature readSignature;

public:
    Storage (string fileNamePrefix) : fileNamePrefix (fileNamePrefix) {}
    void setReadSignature (string sdrDevice, double bandwidth, double sampleRate, double frequency);

    void archive (Samples samples);
};

Storage& operator << (Storage& storage, Samples& samples);
