#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Surface.h"

class Tracer{
	int _pixel_nx, _pixel_ny;
	double _viewport_left, _viewport_right, _viewport_top, _viewport_bottom;
	Vector3d _camera_u, _camera_v, _camera_w;	// camera coordination
	Point3d _camera_pos;	// camera position
	bool _perspective;
	double _fd;		// focal distance

	std::vector<Surface*> _models;
public:
	Tracer();
	void buildWorld();
	void trace();
	Ray computeRay(int x, int y);
};

#endif