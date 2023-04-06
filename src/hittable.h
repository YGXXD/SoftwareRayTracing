#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class material;

struct hit_record
{
	point3 p; //命中点
	vec3 normal; //命中的法线
	double t; //射线的t系数值
	bool front_face; //射线源点与表面的位置，点是否在法线朝前的位置
	std::shared_ptr<material> mat_ptr; //材质指针

	inline void set_front_normal(const ray& r, const vec3& outward_normal)
	{
		front_face = math::dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : - outward_normal;
	}
};

class hittable 
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual ~hittable() = default;
};

#endif
