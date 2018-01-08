
#include "Sampler.h"

namespace Solstice
{
    void LatinHypercube(float* p_samples, int p_n_samples, int p_n_dim,
                        RNG& p_rng)
    {
        /* Generate LHS samples along diagonal */
        float inv_n_samples = (float)1 / p_n_samples;
        for (int i = 0; i < p_n_samples; ++i)
        {
            for (int j = 0; j < p_n_dim; ++j)
            {
                float sj = (i + (p_rng.GetFloat())) * inv_n_samples;
                p_samples[p_n_dim * i + j] =
                    std::min(sj, Maths::OneMinusEpsilon);
            }
        }
        /* Permute LHS samples in each dimension */
        for (int i = 0; i < p_n_dim; ++i)
        {
            for (int j = 0; j < p_n_samples; ++j)
            {
                int other = j + p_rng.UniformUInt32(p_n_samples - j);
                std::swap(p_samples[p_n_dim * j + i],
                          p_samples[p_n_dim * other + i]);
            }
        }
    }

    Vector3 UniformSampleSphere(const Point2f& u)
    {
        float z = 1 - 2 * u.x;
        float r = std::sqrt(std::max((float)0, (float)1 - z * z));
        float phi = 2 * Maths::Pi * u.y;
        return Vector3(r * std::cos(phi), r * std::sin(phi), z);
    }

    CameraSample Sampler::GetCameraSample(const Point2i& p_pixels)
    {
        CameraSample cs;
        Point2f p = Get2D();
        cs.m_pixel_sample = Point2f(p.x, p.y);
        return cs;
    }

    void Sampler::StartPixel(const Point2i& p_current_pixel)
    {
        _current_pixel = p_current_pixel;
        _current_pixel_sample_index = 0;

        /* Reset array offsets for next pixel sample */
        _array_1D_offset = _array2DOffset = 0;
    }

    bool Sampler::StartNextSample()
    {
        /* Reset array offsets for next pixel */
        _array_1D_offset = _array2DOffset = 0;
        return ++_current_pixel_sample_index < m_samples_per_pixel;
    }

    void Sampler::Request1DArray(int n)
    {
        _samples_1D_array_sizes.push_back(n);
        _sample_array_1D.push_back(std::vector<float>(n * m_samples_per_pixel));
    }

    void Sampler::Request2DArray(int n)
    {
        _samples_2D_array_sizes.push_back(n);
        _sample_array_2D.push_back(
            std::vector<Point2f>(n * m_samples_per_pixel));
    }

    const float* Sampler::Get1DArray(int n)
    {
        if (_array_1D_offset == _sample_array_1D.size())
        {
            return nullptr;
        }

        return &_sample_array_1D[_array_1D_offset++]
                                [_current_pixel_sample_index * n];
    }

    const Point2f* Sampler::Get2DArray(int n)
    {
        if (_array_1D_offset == _sample_array_2D.size())
        {
            return nullptr;
        }

        return &_sample_array_2D[_array_1D_offset++]
                                [_current_pixel_sample_index * n];
    }

}  // namespace Solstice