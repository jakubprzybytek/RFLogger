#include <complex>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Formats.hpp>

#include "SDR.hpp"

using namespace SoapySDR;

class SDRDevice {

private:

    Device* device;

    Stream* stream;
    size_t streamMTU;
    complex<float>* buffer;
    void* buffers[1];

public:
    
    static void listAvailableSDRDevices();

    SDRDevice();
    ~SDRDevice();

    void setBandwidth(double bandwidth);
    void setSampleRate(double sampleRate);
    void setFrequency(double frequency);

    void setupStream();
    void closeStream();
    void printStreamInfo();
    void readStream(Samples& samples);

    void printInfo();

};