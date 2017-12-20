#pragma once
#include "Random.h"
#include "Sampler.h"

namespace Solstice {
    class PixelSampler : public Sampler {
      public:
        /* PixelSampler Public Methods */
        PixelSampler(int64_t p_samples_per_pixel, int p_n_sampled_dimensions);
        ~PixelSampler();

        bool StartNextSample();

        float Get1D();

        Point2f Get2D();

      protected:
        std::vector<std::vector<float>> _samples_1D;
        std::vector<std::vector<Point2f>> _samples_2D;
        int _current_1D_dimension = 0, _current_2D_dimension = 0;
        RNG rng;
    };

}  // namespace Solstice