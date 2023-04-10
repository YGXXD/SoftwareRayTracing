#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "vec3.h"

namespace math
{
	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = 3.1415926535897932385;

	inline double degrees_to_radians(double degrees)
	{
	    return degrees * pi / 180.0;
	}

	inline double random_double()
	{
		// 随机范围[0, 1)
		return rand() / (RAND_MAX + 1.0);
	}

	inline double random_double(double min, double max)
	{
		//随机范围[min, max)
		return min + (max - min) * random_double();
	}

	inline double clamp(double x, double min, double max)
	{
		if(x < min) return min;
		if(x > max) return max;
		return x;
	}

	inline bool near_zero(double x)
	{
		const double s = 1e-8;
		return fabs(x) < s;
	}

	inline bool near_zero(const vec3& v)
	{
		const double s = 1e-8;
		return (fabs(v.x()) < s) && (fabs(v.y()) < s) && (fabs(v.z() < s));
	}

	inline double length_squared(const vec3& v) 
	{
		return v.x() * v.x() + v.y() * v.y() + v.z() * v.z();
	}

	inline double length(const vec3& v)
   	{
		return sqrt(length_squared(v));
	}

	inline double dot(const vec3 &u, const vec3 &v) 
	{
	    return u.x() * v.x()
	         + u.y() * v.y()
	         + u.z() * v.z();
	}
	
	inline vec3 cross(const vec3 &u, const vec3 &v) 
	{
	    return vec3(u.y() * v.z() - u.z() * v.y(),
	                u.z() * v.x() - u.x() * v.z(),
	                u.x() * v.y() - u.y() * v.x());
	}

	inline vec3 unit_vector(const vec3& v) 
	{
    	return v / length(v);
	}

	inline vec3 random_vec3()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline vec3 random_vec3(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	inline vec3 random_unit_vector()
	{
		double theta = random_double(0, pi);
		double phi = random_double(0, 2 * pi);
		
		return vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
	}

	inline vec3 random_in_unit_sphere() // 单位球内的向量
	{
		double r = cbrt(random_double());

		return r * random_unit_vector();
	}

	inline vec3 random_in_hemisphere(const vec3& normal)
	{
		vec3 in_unit_sphere = random_in_unit_sphere();
		if(dot(in_unit_sphere, normal) > 0)
		{
			return in_unit_sphere;
		}
		
		return -in_unit_sphere;
	}

	inline vec3 random_in_unit_disk() //单位圆盘内向量
	{
		double theta = random_double(0, 2 * pi);
		double r = sqrt(random_double());

		return vec3(cos(theta), sin(theta), 0);
	}

	inline vec3 reflect(const vec3& r_direction, const vec3& normal)
	{
		return r_direction - 2 * dot(r_direction, normal) * normal;
	}

	inline vec3 refrect(const vec3& r_direction, const vec3& normal, double refrect_ratio)
	{
		// 计算入射光线与法线夹角余弦值
		double cos_theta = fmin(dot(-r_direction, normal), 1.0);
		// 计算折射光线与法线垂直的分量
		vec3 r_out_perp = refrect_ratio * (r_direction + cos_theta * normal);
		// 计算折射光线与法线平行的分量
		vec3 r_out_parallel = (-normal) * sqrt(1.0 - length_squared(r_out_perp)); 

		return r_out_perp + r_out_parallel;
	}
}

#endif
