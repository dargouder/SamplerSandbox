#include "Sphere.h"

using namespace Solstice;

Sphere::Sphere() {}

Sphere::Sphere(Vector3 cent, float r) : centre(cent), radius(r){};

bool Sphere::hit(const Ray& r, float t_min, float t_max,
                 HitRecord& record) const {
    Vector3 oc = r.origin - centre;

    float a = Vector3::DotProduct(r.direction, r.direction);
    float b = Vector3::DotProduct(oc, r.direction);
    float c = Vector3::DotProduct(oc, oc) - radius * radius;

    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;

        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = r.PointAlongRay(temp);
            record.normal = (record.p - centre) / radius;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;

        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = r.PointAlongRay(temp);
            record.normal = (record.p - centre) / radius;
            return true;
        }
    }
    return false;
}
