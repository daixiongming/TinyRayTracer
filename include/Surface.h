#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Ray.hpp"
#include "HitRecord.hpp"

class Surface{
public:
	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec);
	
};

#endif