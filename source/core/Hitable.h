#pragma once
#include <memory>
#include <random>
#include "Random.h"
#include "Ray.h"
#include "Sampler.h"

namespace Solstice
{
    class Material;

    static RNG rng;

    static Vector3 random_in_unit_sphere()
    {
        Vector3 p;
        do
        {
            p = Vector3(rng.GetFloat(), rng.GetFloat(), rng.GetFloat()) * 2.0f -
                Vector3(1.0f);

        } while (p.SquaredLength() >= 1.0f);
        return p;
    }

    static Vector3 random_in_unit_disk()
    {
        Vector3 p;
        do
        {
            p = Vector3(rng.GetFloat(), rng.GetFloat(), rng.GetFloat()) * 2.0f -
                Vector3(1.0f, 1.0f, 0.0f);
            // p = Vector3(0.5);
        } while (Vector3::DotProduct(p, p) >= 1.0f);
        return p;
    }
    class HitRecord
    {
      public:
        float t;
        Vector3 p;
        Vector3 normal;
    };

    class Hitable
    {
      public:
        virtual bool hit(const Ray& r, float t_min, float t_max,
                         HitRecord& record) const = 0;
    };

}  // namespace Solstice