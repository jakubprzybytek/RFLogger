#include <iostream>

#include "../sdr/SDR.hpp"

class OStreamSpectrumWriter {

private:
	ostream& stream;
	short consoleWidth;

	void process(const Samples&);
	void process(const Timestamped&);

	friend OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter&, const Samples&);
	friend OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter&, const Timestamped&);
	
public:
	OStreamSpectrumWriter(ostream& stream, short consoleWidth = 10);
};

OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter&, const Samples&);
OStreamSpectrumWriter& operator<< (OStreamSpectrumWriter&, const Timestamped&);
