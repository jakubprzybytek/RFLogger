#include <complex>
#include <vector>

#include "kissfft.hh"

using namespace std;
using namespace kissfft_utils;

typedef complex<float> sample;
typedef vector<sample> samples;

class FFT {

public:

    void transform (samples &input, samples &output) {
	kissfft<float> fft(input.size(), false);
	fft.transform(input.data(), output.data());
    }

};
