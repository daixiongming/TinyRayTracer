#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Ray.hpp"
#include "HitRecord.hpp"

class Surface{
public:
	Surface();
	virtual ~Surface();
	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec) =0;
	
};

#endif