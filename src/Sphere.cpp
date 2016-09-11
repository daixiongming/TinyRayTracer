#include "Sphere.h"
#include "Vector3.hpp"

Sphere::Sphere()
:_c(0.0, 0.0, 0.0),
_r(1.0)
{

}

Sphere::Sphere(Point3d c, double r)
:_c(c), _r(r)
{

}

Sphere::~Sphere()
{

}

bool Sphere::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	Vector3d d = ray.direction;
	Point3d e = ray.origin;
	Point3d c = _c;
	double b = d * (e - c);
	double discriminant = b * b - (d * d)*((e - c) * (e - c) - _r * _r);
	return discriminant >= 0;
}