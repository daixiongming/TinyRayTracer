#include "Plane.h"

Plane::Plane()
:_norm(0.0, 0.0, 1.0), _d(0.0)
{
}

Plane::Plane(Vector3d norm, double d)
:_norm(norm.norm()), _d(d)
{

}

Plane::~Plane()
{

}

bool Plane::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	double t = (_d - ray.origin * _norm) / (ray.direction * _norm);
	if (t >= t0 && t <= t1){
		rec._t = t;
		rec._hit_point = ray.origin + t * ray.direction;
		return true;
	}
	else
		return false;
}

Vector3d Plane::getNorm(Point3d p)
{
	return _norm;
}