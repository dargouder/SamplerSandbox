#include "Camera.h"
#include "Hitable.h"


using namespace Solstice;

//Camera::Camera(Vector3 p_position, Vector3 p_direction, float p_fov, float p_aspect) :
//        position(p_position), direction(p_direction), fov(p_fov), aspect(p_aspect) {
//
//    up = Vector3(0, 1, 0);
//
//	uvw.InitFromWV(direction, up);
//
//    vh = tan( (fov * Maths::Pi/180.0f) /2.0f);
//
//    vw = vh * aspect;
//    std::cout << aspect << std::endl;
//    corner = uvw.W - uvw.U * vw - uvw.V * vh;
//    across = uvw.U * vw;
//    up = uvw.V * vh;
//
//}
Camera::Camera(Vector3 look_from, Vector3 look_at, Vector3 v_up, float vertical_fov,
	float aspect, float aperture, float focus_dist) {

	_lens_radius = aperture / 2.0f;

	float theta = vertical_fov * Maths::Pi / 180.0f;
	float half_height = tan(theta / 2.0f);
	float half_width = aspect * half_height;

	_position = look_from;
	
	_uvw.W = Vector3::UnitVector(look_from - look_at);
	_uvw.U = Vector3::UnitVector(Vector3::CrossProduct(v_up, _uvw.W));
	_uvw.V = Vector3::CrossProduct(_uvw.W, _uvw.U);

	_lower_left_corner = _position - _uvw.U*half_width*focus_dist - _uvw.V*half_height*focus_dist - _uvw.W*focus_dist;
	_horizontal = _uvw.U * half_width * 2 * focus_dist;
	_vertical = _uvw.V * half_height * 2 * focus_dist;

}

Ray Camera::generate_ray(const CameraSample& p_camera_sample){
	
	Vector3 rd = random_in_unit_disk() * _lens_radius;
	
	float s = p_camera_sample.m_pixel_sample.x;
	float t = p_camera_sample.m_pixel_sample.y;

	Vector3 offset = s * rd.x + t * rd.y;
	Vector3 target = _lower_left_corner + _horizontal*s + _vertical*t - _position - offset;
	//Vector3 target = corner + (across * u + up * v);
    return Ray(_position + offset, Vector3::UnitVector(target));
}