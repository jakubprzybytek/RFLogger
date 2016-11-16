#include "SDR.hpp"

void SamplesUtil::shrink(Samples source, Samples target) {
	complex<float> max(0.0, 0.0);

	unsigned int j = 0;
	for (unsigned int i = 0; i < source.size(); i++) {
		if (norm(source[i]) > norm(max)) {
			max = source[i];
		}
		if (i % target.size() == target.size() - 1) {
			target[j++] = max;
		}
	}

	if (j < target.size()) {
		target[j] = max;
	}
}
