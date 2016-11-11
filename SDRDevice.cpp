#include <iostream>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

#include "SDRDevice.hpp"

#define CHANNEL 0

SDRDevice::SDRDevice() {
    cout << "Initializing SDR Device..." << endl;

    device = Device::make();
}

SDRDevice::~SDRDevice() {
    cout << "Closing SDR Device" << endl;

    Device::unmake(device);
}

void SDRDevice::setBandwidth(double bandwidth) {
    cout << "Setting bandwidth to: " << Hertz(bandwidth);
    device->setBandwidth(SOAPY_SDR_RX, CHANNEL, bandwidth);
    cout << ", set to: " << Hertz(device->getBandwidth(SOAPY_SDR_RX, CHANNEL)) << endl;
}

void SDRDevice::setSampleRate(double sampleRate) {
    cout << "Setting sample rate to: " << Hertz(sampleRate);
    device->setSampleRate(SOAPY_SDR_RX, CHANNEL, sampleRate);
    cout << ", set to: " << Hertz(device->getSampleRate(SOAPY_SDR_RX, CHANNEL)) << endl;
}

void SDRDevice::setFrequency(double frequency) {
    cout << "Setting frequency to: " << Hertz(frequency);
    device->setFrequency(SOAPY_SDR_RX, CHANNEL, frequency);
    cout << ", set to: " << Hertz(device->getFrequency(SOAPY_SDR_RX, CHANNEL)) << endl;
}

void SDRDevice::setupStream() {
    cout << "Setting up a stream" << endl;
    stream = device->setupStream(SOAPY_SDR_RX, "CF32");
    streamMTU = device->getStreamMTU(stream);
    device->activateStream(stream);

    buffer = new complex<float>[streamMTU];
    buffers[0] = buffer;
}

void SDRDevice::closeStream() {
    cout << "Closing stream" << endl;
    device->deactivateStream(stream);
    device->closeStream(stream);

    delete buffer;
}

void SDRDevice::printStreamInfo() {
    cout << "Stream MTU: " << streamMTU << endl;
    cout << "Stream buffer size: " << streamMTU * sizeof(complex<float>) << endl;
}

void SDRDevice::readStream(Samples& samples) {
    int flags = 0;
    long long timeNs = 0;
    /* int read = */ device->readStream(stream, buffers, streamMTU, flags, timeNs);

//    cout << "Read '" << read << "' in '" << timeNs << "' ns" << endl;

    for (unsigned int i = 0; i < samples.size(); i++) {
	samples[i] = buffer[i];
    }
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

	// Gain API
	cout << "Channel " << channelNumber << " automatic gain support: " << (device->hasGainMode(SOAPY_SDR_RX, channelNumber) ? "yes" : "no") << endl;
	vector<string> gains = device->listGains(SOAPY_SDR_RX, channelNumber);
	cout << "Channel " << channelNumber << " available gains: " << gains << endl;
	for (string gain : gains) {
	    cout << "Channel " << channelNumber << " gain range for '" << gain << "': " << device->getGainRange(SOAPY_SDR_RX, channelNumber, gain) << endl;
	}

	// Antenna API
	cout << "Channel " << channelNumber << " available antennas: " << device->listAntennas(SOAPY_SDR_RX, channelNumber) << endl;

	// sample rates
	cout << "Channel " << channelNumber << " sample rates: " << device->listSampleRates(SOAPY_SDR_RX, channelNumber) << endl;

	// bandwidths
	cout << "Channel " << channelNumber << " baseband widths: " << device->getBandwidthRange(SOAPY_SDR_RX, channelNumber) << endl;
    }

    // Clocks API
    cout << "Master clock rate: " << device->getMasterClockRate() << endl;
    cout << "Master clock rates: " << device->getMasterClockRates() << endl;
    cout << "Clock sources: " << device->listClockSources() << endl;
    cout << "Clock source: " << device->getClockSource() << endl;

    // Time API
    cout << "Time sources: " << device->listTimeSources() << endl;
    cout << "Time source: " << device->getTimeSource() << endl;

    // Sensors API
    cout << "Sensors: " << device->listSensors() << endl;

    // Register API
    cout << "Register interfaces: " << device->listRegisterInterfaces() << endl;

    // Settings API
    cout << "Settings: " << device->getSettingInfo() << endl;
}

void SDRDevice::listAvailableSDRDevices() {
    cout << "Listing available SDR devices:" << endl;

    KwargsList devicesList = Device::enumerate();

    int i = 0;
    for (Kwargs deviceInfo : devicesList) {
	cout << "(" << ++i << ") " << deviceInfo["label"] << " (" << deviceInfo["driver"] << ")" << endl;
    }

    cout << "Found " << i << " device(s)" << endl;
}
