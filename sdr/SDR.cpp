#include "SDR.hpp"

const Sample ZERO(0.0, 0.0);
const float _2PI = 2.0 * acos(-1);

void SamplesUtil::shrink(Samples& source, Samples& target) {
	Sample max = ZERO;

	unsigned short binWidth = (source.size() - 1) / target.size() + 1;
	unsigned short j = 0;
	for (unsigned int i = 0; i < source.size(); i++) {
		if (norm(source[i]) > norm(max)) {
			max = source[i];
		}
		if (i % binWidth + 1 == binWidth) {
			target[j++] = max;
			max = ZERO;
		}
	}

	if (j < target.size()) {
		target[j] = max;
	}
}

void SamplesUtil::fillWithCos(Samples& samples, const vector<float> &frequencies) {
	fillWithCos(samples, samples.size(), frequencies);
}

void SamplesUtil::fillWithCos(Samples& samples, const unsigned int n, const vector<float> &frequencies) {
	for (unsigned int i = 0; i < n; i++) {
		float real = 0.0;
		for (float frequency : frequencies) {
			real += cos(_2PI * frequency * i / samples.size());
		}
		samples[i].real(real / frequencies.size());
		samples[i].imag(0.0);
	}
}
