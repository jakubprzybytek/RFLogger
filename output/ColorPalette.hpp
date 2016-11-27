#include <vector>

#include <Magick++.h>

using namespace std;
using namespace Magick;

#define BLACK ColorRGB(0.0, 0.0, 0.0)
#define BLUE ColorRGB(0.0, 0.0, 1.0)
#define GREEN ColorRGB(0.0, 1.0, 0.0)
#define YELLOW ColorRGB(1.0, 1.0, 0.0)
#define RED ColorRGB(1.0, 0.0, 0.0)

class ColorTransitionsPalette {

private:
	void buildPalette(vector<ColorRGB>);
	
public:

	static ColorTransitionsPalette& INSTANCE();

	vector<ColorRGB> palette;

	ColorTransitionsPalette(vector<ColorRGB>);
	unsigned short size();
};
