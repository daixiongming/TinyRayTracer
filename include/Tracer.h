#ifndef _TRACER_H_
#define _TRACER_H_

#include "Vector3.hpp"

class Tracer{
	int _pixel_nx, _pixel_ny;
	double _viewport_left, _viewport_right, _viewport_top, _viewport_bottom;
	Vector3d _camera_u, _camera_v, _camera_w;	// camera coordination
	Point3d _camera_pos;	// camera position
	bool _perspective;
	double _fd;		// focal distance
public:
	Tracer();
	void trace();
	void computeRay(int x, int y, Vector3d& direction, Vector3d& origin);
};

#endif