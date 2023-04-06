#ifndef RAY_H
#define RAY_H

#include "math_util.h"

class ray
{
public:
	ray() = default;
	ray(const point3& origin, const vec3& origin_to_target) : orig(origin), dir(math::unit_vector(origin_to_target)) { }
	~ray() = default;

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
	point3 at(double t) const { return orig + t * dir; } //射线的终点为P(t) = O + D * t

private:
	point3 orig; // 原点
	vec3 dir; // 方向
};

#endif
