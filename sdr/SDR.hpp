#pragma once
#include <complex>
#include <vector>

using namespace std;

typedef complex<float> Sample;
typedef vector<Sample> Samples;

class SamplesUtil {

public:
	static void shrink(Samples, Samples);

	static void fillWithCos(Samples&, const vector<float> &);
	static void fillWithCos(Samples&, unsigned int, const vector<float> &);
};
