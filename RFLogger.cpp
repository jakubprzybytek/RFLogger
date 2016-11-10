#include <csignal>
#include <iostream>
#include <getopt.h>

using namespace std;

#include "SDRDevice.hpp"
#include "fft/FFT.hpp"
#include "output/ostream.hpp"

static void printHelp() {
    cout << "Usage RFLogger [options]" << endl;
    cout << "  Options summary:" << endl;
    cout << "    -l, --list-device              List all available SDR devices and exit" << endl << endl;
    cout << "    -i, --device-info              Display detailed information about the device in use" << endl;
    cout << "    -n, --number <number>          Perform <number> reads and exit. If '0' then read in loop." << endl << endl;
    cout << "    -h, --help                     Display this help information and exit" << endl;
}

static bool keepReading = true;

static void interrupt(int signum) {
    keepReading = false;
}

int main (int argc, char **argv) {

    signal(SIGINT, interrupt);

    static int printDeviceInfo = 0;
    static unsigned int number = 10;

    cout << "Starting..." << endl;

    static struct option longOptions[] = {
	{ "list-devices", no_argument, 0, 'l' },
	{ "device-info", no_argument, &printDeviceInfo, 'i' },
	{ "number", required_argument, 0, 'n' },
        { "help", no_argument, 0, 'h' },
        { 0, 0, 0, 0 }
    };

    int opt;
    int optionIndex = 0;
    while ((opt = getopt_long(argc, argv, "lin:h", longOptions, &optionIndex)) != -1) {
	switch (opt) {
	    case 'l':
	        SDRDevice::listAvailableSDRDevices();
	    exit(0);

	    case 'i':
	    printDeviceInfo = 1;
	    break;

	    case 'n':
	    number = stoi(optarg);
	    break;

	    case 'h':
	    printHelp();
	    exit(0);
	}
    }

    SDRDevice *sdr = new SDRDevice();

    if (printDeviceInfo) {
	sdr->printInfo();
    }

    sdr->setBandwidth(1.536e6);
    sdr->setSampleRate(2.048e6);
    sdr->setFrequency(100.5e6);

    sdr->setupStream();
    if (printDeviceInfo) {
	sdr->printStreamInfo();
    }

    OStreamSpectrumWriter console(cout, 200);

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
	sdr->readStream(samples);
	fft.transform(samples, spectrum);
	console << spectrum;

	if (number > 0) {
	    if (++i >= number) {
		keepReading = false;
	    }
	}
    }

    sdr->closeStream();

    delete sdr;
}
