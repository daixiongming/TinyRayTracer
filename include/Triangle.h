#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Surface.h"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class Triangle : public Surface{
	Point3d _a, _b, _c;
public:
	Triangle();
	Triangle(Point3d a, Point3d b, Point3d c);
	virtual ~Triangle();
	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec);
	virtual Vector3d getNorm(Point3d p);
};

#endif