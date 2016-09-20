#include "Sphere.h"
#include "Vector3.hpp"

Sphere::Sphere()
:_c(0.0f, 0.0f, 0.0f),
_r(1.0f)
{

}

Sphere::Sphere(Point3f c, float r)
:_c(c), _r(r)
{

}

Sphere::~Sphere()
{

}

bool Sphere::hit(const Ray& ray, float t0, float t1, HitRecord& rec)
{
	Vector3f d = ray.direction;
	Point3f e = ray.origin;
	Point3f c = _c;
	float b = d * (e - c);
	float discriminant = b * b - (d * d)*((e - c) * (e - c) - _r * _r);
	if (discriminant >= 0){
		float t = (-b - sqrt(discriminant)) / (d * d);
		if (t >= t0 && t <= t1){
			rec._t = t;
			rec._hit_point = ray.origin + t * ray.direction;
			return true;
		}
	}
	return false;
}

Vector3f Sphere::getNormal(Point3f p)
{
	return (p - _c).normal();
}