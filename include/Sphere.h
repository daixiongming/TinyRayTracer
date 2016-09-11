#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Surface.h"

class Sphere : public Surface{
public:
	Point3d _c;
	double _r;
public:
	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec);
};

#endif