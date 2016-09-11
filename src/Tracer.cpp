#include <iostream>
#include "Tracer.h"
#include "Sphere.h"

using std::cout;
using std::endl;

Tracer::Tracer()
:_pixel_nx(60), _pixel_ny(60),
_viewport_left(-0.1), _viewport_right(0.1), _viewport_top(0.1), _viewport_bottom(-0.1),
_camera_u(1.0, 0.0, 0.0), _camera_v(0.0, 0.0, 1.0), _camera_w(0.0, -1.0, 0.0),
_camera_pos(0.0, 0.0, 1.0),
_perspective(true),
_fd(0.2)
{

}


void Tracer::buildWorld()
{
	Surface* sphere1 = new Sphere(Point3d(0.0, 2.0, 1.0), 0.5);
	_models.push_back(sphere1);
}

// TODO: destroy world
//


void Tracer::trace()
{
	// for each pixel
	for (int x = 0; x < _pixel_nx; x++){
		for (int y = 0; y < _pixel_ny; y++){
			// compute camera ray
			Ray ray = computeRay(x, y);
			for (int i = 0; i < _models.size(); i++){
				HitRecord hitr;
				if (_models[i]->hit(ray, 0.25, 10.0, hitr)){
					cout << "¡ö";
				}
				else{
					cout << "¡¡";
				}
			}
		}
		cout << endl;

	}
}

Ray Tracer::computeRay(int x, int y)
{
	double u = _viewport_left + (_viewport_right - _viewport_left)*(x + 0.5) / _pixel_nx;
	double v = _viewport_bottom + (_viewport_top - _viewport_bottom)*(y + 0.5) / _pixel_ny;
	Ray ray;
	if (_perspective){
		ray.direction = -_fd * _camera_w + u * _camera_u + v * _camera_v;
		ray.direction = ray.direction.norm();
		ray.origin = _camera_pos;
	}else{
		ray.direction = -_camera_w;
		ray.direction = ray.direction.norm();
		ray.origin = _camera_pos + u * _camera_u + v * _camera_v;
	}
	return ray;
}