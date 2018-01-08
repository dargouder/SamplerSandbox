//
// Created by Darryl Gouder on 22/12/2017.
//
#pragma once

#include "IO/Image.h"

namespace Solstice
{
    class Statistics
    {
      public:
        static double MSE(const Image& ground_truth,
                          const Image& observed_image, int nx, int ny)
        {
            double res = 0.0;
            for (int i = 0; i < nx; ++i)
            {
                for (int j = 0; j < ny; ++j)
                {
                    double error = ground_truth.get_pixel(i, j).r -
                                   observed_image.get_pixel(i, j).r;
                    res += error * error;
                }
            }
            return res / double(nx * ny);
        }
    };

}  // namespace Solstice