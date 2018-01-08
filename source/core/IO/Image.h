#pragma once

#include "RGBColour.h"
#include "Solstice.h"

namespace Solstice
{
    class Image
    {
      private:
        int _width, _height;
        std::vector<std::vector<std::unique_ptr<RGBColour>>> _pixels;
        std::string _name;

      public:
        Image(int p_x, int p_y, std::string p_name)
            : _width(p_x), _height(p_y), _name(p_name)
        {
            init_image(_width, _height);
        }

        void init_image(int p_x, int p_y)
        {
            for (int i = 0; i < p_y; ++i)
            {
                std::vector<std::unique_ptr<RGBColour>> rows;
                for (int j = 0; j < p_x; ++j)
                {
                    rows.push_back(std::make_unique<RGBColour>());
                }
                _pixels.push_back(std::move(rows));
            }
        }

        bool is_valid_pixel(int x, int y) const;
        bool set_pixel(int x, int y, RGBColour colour);
        RGBColour get_pixel(int x, int y) const;

        std::string get_image_name() const;

        std::vector<unsigned char> get_image() const;
    };
}  // namespace Solstice