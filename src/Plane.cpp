#include "Plane.h"

Plane::Plane()
:_normal(0.0f, 0.0f, 1.0f), _d(0.0f)
{
}

Plane::Plane(Vector3f normal, float d)
:_normal(normal.normal()), _d(d)
{

}

Plane::~Plane()
{

}

bool Plane::hit(const Ray& ray, float t0, float t1, HitRecord& rec)
{
	float t = (_d - ray.origin * _normal) / (ray.direction * _normal);
	if (t >= t0 && t <= t1){
		rec._t = t;
		rec._hit_point = ray.origin + t * ray.direction;
		return true;
	}
	else
		return false;
}

Vector3f Plane::getNormal(Point3f p)
{
	return _normal;
}