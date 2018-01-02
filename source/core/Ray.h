#pragma once

#include "Vector3.h"
#include "Maths.h"

namespace Solstice{
	class Ray{
	public:
		Vector3 origin;
		Vector3 direction;
		/* Mutable so they can be modified when intersection rays are const but need to update the hit point using the tmax. */
		mutable float tmin;
		mutable float tmax;
		int depth;
	public:
		Ray() {
			tmin = 0.0f;
			tmax = Maths::Infinity;
			depth = 0;
		}

		Ray(const Vector3& p_origin, const Vector3& p_direction) : origin(p_origin), direction(p_direction){	
			tmin = 0.0f;
            tmax = Maths::Infinity;
			depth = 0;
		}

		Ray(const Vector3& p_origin, const Vector3& p_direction, const Ray& parent, const float p_min, 
			const float p_max = Maths::Infinity) : origin(p_origin), direction(p_direction),
			tmin(p_min), tmax(p_max), depth(parent.depth+1)
		{
		}

		Ray(const Vector3& p_origin, const Vector3& p_direction, float p_start, 
			float p_end = Maths::Infinity, int p_d = 0) : 
				origin(p_origin), direction(p_direction), tmin(p_start), tmax(p_end), depth(p_d){

		}
		
		Ray(const Ray& p_ray) {
			*this = p_ray;
		}

	
		Vector3 PointAlongRay(float p_t) const {
			return origin + direction * p_t;
		}

	};

	inline std::ostream& operator<<(std::ostream& p_os, const Ray& p_ray){
		p_os << "(" << p_ray.origin << ") + t(" << p_ray.direction << ")";
		return p_os;
	}
}
