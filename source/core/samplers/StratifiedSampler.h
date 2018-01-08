#pragma once

#include "PixelSampler.h"

namespace Solstice
{
    class StratifiedSampler : public PixelSampler
    {
      public:
        StratifiedSampler(int p_x_pixel_samples, int p_y_pixel_samples,
                          bool p_jitter_samples, int p_n_sampled_dimensions)
            : PixelSampler(p_x_pixel_samples * p_y_pixel_samples,
                           p_n_sampled_dimensions),
              _x_pixel_samples(p_x_pixel_samples),
              _y_pixel_samples(p_y_pixel_samples),
              _jitter_samples(p_jitter_samples)
        {
        }

        void StartPixel(const Point2i& p_pixel);

      private:
        const int _x_pixel_samples;
        const int _y_pixel_samples;
        const bool _jitter_samples;
    };
}  // namespace Solstice