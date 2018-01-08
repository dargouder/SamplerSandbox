//
// Created by Darryl Gouder on 22/12/2017.
//

#pragma once

#include "Hitable.h"
#include "HitableList.h"

namespace Solstice
{
    class Scene
    {
      private:
        HitableList list;

      public:
        void BuildFloorScene();

        bool Intersect(const Ray& r, HitRecord& record);
    };
}  // namespace Solstice