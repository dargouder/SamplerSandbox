#pragma once

#include "ONB.h"
#include "Ray.h"
#include "Sampler.h"

namespace Solstice {

    class Camera {
      private:
        Vector3 _lower_left_corner;
        Vector3 _horizontal;
        Vector3 _vertical;

        Vector3 _position;
        OrthonormalBasis _uvw;
        float _lens_radius;

      public:
        Camera(Vector3 look_from, Vector3 look_at, Vector3 v_up,
               float vertical_fov, float aspect, float aperture,
               float focus_dist);

        Ray generate_ray(const CameraSample& p_camera_sample);

        friend std::ostream& operator<<(std::ostream& os, const Camera& c) {
            os << "camera {" << std::endl;
            os << "\tposition: " << c._position << std::endl;
            os << "}";
            return os;
        }
    };

}  // namespace Solstice