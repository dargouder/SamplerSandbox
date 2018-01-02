#include <cmath>

#include "Image.h"

using namespace Solstice;

bool Image::is_valid_pixel(int x, int y) const {
    if ((x > -1 && x < _width) || (y > -1 && y < _height)) {
        return true;
    }

    // Index out of bounds.
    return false;
}

bool Image::set_pixel(int x, int y, RGBColour colour) {
    if (is_valid_pixel(x, y)) {
        *(_pixels[y][x]) = colour;
        return true;
    }

    // Index out of bounds.
    return false;
}

RGBColour Image::get_pixel(int x, int y) const {
    if (is_valid_pixel(x, y)) {
        return *(_pixels[y][x]);
    }

    // Index out of bounds.
    return RGBColour(0);
}

std::vector<unsigned char> Image::get_image() const {
    std::vector<unsigned char> image;
    for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
            RGBColour colour = *_pixels[y][x];
            colour.r = sqrtf(colour.r);
            colour.g = sqrtf(colour.g);
            colour.b = sqrtf(colour.b);
            image.push_back(
                (unsigned char)Maths::Min(255, (int)(256.0f * colour.r)));
            image.push_back(
                (unsigned char)Maths::Min(255, (int)(256.0f * colour.g)));
            image.push_back(
                (unsigned char)Maths::Min(255, (int)(256.0f * colour.b)));
            image.push_back(255);
        }
    }

    return image;
}

std::string Image::get_image_name() const
{
    return _name;
}