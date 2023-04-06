#ifndef CAMERA_H
#define CAMERA_H

#include "math_util.h"
#include "ray.h"

class camera 
{
public:
	camera(point3 eye_pos, point3 look_at, vec3 v_up, double fov, double aspect_ratio, double aperture_radius, double focus_dist)
	{
		double theta = math::degrees_to_radians(fov);
		double h = tan(theta / 2);
		double viewport_height = 2.0 * h;
		double viewport_width = viewport_height * aspect_ratio;

		w = math::unit_vector(eye_pos - look_at);
		u = math::unit_vector(math::cross(v_up, w));
		v = math::cross(w, u);

		// focus_dist焦距, 近平面的距离
		origin = eye_pos;
		horizontal = viewport_width * u * focus_dist;
		vertical = viewport_height * v * focus_dist;
		lower_left_corner = origin - 0.5 * horizontal - 0.5 * vertical - w * focus_dist;

		// aperture_radius摄像机光圈, 模拟摄像机光圈聚焦
		lens_radius = aperture_radius;
	}

	~camera() = default;

	ray get_ray(double view_u, double view_v) const
	{
		vec3 rd = math::random_in_unit_disk() * lens_radius;
		vec3 eye_pos_offset = u * rd.x() + v * rd.y();
		return ray(origin + eye_pos_offset, lower_left_corner + view_u * horizontal + view_v * vertical - origin - eye_pos_offset);
	}

private:
	
	point3 origin; //相机原点
	point3 lower_left_corner; //视口左下角
	vec3 horizontal; //视口宽度
	vec3 vertical; //视口高度
	vec3 u, v, w; //相机空间
	
	double lens_radius; //相机光圈半径
};

#endif
