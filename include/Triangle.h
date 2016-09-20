#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Surface.h"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class Triangle : public Surface{
	Point3f _a, _b, _c;
public:
	Triangle();
	Triangle(Point3f a, Point3f b, Point3f c);
	virtual ~Triangle();
	virtual bool hit(const Ray& ray, float t0, float t1, HitRecord& rec);
	virtual Vector3f getNormal(Point3f p);
};

#endif