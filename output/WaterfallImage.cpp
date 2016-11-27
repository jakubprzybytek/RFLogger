#include <iostream>
#include <cassert>

#include "WaterfallImage.hpp"

void WaterfallImage::init() {
	InitializeMagick(NULL);
}

void WaterfallImage::addSpectrum(Samples samples) {
	assert(samples.size() == width);
	
	vector<PixelIndex> line(width);

	float max = 0.0;
	for (Sample sample : samples) {
		if (norm(sample) > max) {
			max = norm(sample);
		}
	}

	float maxIndex = (float)palette.size() - 1;
	unsigned int i = 0;
	for (Sample sample : samples) {
		line[i++] = (PixelIndex)(maxIndex * norm(sample) / max);
	}

	buffer.push_back(line);
}

void WaterfallImage::close() {
	Image image(Geometry(width, buffer.size()), Color("black"));

	unsigned int i = 0;
	for (vector<PixelIndex> line : buffer) {
		PixelPacket *pixelCache = image.getPixels(0, i++, width, 1);
		
		unsigned int j = 0;
		for (PixelIndex index : line) {
			pixelCache[j++] = palette.palette[index];
		}

		image.syncPixels();	
	}

	image.write(fileName); 
	cout << "Saved " << buffer.size() << " lines into " << fileName << endl;
}

WaterfallImage& operator<< (WaterfallImage& waterfall, const Samples& samples) {
	waterfall.addSpectrum(samples);
	return waterfall;
}
