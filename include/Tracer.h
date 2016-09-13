#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include <map>
#include <string>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Surface.h"
#include "HitRecord.hpp"

class Tracer{
	int _pixel_nx, _pixel_ny;
	double _viewport_left, _viewport_right, _viewport_top, _viewport_bottom;
	Vector3d _camera_u, _camera_v, _camera_w;	// camera coordination
	Point3d _camera_pos;	// camera position
	bool _perspective;
	double _fd;		// focal distance

	Color _ambient_light;
	Color _background;
	std::vector<Light*> _lights;
	std::vector<Surface*> _models;	// models
	std::map<std::string, Material*> _materials;
	
	int _mirror_recursion_depth;

public:
	Tracer();
	void buildWorld();
	void trace();
	Color rayColor(Ray ray, int mirror_depth = 0);
	Ray computeRay(int x, int y);
	HitRecord hitSurface(Ray ray, double t0, double t1);
};

#endif