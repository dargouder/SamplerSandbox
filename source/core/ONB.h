#pragma once

#include "Vector3.h"

namespace Solstice
{
    class OrthonormalBasis
    {
      private:
        static const float Epsilon;

      public:
        Vector3 U, V, W;

      public:
        OrthonormalBasis() {}
        OrthonormalBasis(const Vector3& a, const Vector3& b, const Vector3& c)
        {
            U = a;
            V = b;
            W = c;
        }

        void InitFromWV(const Vector3& e, const Vector3& v);

        friend std::ostream& operator<<(std::ostream& os,
                                        const OrthonormalBasis& o)
        {
            os << "ONB {" << std::endl;
            os << "\tU: " << o.U << std::endl;
            os << "\tV: " << o.V << std::endl;
            os << "\tW: " << o.W << std::endl;
            os << "}";
            return os;
        }
    };
}  // namespace Solstice
