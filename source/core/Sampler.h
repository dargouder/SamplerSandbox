#pragma once
#include <cstdint> 
#include <vector>
#include "Random.h"
#include <algorithm>
#include "Maths.h"
#include "Vector3.h"

namespace Solstice {

	class Point2f {
	public:
		float x, y;

		Point2f() {
			x = y = 0.0f;
		}

		Point2f(float p_x, float p_y) : x(p_x), y(p_y)
		{

		}
	};


	class Point2i {
	public:
		int x;
		int y;

		Point2i() {
			x = y = 0;
		}

		Point2i(const int p_x, const int p_y) : x(p_x), y(p_y)
		{

		}
	};


	 class CameraSample {
	 public:
	 	Point2f m_pixel_sample;
	 	float m_time;
	 	Point2f m_lens_sample;
	 };

	 Vector3 UniformSampleSphere(const Point2f &u);


	 template <typename T>
	 void Shuffle(T* p_sample, int p_count, int p_n_dimensions, RNG& p_rng)
	 {
	 	for (int i = 0; i < p_count; ++i)
	 	{
	 		int other = i + p_rng.UniformUInt32(p_count - i);
	 		for (int j = 0; j < p_n_dimensions; ++j)
	 		{
	 			std::swap(p_sample[p_n_dimensions*i + j], p_sample[p_n_dimensions*other + j]);
	 		}
	 	}
	 }

	 void LatinHypercube(float* p_samples, int p_n_samples, int p_n_dim, RNG& p_rng);

	 class Sampler {
	 public:
	 	/* Sampler Interface */
	 	Sampler(int64_t p_samples_per_pixel) : m_samples_per_pixel(p_samples_per_pixel)
	 	{

	 	}

	 	CameraSample GetCameraSample(const Point2i& p_pixels);

	 	virtual void StartPixel(const Point2i& p);
	 	virtual bool StartNextSample();

	 	void Request1DArray(int n);
	 	void Request2DArray(int n);
		
	 	virtual float Get1D() = 0;
	 	virtual Point2f Get2D() = 0;

	 	const float* Get1DArray(int n);
	 	const Point2f* Get2DArray(int n);

	 	/* Sampler Public Data */
	 	const int64_t m_samples_per_pixel;

	 	/* Sampler Private Data */
	 private:
	 	size_t _array_1D_offset, _array2DOffset;

	 	/* Sampler Protected Data */
	 protected:
	 	std::vector<int> _samples_1D_array_sizes, _samples_2D_array_sizes;
	 	std::vector<std::vector<float>> _sample_array_1D;
	 	std::vector<std::vector<Point2f>> _sample_array_2D;

	 	Point2i _current_pixel;
	 	int64_t _current_pixel_sample_index;
	 };
}