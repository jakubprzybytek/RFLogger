#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/complex.hpp>

#include "../sdr/SDR.hpp"

using namespace std;
using namespace boost::archive;

class SamplesCollection {

private:
    Samples samples;

public:
    SamplesCollection(Samples samples) : samples(samples) {}

//    friend class boost::serialization::access;
    template <class Archive>
    void serialize (Archive & ar, __attribute__((unused))  const unsigned int version) {
	ar & samples;
    }

};

class Storage {

private:

public:

    void archive(Samples samples) {
	ofstream ofs("Samples.bin");
	binary_oarchive archive(ofs);

	archive << samples;
    }

};
