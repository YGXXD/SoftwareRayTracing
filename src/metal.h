#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "math_util.h"
#include "hittable.h"

class metal : public material
{
public:
	metal(const color& a) : albedo(a), fuzz(0) { } 
	metal(const color& a, double f) : albedo(a), fuzz(f) { }
	~metal() = default;
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflect_direction = math::reflect(r_in.direction(), rec.normal);
		scattered = ray(rec.p, reflect_direction + fuzz * math::random_in_unit_sphere());
		attenuation = albedo;

		return (math::dot(reflect_direction, rec.normal) > 0);
	}

private:
	color albedo; // 反照率
	double fuzz; //模糊系数
};

#endif
