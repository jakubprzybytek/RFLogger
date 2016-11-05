#include <SoapySDR/Device.hpp>
#include <SoapySDR/Formats.hpp>

using namespace SoapySDR;

class SDRDevice {

private:
    Device* device;

public:
    
    static void listAvailableSDRDevices();

    SDRDevice();

    ~SDRDevice();

    void printInfo();

};