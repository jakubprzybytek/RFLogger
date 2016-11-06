#include <iostream>

using namespace std;

#include "SDRDevice.hpp"

int main () {
    cout << "Starting..." << endl;

//    SDRDevice::listAvailableSDRDevices();

    SDRDevice *sdr = new SDRDevice();

    sdr->printInfo();

    delete sdr;
}
