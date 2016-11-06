#include <SoapySDR/Device.hpp>
#include <SoapySDR/Formats.hpp>

using namespace SoapySDR;

class SDRDevice {

private:

    Device* device;

    Stream* stream;

public:
    
    static void listAvailableSDRDevices();

    SDRDevice();

    ~SDRDevice();

    void setBandwidth(double bandwidth);

    void setSampleRate(double sampleRate);

    void setFrequency(double frequency);

    void setupStream();

    void printStreamInfo();

    void closeStream();

    void printInfo();

};