#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include "Vector3.hpp"

class HitRecord{
public:
	int _surface;	// which surface (surface id)
	float _t;	// where hit
	Point3f _hit_point;
};

#endif