#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <ctime>

#include "../common/stdUtils.hpp"
#include "FFT.hpp"

using namespace std;

const float _2PI = 2.0 * acos(-1);

void fillWithCos(samples& samples, unsigned int n, const vector<float> &frequencies) {
    cout << "Test sample: n='" << n << "', frequencies: " << frequencies << endl;

    for (unsigned int i = 0; i < n; i++) {
	float real = 0.0;
	for (float frequency : frequencies) {
	    real += cos(_2PI * frequency * i / samples.size());
	}
	samples[i].real(real / frequencies.size());
	samples[i].imag(0.0);
    }
}

void normalize(samples& samples) {
    for (unsigned int i = 0; i < samples.size(); i++) {
	samples[i] = samples[i] / (float)samples.size();
    }
}

int main() {

    FFT fft;

    cout << "Test 1: sanity check" << endl;

    samples smallInput(4);
    fillWithCos(smallInput, 4, {1.0});
    cout << "Input data: " << smallInput << endl;

    samples smallOutput(smallInput.size());

    fft.transform(smallInput, smallOutput);

    normalize(smallOutput);

    cout << "Output data: [";
    for (sample a : smallOutput) {
	cout << norm(a) << ",";
    }
    cout << "]" << endl;

    cout << endl << "Test 2: execution time" << endl;

    samples input(1 << 20);
    fillWithCos(input, 1 << 20, {2.0, 6.0});

    samples output(input.size());

    clock_t start = clock();
    fft.transform(input, output);
    clock_t end = clock();

    cout << "CPU time: " << double(end - start) / (CLOCKS_PER_SEC / 1000.0) << "ms" << endl;

}
