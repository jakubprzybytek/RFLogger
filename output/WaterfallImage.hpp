#include <list>
#include <vector>

#include <Magick++.h>

#include "../sdr/SDR.hpp"
#include "ColorPalette.hpp"

using namespace std;
using namespace Magick;

typedef unsigned short PixelIndex;

class WaterfallImage {

private:
	string fileName;
	unsigned int width;

	ColorTransitionsPalette& palette;

	list<vector<PixelIndex>> buffer;
	
public:

	static void init();

	WaterfallImage(string fileName, unsigned int width) : fileName(fileName), width(width), palette(ColorTransitionsPalette::INSTANCE()) {}

	void addSpectrum(Samples samples);
	void close();
};

WaterfallImage& operator<< (WaterfallImage&, const Samples&);
