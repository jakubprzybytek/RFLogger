#pragma once

#include <complex>
#include <vector>

#include "common/Timestamp.hpp"

using namespace std;

typedef complex<float> Sample;
typedef vector<Sample> Samples;

class Timestamped {

public:
	Timestamp ts;
	Samples samples;

	Timestamped() {}
	Timestamped(Timestamp ts, Samples samples) : ts(ts), samples(samples) {}
};

class SamplesUtil {

public:
	static void shrink(Samples&, Samples&);

	static void fillWithCos(Samples&, const vector<float> &);
	static void fillWithCos(Samples&, const unsigned int, const vector<float> &);
};
