#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include "Surface.h"
#include "Vector3.hpp"

class Polygon : public Surface{
	std::vector<Vector3f> _points;

	int _index_u, _index_v;

	void preProjection();

public:
	//Polygon();
	Polygon(const std::vector<Point3f>& points);
	virtual ~Polygon();
	virtual bool hit(const Ray& ray, float t0, float t1, HitRecord& rec);
	virtual Vector3f getNormal(Point3f p);
};

#endif
