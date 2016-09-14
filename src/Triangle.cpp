#include "Triangle.h"

Triangle::Triangle()
:_a(1.0, 0.0, 0.0), _b(0.0, 0.0, 0.0), _c(0.0, 1.0, 0.0)
{

}

Triangle::Triangle(Point3d a, Point3d b, Point3d c)
: _a(a), _b(b), _c(c)
{

}

Triangle::~Triangle()
{

}

bool Triangle::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	double a = _a._x - _b._x;
	double b = _a._y - _b._y;
	double c = _a._z - _b._z;
	double d = _a._x - _c._x;
	double e = _a._y - _c._y;
	double f = _a._z - _c._z;
	double g = ray.direction._x;
	double h = ray.direction._y;
	double i = ray.direction._z;
	double j = _a._x - ray.origin._x;
	double k = _a._y - ray.origin._y;
	double l = _a._z - ray.origin._z;

	double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	double t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;
	if (t < t0 || t > t1)
		return false;

	double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / M;
	if (gamma < 0 || gamma > 1)
		return false;

	double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
	if (beta < 0 || beta > 1 - gamma)
		return false;

	rec._t = t;
	rec._hit_point = ray.origin + t * ray.direction;
	return true;
}

Vector3d Triangle::getNorm(Point3d p)
{
	return ((_a - _c).cross(_b - _a)).norm();
}