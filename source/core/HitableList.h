#pragma once

#include <vector>
#include <memory>
#include "Hitable.h"

namespace Solstice {
	class HitableList : public Hitable {

	public:
		std::vector<std::unique_ptr<Hitable>> list;

		HitableList() {}

		virtual bool hit(const Ray& r, float t_min, float t_max, 
		HitRecord& record) const;

	};

	bool HitableList::hit(const Ray& ray, float tmin, float tmax, HitRecord& rec) const {
		HitRecord temp_rec;

		bool hit_anything = false;

		double closest_so_far = tmax;

		for(auto& hitable_object : list) {
			if(hitable_object->hit(ray, tmin, closest_so_far,temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}
}