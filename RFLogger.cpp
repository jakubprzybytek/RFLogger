#include <iostream>
#include <getopt.h>

using namespace std;

#include "output/ostream.hpp"
#include "fft/FFT.hpp"
#include "sdr/SDRDevice.hpp"
#include "RFLogger.hpp"

static void printHelp() {
    cout << "Usage RFLogger [options]" << endl;
    cout << "  Options summary:" << endl;
    cout << "    -l, --list-device              List all available SDR devices and exit" << endl << endl;
    cout << "    -i, --device-info              Display detailed information about the device in use" << endl;
    cout << "    -n, --number <number>          Perform <number> reads and exit. If '0' then read in loop." << endl << endl;
    cout << "    -h, --help                     Display this help information and exit" << endl;
}

int main (int argc, char **argv) {

    static unsigned int number = 10;
    double bandwidth = 1.536e6;
    double sampleRate = 2.048e6;
    double frequency = 100.5e6;
    static int printDeviceInfo = 0;

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

    ReadSamples(number, bandwidth, sampleRate, frequency, printDeviceInfo);

}
