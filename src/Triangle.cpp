#include "Triangle.h"

Triangle::Triangle()
:_a(1.0f, 0.0f, 0.0f), _b(0.0f, 0.0f, 0.0f), _c(0.0f, 1.0f, 0.0f)
{

}

Triangle::Triangle(Point3f a, Point3f b, Point3f c)
: _a(a), _b(b), _c(c)
{

}

Triangle::~Triangle()
{

}

bool Triangle::hit(const Ray& ray, float t0, float t1, HitRecord& rec)
{
	float a = _a._x - _b._x;
	float b = _a._y - _b._y;
	float c = _a._z - _b._z;
	float d = _a._x - _c._x;
	float e = _a._y - _c._y;
	float f = _a._z - _c._z;
	float g = ray.direction._x;
	float h = ray.direction._y;
	float i = ray.direction._z;
	float j = _a._x - ray.origin._x;
	float k = _a._y - ray.origin._y;
	float l = _a._z - ray.origin._z;

	float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	float t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;
	if (t < t0 || t > t1)
		return false;

	float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / M;
	if (gamma < 0.0f || gamma > 1.0f)
		return false;

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
	if (beta < 0.0f || beta > 1 - gamma)
		return false;

	rec._t = t;
	rec._hit_point = ray.origin + t * ray.direction;
	return true;
}

Vector3f Triangle::getNormal(Point3f p)
{
	return ((_a - _c).cross(_b - _a)).normal();
}