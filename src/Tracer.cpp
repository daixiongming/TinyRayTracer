#include <iostream>
#include <fstream>
#include "Tracer.h"
#include "Sphere.h"
#include "Plane.h"

using std::cout;
using std::endl;
using std::ofstream;

Tracer::Tracer()
:_pixel_nx(300), _pixel_ny(300),
_viewport_left(-0.1), _viewport_right(0.1), _viewport_top(0.1), _viewport_bottom(-0.1),
_camera_u(1.0, 0.0, 0.0), _camera_v(0.0, 0.0, 1.0), _camera_w(0.0, -1.0, 0.0),
_camera_pos(0.0, 0.0, 1.0),
_perspective(true),
_fd(0.2)
{

}


void Tracer::buildWorld()
{
	Light* light1 = new Light(Color(1.0, 1.0, 1.0), Vector3d(1.0, 2.0, -4.0).norm());
	//Light* light2 = new Light(1.0, Vector3d(-1.0, -2.0, -4.0).norm());
	_lights.push_back(light1);
	//_lights.push_back(light2);

	Surface* sphere1 = new Sphere(Point3d(0.0, 2.0, 1.0), 0.5);
	Plane* plane1 = new Plane(Vector3d(0.0, 0.0, 1.0).norm(), Point3d(0.0, 0.0, 0.0));
	_models.push_back(sphere1);
	_models.push_back(plane1);
}

// TODO: destroy world
//


void Tracer::trace()
{
	ofstream img("output.ppm");
	img << "P3" << endl;
	img << _pixel_nx << ' ' << _pixel_ny << endl;
	img << "255" << endl;
	// for each pixel
	for (int y = _pixel_ny - 1; y >= 0; y--){
		for (int x = 0; x < _pixel_nx; x++){
			// compute camera ray
			Ray ray = computeRay(x, y);
			bool hit = false;
			HitRecord min_hit;
			min_hit._t = INFINITY;
			int hit_obj = 0;

			// check all models
			for (int i = 0; i < _models.size(); i++){
				HitRecord hitr;
				if (_models[i]->hit(ray, 0.25, 100.0, hitr)){
					hit = true;
					if (hitr._t < min_hit._t){
						min_hit = hitr;
						hit_obj = i;
					}
				}
			}

			// shading
			if (hit){
				Color color = _models[hit_obj]->shading(Color(0.2, 0.2, 0.2), _lights, -ray.direction, min_hit);
				int cx = (int)(color._x * 255);
				int cy = (int)(color._y * 255);
				int cz = (int)(color._z * 255);
				if (cx > 255)
					cx = 255;
				if (cy > 255)
					cy = 255;
				if (cz > 255)
					cz = 255;

				img << cx << ' ' << cy << ' ' << cz << endl;
			}
			else{
				img << 0 << ' ' << 0 << ' ' << 0 << endl;
			}
		}
		img << endl;

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