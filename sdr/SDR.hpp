#pragma once
#include <complex>
#include <vector>

using namespace std;

typedef complex<float> Sample;
typedef vector<Sample> Samples;

class Timestamped {

public:
	unsigned long long ms;
	Samples samples;

	Timestamped() {}
	Timestamped(unsigned long long ms, Samples samples) : ms(ms), samples(samples) {}
};

class SamplesUtil {

public:
	static void shrink(Samples&, Samples&);

	static void fillWithCos(Samples&, const vector<float> &);
	static void fillWithCos(Samples&, const unsigned int, const vector<float> &);
};
