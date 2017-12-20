#pragma once

#include "Maths.h"
#include "Solstice.h"

namespace Solstice {

    class RGBColour {
      public:
        float r, g, b;

      public:
        RGBColour() { r = g = b = 0; }

        inline RGBColour(float red, float green, float blue)
            : r(red), g(green), b(blue) {}

        inline RGBColour(float p_col) : r(p_col), g(p_col), b(p_col) {}

        RGBColour(const RGBColour& original) { *this = original; }

        inline RGBColour& operator=(const RGBColour& right) {
            r = right.r;
            g = right.g;
            b = right.b;

            return *this;
        }

        inline RGBColour& operator+=(const RGBColour& right) {
            *this = *this + right;
            return *this;
        }

        inline RGBColour& operator-=(const RGBColour& right) {
            *this = *this - right;
            return *this;
        }

        inline RGBColour& operator*=(const RGBColour& right) {
            *this = *this * right;
            return *this;
        }
        inline RGBColour& operator/=(const RGBColour& right) {
            *this = *this / right;
            return *this;
        }
        inline RGBColour& operator*=(float right) {
            *this = *this * right;
            return *this;
        }
        inline RGBColour& operator/=(float right) {
            *this = *this / right;
            return *this;
        }

        RGBColour operator+() const { return *this; }
        RGBColour operator-() const { return RGBColour(-r, -g, -b); }
        friend std::ostream& operator<<(std::ostream& os, const RGBColour& c) {
            os << "{ R: " << c.r << " G: " << c.g << " B: " << c.b << " }";
            return os;
        }
        inline friend RGBColour operator*(const RGBColour& c, float f) {
            return RGBColour(c.r * f, c.g * f, c.b * f);
        }

        inline friend RGBColour operator*(float f, const RGBColour& c) {
            return RGBColour(c.r * f, c.g * f, c.b * f);
        }
        inline friend RGBColour operator/(const RGBColour& c, float f) {
            return RGBColour(c.r / f, c.g / f, c.b / f);
        }
        inline friend RGBColour operator*(const RGBColour& c1,
                                          const RGBColour& c2) {
            return RGBColour(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
        }
        inline friend RGBColour operator/(const RGBColour& c1,
                                          const RGBColour& c2) {
            return RGBColour(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
        }
        inline friend RGBColour operator+(const RGBColour& c1,
                                          const RGBColour& c2) {
            return RGBColour(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
        }
        inline friend RGBColour operator-(const RGBColour& c1,
                                          const RGBColour& c2) {
            return RGBColour(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
        }

        inline friend bool operator==(const RGBColour& r1,
                                      const RGBColour& r2) {
            if (r1.r != r2.r) return false;
            if (r1.g != r2.g) return false;
            if (r1.b != r2.b) return false;
            return true;
        }

        inline bool IsBlack() const { return r == 0 && g == 0 && b == 0; }

        inline RGBColour Clamp(const float low = 0,
                               const float high = Maths::Infinity) {
            RGBColour c;
            c.r = Maths::Clamp(r, low, high);
            c.g = Maths::Clamp(g, low, high);
            c.b = Maths::Clamp(b, low, high);

            return c;
        }
    };

}  // namespace Solstice