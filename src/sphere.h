#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
	sphere() = default;
	sphere(point3 center, double radius, std::shared_ptr<material> mat) : cen(center), rad(radius), mat_ptr(mat) { };
	~sphere() = default;

	point3 center() const { return cen; }
	double radius() const { return rad; }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		// 圆心为C, 射线 P(t) = O + t * D
		// 射线与圆相交, 得 (P(t) - C) * (P(t) - C) = r * r
		// 化简得 D^2 * t^2 + 2 * D * (O - C) * t + (O - C)^2 - r^2 = 0
		// 有交点的情况下上述登时有解, b^2 - 4 * a * c > 0
	
		vec3 oc = r.origin() - cen;
		double half_b = math::dot(oc, r.direction());
		double a = math::dot(r.direction(), r.direction());
		double c = math::dot(oc, oc) - rad * rad;
		double discriminant = half_b * half_b - a * c; 
	 	if(discriminant < 0)
			return false;
	
		double sqrt_discriminant = sqrt(discriminant);
		
		// 计算射线与球交点与射线源点距离最近的点
		// 大:(- half_b + sqrt(discriminant)) / a
		// 小:(- half_b - sqrt(discriminant)) / a
		
		double root = (- half_b - sqrt(discriminant)) / a;
		if(root < t_min || root > t_max)
		{
			root = (- half_b + sqrt(discriminant)) / a;
			if(root < t_min || root > t_max)
				return false;
		}	
		
		rec.t = root;
		rec.p = r.at(root);
		vec3 outward_normal = (rec.p - cen) / rad;
		rec.set_front_normal(r, outward_normal);
		rec.mat_ptr = mat_ptr;

		return true;
	}

private:
	point3 cen; //圆心
	double rad; //半径
	
	std::shared_ptr<material> mat_ptr; // 材质
};

#endif
