#include "../SDR.hpp"
#include "kissfft.hh"

using namespace std;
using namespace kissfft_utils;

class FFT {

public:

    void transform (Samples &input, Samples &output) {
	kissfft<float> fft(input.size(), false);
	fft.transform(input.data(), output.data());
    }

};
