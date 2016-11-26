#include <Magick++.h> 
#include <iostream>
#include <vector>

using namespace std; 
using namespace Magick; 

void testGif() {
	cout << "Test 1 - Gif example: ImagesTest.gif" << endl;

	Image image(Geometry(64, 64), Color("red"));
	image.type(PaletteType);
	image.classType(PseudoClass);
	
	unsigned int i = 0;
	for (unsigned int j = 0; j <= 255; j++, i++) {
		image.colorMap(i, ColorRGB((double)j / 255.0, 0.0, 0.0));
	}
/*	for (unsigned int j = 0; j <= 255; j++, i++) {
		image.colorMap(i, ColorRGB(0.0, (double)j / 255.0, 0.0));
	}
	for (unsigned int j = 0; j <= 255; j++, i++) {
		image.colorMap(i, ColorRGB(0.0, 0.0, (double)j / 255.0));
	}
*/
	cout << "Color map size: " << image.colorMapSize() << ", max color map size: " << MaxColormapSize << endl;
	
	image.getPixels(0, 0, 64, 64); 
	IndexPacket *indexes = image.getIndexes();

	for (unsigned int i = 0; i < 256 * 1; i++) {
		indexes[i] = i;
	}	
	
	image.syncPixels();
	image.write("ImagesTest.gif"); 
}

#define BLUE ColorRGB(0.0, 0.0, 1.0)
#define GREEN ColorRGB(0.0, 1.0, 0.0)
#define YELLOW ColorRGB(1.0, 1.0, 0.0)
#define RED ColorRGB(1.0, 0.0, 0.0)

void testPng() {
	cout << "Test 2 - Png example: ImagesTest.png" << endl;

	Image image(Geometry(64, 64), Color("black"));
	PixelPacket *pixel_cache = image.getPixels(0, 0, 64, 64); 

	vector<ColorRGB> breakColors{ BLUE, GREEN, YELLOW, RED };

	unsigned int i = 0;
	ColorRGB previousColor = breakColors.front();
	for (ColorRGB& breakColor : breakColors) {
		if (&breakColor != &breakColors.front()) {
			for (unsigned int j = 0; j <= 255; j++, i++) {
				pixel_cache[i] = ColorRGB(
						previousColor.red() + (breakColor.red() - previousColor.red()) * (double)j / 255.0,
						previousColor.green() + (breakColor.green() - previousColor.green()) * (double)j / 255.0,
						previousColor.blue() + (breakColor.blue() - previousColor.blue()) * (double)j / 255.0);
			}
			previousColor = breakColor;
		}
	}
	
	cout << "Wrote: " << i << " pixels" << endl;

	image.syncPixels();	
	image.write( "ImagesTest.png" ); 
}

int main() { 
	InitializeMagick(NULL);
  
	testGif();
	testPng();

	return 0; 
}