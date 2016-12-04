#include <csignal>
#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

#include "common/Timestamp.hpp"
#include "common/Timer.hpp"
#include "output/ostream.hpp"
#include "output/WaterfallImage.hpp"
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

	mutex feedbackMutex;
	condition_variable feedback;
	
	Timer timer(seconds(5), feedbackMutex, feedback);
	timer.start();
	
	{
		unique_lock<mutex> lock(feedbackMutex);
		feedback.wait(lock);
	}
	
	unsigned int i = 0;
	while (keepReading) {
		Timestamp ts = Timestamp::NOW();

		sdr.readStream(samples);
		fft.transform(samples, spectrum);
		
		output << Timestamped(ts, spectrum);
		
		SamplesUtil::shrink(spectrum, shrunkSpectrum);
		storage << Timestamped(ts, shrunkSpectrum);
		waterfall << shrunkSpectrum;

		if (number > 0) {
			if (++i >= number) {
				keepReading = false;
			}
		}
	}

	timer.stop();
	
	waterfall.close();
	sdr.closeStream();
}
