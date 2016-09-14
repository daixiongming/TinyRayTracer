#ifndef _PLANE_H_
#define _PLANE_H_

#include "Surface.h"
#include "Vector3.hpp"

class Plane : public Surface{
	Vector3d _norm;
	double _d;	// the distance from O to plane

public:
	Plane();
	Plane(Vector3d norm, double d);
	virtual ~Plane();

	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec);
	virtual Vector3d getNorm(Point3d p);
};

#endif