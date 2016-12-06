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
	cout << "\t-l, --list-device\t\t\tList all available SDR devices and exit" << endl << endl;
	cout << "\t-i, --device-info\t\t\tDisplay detailed information about the device in use" << endl;
	cout << "\t-n, --number <number>\t\tPerform <number> reads and exit. If '0' then read in loop." << endl;
	cout << "\t-b, --bandwidth <float>\t\tSets bandwidth to <float>" << endl;
	cout << "\t-s, --samplerate <float>\t\tSets sample reate to <float>" << endl;
	cout << "\t-f, --frequency <float>\t\tSets frequency to <float>" << endl;
	cout << "\t-c, --console <number>\t\tUse console as an output with width set to <number>" << endl << endl;
	cout << "\t-h, --help\t\t\t\t\tDisplay this help information and exit" << endl;
}

int main (int argc, char **argv) {

	static unsigned int number = 10;
	double bandwidth = 1.536e6;
	double sampleRate = 2.048e6;
	double frequency = 100.5e6;
	static int printDeviceInfo = 0;
	unsigned short consoleWidth = 200;
	milliseconds interval(1000);

	static struct option longOptions[] = {
		{ "list-devices", no_argument, 0, 'l' },
		{ "device-info", no_argument, &printDeviceInfo, 'i' },
		{ "number", required_argument, 0, 'n' },
		{ "bandwidth", required_argument, 0, 'b' },
		{ "samplerate", required_argument, 0, 's' },
		{ "frequency", required_argument, 0, 'f' },
		{ "console", required_argument, 0, 'c' },
		{ "help", no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	int opt;
	int optionIndex = 0;
	while ((opt = getopt_long(argc, argv, "lin:b:s:f:c:ht:", longOptions, &optionIndex)) != -1) {
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

			case 'b':
			bandwidth = stof(optarg);
			break;

			case 's':
			sampleRate = stof(optarg);
			break;

			case 'f':
			frequency = stof(optarg);
			break;

			case 'c':
			consoleWidth = stoi(optarg);
			break;

			case 't':
			interval = sToDuration(optarg);
			break;

			case 'h':
			printHelp();
			exit(0);
		}
	}
cout << "Internal: " << interval << endl;
	OStreamSpectrumWriter console(cout, consoleWidth);
	ReadSamples(number, bandwidth, sampleRate, frequency, interval, printDeviceInfo, console);
}
