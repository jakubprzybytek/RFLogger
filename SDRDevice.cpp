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
    cout << "Driver key: " << device->getDriverKey() << endl;
    cout << "Hardware key: " << device->getHardwareKey() << endl;
    cout << "Hardware info: " << device->getHardwareInfo() << endl;
    cout << "Frontent mapping: " << device->getFrontendMapping(SOAPY_SDR_RX) << endl;

    size_t channels = device->getNumChannels(SOAPY_SDR_RX);
    cout << "Number of channels: " << channels << endl;
    for (size_t channelNumber = 0; channelNumber < channels; channelNumber++) {
	cout << "Channel " << channelNumber << " info: " << device->getChannelInfo(SOAPY_SDR_RX, channelNumber) << endl;
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
