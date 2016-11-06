#include <iostream>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

#include "stdUtils.hpp"
#include "SDRDevice.hpp"

SDRDevice::SDRDevice() {
    cout << "Initializing SDR Device..." << endl;

    device = Device::make();
}

SDRDevice::~SDRDevice() {
    cout << "Closing SDR Device\n";

    Device::unmake(device);
}

void SDRDevice::printInfo() {
    // general info
    cout << "Driver key: " << device->getDriverKey() << endl;
    cout << "Hardware key: " << device->getHardwareKey() << endl;
    cout << "Hardware info: " << device->getHardwareInfo() << endl;
    cout << "Frontent mapping: " << device->getFrontendMapping(SOAPY_SDR_RX) << endl;

    // channels info
    size_t channels = device->getNumChannels(SOAPY_SDR_RX);
    cout << "Number of channels: " << channels << endl;
    for (size_t channelNumber = 0; channelNumber < channels; channelNumber++) {
	cout << "Channel " << channelNumber << " info: " << device->getChannelInfo(SOAPY_SDR_RX, channelNumber) << endl;
        cout << "Channel " << channelNumber << " full duplex support: " << (device->getFullDuplex(SOAPY_SDR_RX, channelNumber) ? "yes" : "no") << endl;

        // supported formats
	cout << "Channel " << channelNumber << " stream formats: " << device->getStreamFormats(SOAPY_SDR_RX, channelNumber) << endl;
	double fullScale;
	string nativeStreamFormat = device->getNativeStreamFormat(SOAPY_SDR_RX, channelNumber, fullScale);
	cout << "Channel " << channelNumber << " native stream formats: " << nativeStreamFormat << ", maximum possible value: " << fullScale << endl;
	cout << "Channel " << channelNumber << " stream args: " << device->getStreamArgsInfo(SOAPY_SDR_RX, channelNumber) << endl;

	// frequency info
	cout << "Channel " << channelNumber << " tunable elements: " << device->listFrequencies(SOAPY_SDR_RX, channelNumber) << endl;
	cout << "Channel " << channelNumber << " tune args: " << device->getFrequencyArgsInfo(SOAPY_SDR_RX, channelNumber) << endl;
	cout << "Channel " << channelNumber << " frequency ranges: " << device->getFrequencyRange(SOAPY_SDR_RX, channelNumber) << endl;

	// gains info
	cout << "Channel " << channelNumber << " automatic gain support: " << (device->hasGainMode(SOAPY_SDR_RX, channelNumber) ? "yes" : "no") << endl;
	vector<string> gains = device->listGains(SOAPY_SDR_RX, channelNumber);
	cout << "Channel " << channelNumber << " available gains: " << gains << endl;
	for (vector<string>::iterator gainIterator = gains.begin(); gainIterator != gains.end(); gainIterator++) {
	    cout << "Channel " << channelNumber << " gain range for '" << *gainIterator << "': " << device->getGainRange(SOAPY_SDR_RX, channelNumber, *gainIterator) << endl;
	}

	// sample rates
	cout << "Channel " << channelNumber << " sample rates: " << device->listSampleRates(SOAPY_SDR_RX, channelNumber) << endl;
    }
}

void SDRDevice::listAvailableSDRDevices() {
    cout << "Listing available SDR devices:\n";

    KwargsList devicesList = Device::enumerate();

    int i = 0;
    for (Kwargs deviceInfo : devicesList) {
	cout << "(" << ++i << ") " << deviceInfo["label"] << " (" << deviceInfo["driver"] << ")\n";
    }

    cout << "Found " << i << " device(s)\n";
}
