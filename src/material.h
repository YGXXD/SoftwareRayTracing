#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"

struct hit_record;

class material
{
public:
	// 光线散射
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
	virtual ~material()	= default;
};


#endif
