#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

class hittable_list : public hittable
{
public:
	hittable_list() = default;
	hittable_list(std::shared_ptr<hittable> object) { add(object); }
	~hittable_list() = default;

	void clear() { objects.clear(); }
	void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		hit_record temp_record;
		double closest_so_far = t_max; //射线在多个物体的命中最近的点
		bool hit_anything = false;

		for(const auto& object : objects)
		{
			if(object.get()->hit(r, t_min, closest_so_far, temp_record))
			{
				hit_anything = true;
				closest_so_far = temp_record.t;
				rec = temp_record;
			}
		}

		return hit_anything;
	}

private:
	std::vector<std::shared_ptr<hittable>> objects;
};

#endif
