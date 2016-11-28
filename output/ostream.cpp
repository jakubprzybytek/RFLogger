#include "../common/stdUtils.hpp"
#include "ostream.hpp"

OStreamSpectrumWriter::OStreamSpectrumWriter(ostream& stream, short consoleWidth) : stream(stream), consoleWidth(consoleWidth) {
}

void OStreamSpectrumWriter::process(const Timestamped& timestampedSamples) {
	stream << "[" << Console::Red << timestampedSamples.ms << Console::Reset << "] ";
	process(timestampedSamples.samples);
}

void OStreamSpectrumWriter::process(const Samples& samples) {
	float max = 0.0;
	for (Sample sample : samples) {
		if (norm(sample) > max) {
			max = norm(sample);
		}
	}

	short binWidth = (samples.size() - 1) / consoleWidth + 1;
	float binValue = 0.0;
	for (unsigned int i = 0; i < samples.size(); i++) {
		if (i != 0 && i % binWidth == 0) {
			stream << short(9 * binValue / max);
			binValue = 0.0;
		}
		if (norm(samples[i]) > binValue) {
			binValue = norm(samples[i]);
		}
	}
	stream << short(9 * binValue / max) << endl;
}

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter& os, const Samples& samples) {
	os.process(samples);
	return os;
}

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter& os, const Timestamped& timestampedSamples) {
	os.process(timestampedSamples);
	return os;
}
