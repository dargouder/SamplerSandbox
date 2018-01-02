#include "StratifiedSampler.h"

using namespace Solstice;

void StratifiedSample1D(float *p_sample, int p_n_samples, RNG &p_rng,
                        bool p_jitter) {
    float inv_n_samples = (float)1 / p_n_samples;
    for (int i = 0; i < p_n_samples; ++i) {
        float delta = p_jitter ? p_rng.GetFloat() : 0.5f;
        p_sample[i] =
            std::min((i + delta) * inv_n_samples, Maths::OneMinusEpsilon);
    }
}

void StratifiedSample2D(Point2f *p_sample, int p_nx, int p_ny, RNG &p_rng,
                        bool p_jitter) {
    float dx = (float)1 / p_nx;
    float dy = (float)1 / p_ny;
    for (int y = 0; y < p_ny; ++y) {
        for (int x = 0; x < p_nx; ++x) {
            float jx = p_jitter ? p_rng.GetFloat() : 0.5f;
            float jy = p_jitter ? p_rng.GetFloat() : 0.5f;

            p_sample->x = std::min((x + jx) * dx, Maths::OneMinusEpsilon);
            p_sample->y = std::min((y + jy) * dy, Maths::OneMinusEpsilon);
            ++p_sample;
        }
    }
}

void StratifiedSampler::StartPixel(const Point2i &p_pixel) {
    /* Generate single stratified samples for the pixel */
    for (size_t i = 0; i < samples_1D.size(); ++i) {
        StratifiedSample1D(&samples_1D[i][0],
                           _x_pixel_samples * _y_pixel_samples, rng,
                           _jitter_samples);
        Shuffle(&samples_1D[i][0], _x_pixel_samples * _y_pixel_samples, 1,
                rng);
    }
    for (size_t i = 0; i < samples_2D.size(); ++i) {
        StratifiedSample2D(&samples_2D[i][0], _x_pixel_samples,
                           _y_pixel_samples, rng, _jitter_samples);
        Shuffle(&samples_2D[i][0], _x_pixel_samples * _y_pixel_samples, 1,
                rng);
    }
    /* Generate arrays of stratified samples for the pixel */
    for (size_t i = 0; i < _samples_1D_array_sizes.size(); ++i) {
        for (int64_t j = 0; j < m_samples_per_pixel; ++j) {
            int count = _samples_1D_array_sizes[i];
            StratifiedSample1D(&_sample_array_1D[i][j * count], count, rng,
                               _jitter_samples);
            Shuffle(&_sample_array_1D[i][0], count, 1, rng);
        }
    }
    for (size_t i = 0; i < _samples_2D_array_sizes.size(); ++i) {
        for (int64_t j = 0; j < m_samples_per_pixel; ++j) {
            int count = _samples_2D_array_sizes[i];
            LatinHypercube(&(_sample_array_2D[i][j * count]).x, count, 2, rng);
        }
    }
    PixelSampler::StartPixel(p_pixel);
}
