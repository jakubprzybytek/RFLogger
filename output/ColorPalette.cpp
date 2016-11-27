#include <iostream>
#include <cassert>

#include "ColorPalette.hpp"

ColorTransitionsPalette& ColorTransitionsPalette::INSTANCE() {
	static ColorTransitionsPalette palette({ BLACK, BLUE, GREEN, YELLOW, RED });
	return palette;
}

ColorTransitionsPalette::ColorTransitionsPalette(vector<ColorRGB> breakColors) {
	buildPalette(breakColors);
}

void ColorTransitionsPalette::buildPalette(vector<ColorRGB> breakColors) {

	assert(breakColors.size() > 1);

	ColorRGB previousColor = breakColors.front();
	for (ColorRGB& breakColor : breakColors) {
		if (&breakColor != &breakColors.front()) {
			for (unsigned int j = 0; j <= 255; j++) {
				palette.push_back(ColorRGB(
						previousColor.red() + (breakColor.red() - previousColor.red()) * (double)j / 255.0,
						previousColor.green() + (breakColor.green() - previousColor.green()) * (double)j / 255.0,
						previousColor.blue() + (breakColor.blue() - previousColor.blue()) * (double)j / 255.0)
				);
			}
			previousColor = breakColor;
		}
	}

	cout << "Created color transitions palette with " << palette.size() << " colors" << endl;
}

unsigned short ColorTransitionsPalette::size() {
	return palette.size();
}
