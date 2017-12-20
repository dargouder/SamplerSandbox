#include "PixelSampler.h"

using namespace Solstice;

PixelSampler::PixelSampler(int64_t p_samples_per_pixel,
                           int p_n_sampled_dimensions)
    : Sampler(p_samples_per_pixel) {
    for (int i = 0; i < p_n_sampled_dimensions; ++i) {
        _samples_1D.push_back(std::vector<float>(p_samples_per_pixel));
        _samples_2D.push_back(std::vector<Point2f>(p_samples_per_pixel));
    }
}

PixelSampler::~PixelSampler() {}

bool PixelSampler::StartNextSample() {
    _current_1D_dimension = _current_2D_dimension = 0;
    return Sampler::StartNextSample();
}

float PixelSampler::Get1D() {
    if (_current_1D_dimension < _samples_1D.size()) {
        return _samples_1D[_current_1D_dimension++]
                          [_current_pixel_sample_index];
    } else {
        return rng.GetFloat();
    }
}

Point2f PixelSampler::Get2D() {
    if (_current_2D_dimension < _samples_2D.size()) {
        return _samples_2D[_current_2D_dimension++]
                          [_current_pixel_sample_index];
    } else {
        return Point2f(rng.GetFloat(), rng.GetFloat());
    }
}
