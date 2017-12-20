#pragma once

#include "Hitable.h"
namespace Solstice {
	class Sphere : public Hitable {
		public:
		Vector3 centre;
		float radius;

		Sphere();
		Sphere(Vector3 cent, float r);

		virtual bool hit (const Ray& r, float t_min, float t_max, 
			HitRecord& record) const;
	};

}