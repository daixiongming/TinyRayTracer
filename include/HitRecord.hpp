#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include "Vector3.hpp"

class HitRecord{
public:
	int _surface;	// which surface (surface id)
	double _t;	// where hit
	Point3d _hit_point;
};

#endif