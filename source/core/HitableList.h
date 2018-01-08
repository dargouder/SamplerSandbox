#pragma once

#include <memory>
#include <vector>
#include "Hitable.h"

namespace Solstice
{
    class HitableList : public Hitable
    {
      public:
        std::vector<std::unique_ptr<Hitable>> list;

        HitableList() {}

        virtual bool hit(const Ray& r, float t_min, float t_max,
                         HitRecord& record) const;
    };

}  // namespace Solstice