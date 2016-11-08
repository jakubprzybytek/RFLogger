#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#include "../common/stdUtils.hpp"
#include "FFT.hpp"

using namespace std;

const float PI = acos(-1);

void fillWithCos(samples& samples, unsigned int n, const vector<float> &frequencies) {
    cout << "Test sample, n='" << n << "', frequencies: " << frequencies << endl;

    for (unsigned int i = 0; i < n; i++) {
	float real = 1.0;
	for (float frequency : frequencies) {
	    real *= cos(2 * PI * frequency * i / samples.size());
	}
	samples[i].real(real);
	samples[i].imag(0.0);
    }
}

void normalize(samples& samples) {
    for (unsigned int i = 0; i < samples.size(); i++) {
	samples[i] = samples[i] / (float)samples.size();
    }
}

int main() {

    samples input(32);
    fillWithCos(input, 32, {1.0, 4.0});

    cout << input << endl;

    samples output(input.size());

    FFT fft;
    fft.transform(input, output);

    normalize(output);

    for (unsigned int i = 0; i < output.size(); i++) {
	cout << norm(output[i]) << endl;
    }
}
