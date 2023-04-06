#ifndef COLOR_H
#define COLOR_H

#include "math_util.h"
#include <iostream>

inline void write_color(std::ostream &out, color pixel_color)
{
	// 伽马矫正
	double r = sqrt(pixel_color.x());
	double g = sqrt(pixel_color.y());
	double b = sqrt(pixel_color.z());

	// 输出颜色值
    out << static_cast<int>(256.0 * math::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256.0 * math::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256.0 * math::clamp(b, 0.0, 0.999)) << '\n';
}

#endif
