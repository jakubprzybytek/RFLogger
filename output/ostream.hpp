#include <iostream>

#include "../SDR.hpp"

class OStreamSpectrumWriter {

    ostream& stream;

public:

    OStreamSpectrumWriter(ostream& stream);

    void process(const Samples& samples);

};

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter& os, const Samples& samples);