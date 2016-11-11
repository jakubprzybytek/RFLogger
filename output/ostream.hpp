#include <iostream>

#include "../sdr/SDR.hpp"

class OStreamSpectrumWriter {

    ostream& stream;

    short consoleWidth;

public:

    OStreamSpectrumWriter(ostream& stream, short consoleWidth = 10);

    void process(const Samples& samples);

};

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter& os, const Samples& samples);