#include "ImageIO.h"
#include <fstream>
#include <iostream>

using namespace Solstice;

/*bool Solstice::ImageIO::export_ppm(std::string filename, const Image& image,
int x, int y)
{
    auto char_image = image.get_image();
    std::ofstream image_file;

    image_file << "P6" << std::endl;
    image_file << x << " " << y << std::endl;
    image_file << "255" << std::endl;

    image_file.open(filename, std::ios::binary);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int pixel_index;
            if (image.is_valid_pixel(i, j)) {

                image_file << char_image[pixel_index];
            }
        }
    }
    image_file.close();
    return false;
}*/

bool ImageIO::export_png(std::string filename,
                         std::vector<unsigned char>& image, int _width,
                         int _height)
{
    unsigned error = lodepng::encode(filename, image, _width, _height);
    // if there's an error, display it
    if (error)
    {
        std::cout << "encoder error " << error << ": "
                  << lodepng_error_text(error) << std::endl;
        return false;
    }
    return true;
}