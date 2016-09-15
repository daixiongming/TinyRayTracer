#ifndef _TRACER_H_
#define _TRACER_H_

#include <string>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "World.h"

class Tracer{
	friend class Parser;

	int _pixel_nx, _pixel_ny;
	double _viewport_left, _viewport_right, _viewport_top, _viewport_bottom;
	Vector3d _camera_u, _camera_v, _camera_w;	// camera coordination
	Point3d _camera_pos;	// camera position
	bool _perspective;
	double _fd;		// focal distance

	Color _ambient_light;
	Color _background;
	
	int _mirror_recursion_depth;
	bool _depth_mode;

	World* _world;

public:
	Tracer(World* world);
	void trace(const std::string& output);
	void setWorld(World* world);
	Color rayColor(Ray ray, int mirror_depth = 0);
	Ray computeRay(int x, int y);
	HitRecord hitSurface(Ray ray, double t0, double t1);
};

#include "Parser.h"

#endif