#include <csignal>
#include <iostream>

using namespace std;

#include "output/ostream.hpp"
#include "fft/FFT.hpp"
#include "sdr/SDRDevice.hpp"
#include "storage/Storage.hpp"

static bool keepReading = true;

static void interrupt(__attribute__((unused)) int signum) {
    keepReading = false;
}

void ReadSamples (unsigned int number, double bandwidth, double sampleRate, double frequency, bool printDeviceInfo, OStreamSpectrumWriter& output) {

    signal(SIGINT, interrupt);

    cout << "Starting reads..." << endl;

    SDRDevice sdr;

    if (printDeviceInfo) {
	sdr.printInfo();
    }

    sdr.setBandwidth(bandwidth);
    sdr.setSampleRate(sampleRate);
    sdr.setFrequency(frequency);

    sdr.setupStream();
    if (printDeviceInfo) {
	sdr.printStreamInfo();
    }

    FFT fft;

    Samples samples(1 << 16);
    Samples spectrum(samples.size());

    if (number > 0) {
	cout << "Performing '" << number << "' reads" << endl;
    } else {
	cout << "Performing endless reads" << endl;
    }    
    
    unsigned int i = 0;
    while (keepReading) {
	sdr.readStream(samples);
	fft.transform(samples, spectrum);
	output << spectrum;

	if (number > 0) {
	    if (++i >= number) {
		keepReading = false;
	    }
	}
    }

    Storage storage;
    storage.archive(spectrum);

    sdr.closeStream();
}
