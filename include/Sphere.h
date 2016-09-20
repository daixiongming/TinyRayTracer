#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Surface.h"

class Sphere : public Surface{
public:
	Point3f _c;
	float _r;
public:
	Sphere();
	Sphere(Point3f c, float r);
	virtual ~Sphere();
	virtual bool hit(const Ray& ray, float t0, float t1, HitRecord& rec);
	virtual Vector3f getNormal(Point3f p);
};

#endif