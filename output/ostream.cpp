#include "ostream.hpp"

OStreamSpectrumWriter::OStreamSpectrumWriter(ostream& stream) : stream(stream) {
}

void OStreamSpectrumWriter::process(const Samples& samples) {
    float max = 0.0;
    for (Sample sample : samples) {
	if (norm(sample) > max) {
	    max = norm(sample);
	}
    }
    for (Sample sample : samples) {
	stream << short(9 * norm(sample) / max);
    }
    stream << endl;
}

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter& os, const Samples& samples) {
    os.process(samples);
    return os;
}
