#include "PixelSampler.h"

using namespace Solstice;

PixelSampler::PixelSampler(int64_t p_samples_per_pixel,
                           int p_n_sampled_dimensions)
    : Sampler(p_samples_per_pixel) {
    for (int i = 0; i < p_n_sampled_dimensions; ++i) {
        samples_1D.push_back(std::vector<float>(p_samples_per_pixel));
        samples_2D.push_back(std::vector<Point2f>(p_samples_per_pixel));
    }
}

PixelSampler::~PixelSampler() {}

bool PixelSampler::StartNextSample() {
    current_1D_dimension = current_2D_dimension = 0;
    return Sampler::StartNextSample();
}

float PixelSampler::Get1D() {
    if (current_1D_dimension < samples_1D.size()) {
        return samples_1D[current_1D_dimension++]
                          [_current_pixel_sample_index];
    } else {
        return rng.GetFloat();
    }
}

Point2f PixelSampler::Get2D() {
    if (current_2D_dimension < samples_2D.size()) {
        return samples_2D[current_2D_dimension++]
                          [_current_pixel_sample_index];
    } else {
        return Point2f(rng.GetFloat(), rng.GetFloat());
    }
}
