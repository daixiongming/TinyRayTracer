#include "Plane.h"

Plane::Plane()
:_norm(0.0, 0.0, 1.0), _point(0.0, 0.0, 0.0)
{
}

Plane::Plane(Vector3d norm, Point3d point)
:_norm(norm), _point(point)
{

}

Plane::~Plane()
{

}

bool Plane::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	double t = -(_norm * (ray.origin - _point)) / (_norm * ray.direction);
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