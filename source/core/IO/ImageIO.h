#pragma once

#include "Image.h"
#include "lodepng/lodepng.h"

namespace Solstice
{
    class ImageIO
    {
      public:
        static bool export_png(std::string filename,
                               std::vector<unsigned char>& image, int x, int y);
    };

}  // namespace Solstice