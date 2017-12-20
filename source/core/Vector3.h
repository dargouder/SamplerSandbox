#pragma once

#include <immintrin.h>
#include <iostream>
#include <cmath>

namespace Solstice {
    class Vector3 {
        
    public:
        
        union{
            struct  { float x, y, z, w; };
            float element[4];
        };

    public:
        Vector3() { x = y = z = 0.0f;  }

        inline Vector3(float p_x, float p_y, float p_z) {
            element[0] = p_x;
            element[1] = p_y;
            element[2] = p_z;
        }
        
        inline Vector3(float p_num) : x(p_num), y(p_num), z(p_num) 
        {
        }
        
        Vector3(const Vector3& p_v) { *this = p_v; }
        
        inline float operator[](int p_index) const {
            return element[p_index];
        }
        inline float& operator[](int p_index) {
            return element[p_index];
        }
        
        inline const Vector3& operator+() const{
            return *this;
        }
        inline Vector3 operator-() const{
            return Vector3(-x, -y, -z);
        }

        inline friend bool operator==(const Vector3& v1, const Vector3& v2){
            if (v1.x != v2.x) return false;
            if (v1.y != v2.y) return false;
            if (v1.z != v2.z) return false;
            return true;
        }
        inline friend bool operator!=(const Vector3& v1, const Vector3& v2){
            return !(v1 == v2);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector3& t){
            os << "{ " << t.x << ", " << t.y << ", " << t.z << " }";

            return os;
        }
        
        inline friend Vector3 operator+(const Vector3& v1, const Vector3& v2){
#ifdef AVX_ENABLED
            Vector3 res;
            __m128 i_v1, i_v2, i_v_res;

            i_v1 = _mm_load_ps(v1.element);
            i_v2 = _mm_load_ps(v2.element);
            i_v_res = _mm_add_ps(i_v1, i_v2);

            _mm_store_ps(res.element, i_v_res);
            return res;

#else
            return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
 #endif
        }

        inline friend Vector3 operator-(const Vector3& v1, const Vector3& v2){
#ifdef AVX_ENABLED
            Vector3 res;
            __m128 i_v1, i_v2, i_v_res;

            i_v1 = _mm_load_ps(v1.element);
            i_v2 = _mm_load_ps(v2.element);
            i_v_res = _mm_sub_ps(i_v1, i_v2);

            _mm_store_ps(res.element, i_v_res);
            return res;

#else
            return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
#endif
        }

        
        inline friend Vector3 operator/(const Vector3& v1, float t){

#ifdef AVX_ENABLED
            Vector3 res;
            __m128 i_v1, i_v_res, i_t;

            i_v1 = _mm_load_ps(v1.element);
            i_t = _mm_set_ps1(t);
            i_v_res = _mm_div_ps(i_v1, i_t);

            _mm_store_ps(res.element, i_v_res);
            return res;

#else
            return Vector3(v1.x / t, v1.y / t, v1.z / t);
#endif
        }

        inline float SquaredLength() const {
            return x*x + y*y + z*z;
        }
        inline float Length() const {
            return sqrt( SquaredLength() );
        }

        inline static Vector3 UnitVector(const Vector3& p_v){
            float length = p_v.Length();
            return p_v / length;
        }
        
        inline friend Vector3 operator*(const Vector3& v1, float t){


#ifdef AVX_ENABLED
            Vector3 res;
            __m128 i_v1, i_v_res, i_t;

            i_v1 = _mm_load_ps(v1.element);
            i_t = _mm_set_ps1(t);
            i_v_res = _mm_mul_ps(i_v1, i_t);

            _mm_store_ps(res.element, i_v_res);
            return res;

#else
            return Vector3(v1.x * t, v1.y * t, v1.z * t);
#endif
        }

        inline static float DotProduct(const Vector3& v1, const Vector3& v2){
            return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
        }

        inline static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2){
            float x = (v1.y * v2.z) - (v1.z * v2.y);
            float y = (v1.z * v2.x) - (v1.x * v2.z);
            float z = (v1.x * v2.y) - (v1.y * v2.x);
            return Vector3(x,y,z);
        }

		inline static Vector3 Reflect(const Vector3& v, const Vector3& n) {
			return v - n * 2 * Vector3::DotProduct(v, n);
		}

		inline static bool Refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted)
		{
			Vector3 uv = Vector3::UnitVector(v);
			float dt = Vector3::DotProduct(uv, n);
			float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);

			if (discriminant > 0) {
				refracted = (uv - n*dt) * ni_over_nt - n*sqrt(discriminant);
				return true;
			}
			else {
                return false;
			}
		}
    };
}
