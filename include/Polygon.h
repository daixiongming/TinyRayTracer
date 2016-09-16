#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include "Surface.h"
#include "Vector3.hpp"

class Polygon : public Surface{
	std::vector<Vector3d> _points;

	int _index_u, _index_v;

	void preProjection();

public:
	//Polygon();
	Polygon(const std::vector<Point3d>& points);
	virtual ~Polygon();
	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec);
	virtual Vector3d getNorm(Point3d p);
};

#endif
