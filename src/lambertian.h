#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "math_util.h"
#include "hittable.h"

class lambertian : public material
{
public:
	lambertian(const color& a) : albedo(a) { }
	~lambertian() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		// 漫反射, 反射光随机
		vec3 scatter_direction = rec.normal + math::random_unit_vector();

		// 随机后direction向量为0
		if(math::near_zero(scatter_direction))
		{
			scatter_direction = rec.normal;
		}

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	}

private:
	color albedo; // 反照率
};

#endif
