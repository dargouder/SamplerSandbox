#pragma once

#include "lodepng/lodepng.h"
#include "Image.h"

namespace Solstice {

	class ImageIO {

	public:
		static bool export_png(std::string filename, std::vector<unsigned char>& image, int x, int y);
	};

}