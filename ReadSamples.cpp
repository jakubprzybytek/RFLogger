#include <csignal>
#include <iostream>
#include <chrono>
#include <ctime>

#include <sys/time.h>

using namespace std;
using namespace std::chrono;

#include "common/Timestamp.hpp"
#include "output/ostream.hpp"
#include "output/WaterfallImage.hpp"
#include "fft/FFT.hpp"
#include "sdr/SDRDevice.hpp"
#include "storage/Storage.hpp"

#define NOW2 duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()

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
	Samples shrunkSpectrum(1 << 10);

	if (number > 0) {
		cout << "Performing '" << number << "' reads" << endl;
	} else {
		cout << "Performing endless reads" << endl;
	}	

	Storage storage("SDRPlus-");
	storage.setReadSignature(sdr.getDeviceSignature(), bandwidth, sampleRate, frequency, spectrum.size());

	WaterfallImage::init();
	WaterfallImage waterfall("Waterfall.png", shrunkSpectrum.size());

	unsigned int i = 0;
	while (keepReading) {
		unsigned long long ms = NOW2;

		sdr.readStream(samples);
		fft.transform(samples, spectrum);
		
		Timestamp ts = Timestamp::NOW();
		cout << ts.formatTime() << endl;
		
		output << Timestamped(ms, spectrum);
		
		SamplesUtil::shrink(spectrum, shrunkSpectrum);
		storage << Timestamped(ms, shrunkSpectrum);
		waterfall << shrunkSpectrum;

		if (number > 0) {
			if (++i >= number) {
				keepReading = false;
			}
		}
	}

	waterfall.close();
	sdr.closeStream();
}
