#include "FFT.hpp"
#include "kissfft.hh"

using namespace kissfft_utils;

void FFT::transform (Samples &input, Samples &output) {
	kissfft<float> fft(input.size(), false);
	fft.transform(input.data(), output.data());
}
