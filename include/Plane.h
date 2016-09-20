#ifndef _PLANE_H_
#define _PLANE_H_

#include "Surface.h"
#include "Vector3.hpp"

class Plane : public Surface{
	Vector3f _normal;
	float _d;	// the distance from O to plane

public:
	Plane();
	Plane(Vector3f normal, float d);
	virtual ~Plane();

	virtual bool hit(const Ray& ray, float t0, float t1, HitRecord& rec);
	virtual Vector3f getNormal(Point3f p);
};

#endif