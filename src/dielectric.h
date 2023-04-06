#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "hittable.h"
#include "math_util.h"

class dielectric : public material
{
public:
	dielectric(double index_of_refrect) : refrect_index(fmax(index_of_refrect, 1e-8)) { }
	~dielectric() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1, 1, 1);
		// 介质折射率比
		double refrect_ratio = rec.front_face ? (1.0 / refrect_index) : refrect_index;

		double cos_theta = fmin(math::dot(-r_in.direction(), rec.normal), 1.0);
		double sin_theta = sqrt(1 - cos_theta * cos_theta); 

		// N * sin(a) = N' * sin(a')
		// N * sin(a) / N' = sin(a')

		// refrect_ratio * sin_theta > 1 将会发生全反射

		vec3 out_direction;
		if(math::near_zero(sin_theta) || refrect_ratio * sin_theta > 1 || reflectance(cos_theta, refrect_ratio) > math::random_double())
		{
			out_direction = math::reflect(r_in.direction(), rec.normal);
		}
		else
	   	{
			out_direction = math::refrect(r_in.direction(), rec.normal, refrect_ratio);	
		}

		scattered = ray(rec.p, out_direction);

		return true;
	}
private:

	static double reflectance(double cosine, double refrect_ratio)
	{
		double r0 = (1 - refrect_ratio) / (1 + refrect_ratio);	
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

	double refrect_index; // 折射率
};

#endif
