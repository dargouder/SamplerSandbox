//
// Created by Darryl Gouder on 25/12/2017.
//

#include "HitableList.h"

using namespace Solstice;

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