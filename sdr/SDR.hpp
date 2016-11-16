#pragma once
#include <complex>
#include <vector>

using namespace std;

typedef complex<float> Sample;
typedef vector<Sample> Samples;

class SamplesUtil {

public:
	static void shrink(Samples, Samples);

};
