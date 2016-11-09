#include <iostream>
#include <getopt.h>

using namespace std;

#include "SDRDevice.hpp"
#include "fft/FFT.hpp"
#include "output/ostream.hpp"

static void printHelp() {
    cout << "Usage RFLogger [options]" << endl;
    cout << "  Options summary:" << endl;
    cout << "    -l, --list-device              List all available SDR devices and exit" << endl;
    cout << "    -i, --device-info              Display detailed information about the device in use" << endl;
    cout << "    -h, --help                     Display this help information and exit" << endl;
}

int main (int argc, char **argv) {

    static int printDeviceInfo = 0;

    cout << "Starting..." << endl;

    static struct option longOptions[] = {
	{"list-devices", no_argument, 0, 'l'},
	{"device-info", no_argument, &printDeviceInfo, 'i'},
	{"help", no_argument, 0, 'h'},
	{ 0, 0, 0, 0 }
    };

    int opt;
    int optionIndex = 0;
    while ((opt = getopt_long(argc, argv, "lih", longOptions, &optionIndex)) != -1) {
	switch (opt) {
	    case 'l':
	        SDRDevice::listAvailableSDRDevices();
	    exit(0);

	    case 'i':
	    printDeviceInfo = 1;
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

    OStreamSpectrumWriter console(cout);

    FFT fft;

    Samples samples(128);
    Samples spectrum(samples.size());

    for (unsigned int i = 0; i < 50; i++) {
	sdr->readStream(samples);
	fft.transform(samples, spectrum);
	console << spectrum;
    }

    sdr->closeStream();

    delete sdr;
}
