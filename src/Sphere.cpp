#include "Sphere.h"
#include "Vector3.hpp"

bool Sphere::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	Vector3d d = ray.direction;
	Point3d e = ray.origin;
	Point3d c = _c;
	float b = d * (e - c);
	double discriminant = b * b - (d * d)*((e - c) * (e - c) - _r * _r);
	if (discriminant >= 0)
		return true;
}