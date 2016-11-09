#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <ctime>

#include "../SDR.hpp"
#include "../common/stdUtils.hpp"
#include "../output/ostream.hpp"
#include "FFT.hpp"

using namespace std;

const float _2PI = 2.0 * acos(-1);

void fillWithCos(Samples& samples, unsigned int n, const vector<float> &frequencies) {
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

void normalize(Samples& samples) {
    for (unsigned int i = 0; i < samples.size(); i++) {
	samples[i] = samples[i] / (float)samples.size();
    }
}

int main() {

    FFT fft;
    OStreamSpectrumWriter console(cout);

    cout << "Test 1: sanity check" << endl;

    Samples smallInput(4);
    fillWithCos(smallInput, 4, {1.0});
    cout << "Input data: " << smallInput << endl;

    Samples smallOutput(smallInput.size());

    fft.transform(smallInput, smallOutput);

    normalize(smallOutput);
    console << smallOutput;

    cout << "Output data: [";
    for (Sample a : smallOutput) {
	cout << norm(a) << ",";
    }
    cout << "]" << endl;

    cout << endl << "Test 2: execution time" << endl;

    for (auto n : {1 << 10, 1 << 16, 1 << 20}) {
	Samples input(n);
	fillWithCos(input, n, {2.0, 6.0});

	Samples output(input.size());

	clock_t start = clock();
	fft.transform(input, output);
	clock_t end = clock();

	cout << "CPU time: " << double(end - start) / (CLOCKS_PER_SEC / 1000.0) << "ms" << endl;
    }

}
