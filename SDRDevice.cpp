#include <iostream>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

#include "SDRDevice.hpp"

void SDRDevice::printSystemInformation() {
    cout << "Enumerating available SDR devices:\n";

    KwargsList devicesList = Device::enumerate();

    int i = 0;
    for (Kwargs deviceInfo : devicesList) {
	cout << "(" << ++i << ") " << deviceInfo["label"] << " (" << deviceInfo["driver"] << ")\n";
    }

    cout << "Found " << i << " device(s)\n";
}
