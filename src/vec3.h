#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 
{
public:
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
	~vec3() = default;

	friend std::ostream& operator<<(std::ostream &out, const vec3 &v); 	
	friend vec3 operator+(const vec3 &u, const vec3 &v);
	friend vec3 operator-(const vec3 &u, const vec3 &v);
  	friend vec3 operator*(const vec3 &u, const vec3 &v);
	friend vec3 operator*(double t, const vec3 &v); 


    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
   
  	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3 &v) 
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t) 
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) 
	{
 		return *this *= 1/t;
	}


private:
	double e[3];
};

// 定义Vec3其它类型
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color
					   
// vec3的运算符重载
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) 
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) 
{
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) 
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t) 
{
    return (1/t) * v;
}

#endif
