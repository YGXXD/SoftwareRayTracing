#include <iostream>
#include "color.h"
#include "math_util.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

std::shared_ptr<hittable_list> random_scene()
{
	std::shared_ptr<hittable_list> world = std::make_shared<hittable_list>();

	auto mat_ground = std::make_shared<lambertian>(color(0.5, 0.5, 0.4));
	world->add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, mat_ground));

	for(int i = -11; i < 11; ++i)
	{
		for(int j = -11; j < 11; ++j)
		{
			auto choose_double = math::random_double();
			point3 center(i + 0.9 * math::random_double(), 0.2, j + 0.9 * math::random_double());

			if(math::length(center - point3(4, 0.2, 0)) > 0.9)
			{
				std::shared_ptr<material> sphere_material;

				if(choose_double < 0.8)
				{
					// diffuse
					auto albedo = math::random_vec3() * math::random_vec3();
					sphere_material = std::make_shared<lambertian>(albedo);
					world->add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if(choose_double < 0.95)
				{
					// metal
					auto albedo = math::random_vec3(0.5, 1);
					auto fuzz = math::random_double(0, 0.5);
					sphere_material = std::make_shared<metal>(albedo, fuzz);
					world->add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else 
				{
					// glass
					auto refrect_index = math::random_double(0.85, 1.5);
					sphere_material = std::make_shared<dielectric>(refrect_index);
					world->add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
			}

		}
	}

	auto material1 = std::make_shared<dielectric>(1.5);
    world->add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world->add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world->add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

color ray_color(const ray& r, hittable& world, int depth)
{
	hit_record rec;

	// 反射次数
	if(depth <= 0)
		return color(0, 0, 0);

	// 0.001在折射之后，光线在两个相切圆之间可能不准确
	if(world.hit(r, 0.001, math::infinity, rec))
	{
		// 材质散射
		ray scattered_ray;
		color attenuation;
		if(rec.mat_ptr->scatter(r, rec, attenuation, scattered_ray))
			return attenuation * ray_color(scattered_ray, world, depth - 1);

		return color(0, 0, 0);
	}

	double t = 0.5 * (r.direction().y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    // Image
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 1280;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500; //每个像素的随机采样次数
	const int max_depth = 80;

	// Camera
	point3 eye_pos = point3(13, 2, 3);
	point3 look_at = point3(0, 0, 0);
	double dist_to_focus = 10;
	double aperture_radius = 0.05;

	auto cam = std::make_shared<camera>(eye_pos, look_at, vec3(0, 1, 0), 30, aspect_ratio, aperture_radius, dist_to_focus);

	// World
	auto world = random_scene();

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for(int j = image_height-1; j >= 0; --j) 
	{
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < image_width; ++i) 
		{
			color pixel_color(0, 0, 0);
			// 随机采样
			for(int s = 0; s < samples_per_pixel; ++s)
			{
				double u = (i + math::random_double(-0.5, 0.5)) / (image_width - 1);
				double v = (j + math::random_double(-0.5, 0.5)) / (image_height - 1);
				ray pixel_ray = cam->get_ray(u, v);
				pixel_color += ray_color(pixel_ray, *world, max_depth); 
			}
			pixel_color *= 1.0 / (double)samples_per_pixel;

			write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
