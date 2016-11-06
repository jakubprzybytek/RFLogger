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

	// stream args info
	cout << "Channel " << channelNumber << " stream args: " << device->getStreamArgsInfo(SOAPY_SDR_RX, channelNumber) << endl;
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
