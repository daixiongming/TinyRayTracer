#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Parser.h"
#include "Tracer.h"
/*
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
*/
using namespace std;

Tracer::Tracer(World* world)
:_pixel_nx(300), _pixel_ny(300),
_viewport_left(-0.1), _viewport_right(0.1), _viewport_top(0.1), _viewport_bottom(-0.1),
_camera_u(1.0, 0.0, 0.0), _camera_v(0.0, 0.0, 1.0), _camera_w(0.0, -1.0, 0.0),
_camera_pos(0.0, 0.0, 1.0),
_perspective(true),
_fd(0.2),
_ambient_light(0.3, 0.3, 0.3),
_background(0.0, 0.0, 0.0),
_mirror_recursion_depth(1),
_depth_mode(false),
_world(world)
{

}


void Tracer::setWorld(World* world)
{
	_world = world;
}


HitRecord Tracer::hitSurface(Ray ray, double t0, double t1)
{
	HitRecord hitr;
	hitr._surface = -1;
	hitr._t = INFINITY;
	// check all models
	Surface* pSurface;
	for (int i = 0; pSurface = _world->getSurface(i); i++){
		HitRecord h;
		if (pSurface->hit(ray, t0, t1, h)){
			if (h._t < hitr._t){
				hitr = h;
				hitr._surface = i;
			}
		}
	}
	return hitr;
}

Color Tracer::rayColor(Ray ray, int mirror_depth)
{
	// hit test
	HitRecord cam_hit = hitSurface(ray, 0.0001, INFINITY);

	Color color;
	// shading
	if (cam_hit._surface >= 0){
		
		// the Surface
		Surface* pSurface = _world->getSurface(cam_hit._surface);

		if (_depth_mode){

			// depth mode
			double intensity = sqrt((cam_hit._t * ray.direction) * (cam_hit._t * ray.direction));
			color = Color(intensity, intensity, intensity);
		}
		else{
			
			// normal mode
			vector<Light*> valid_lights;

			// check for shadow
			Point3d hit_point = cam_hit._hit_point;
			Light* pLight;
			for (int i = 0; pLight = _world->getLight(i); i++){
				Ray light_ray;
				light_ray.origin = hit_point;
				light_ray.direction = -pLight->_direction;
				HitRecord light_hit = hitSurface(light_ray, 0.00001, INFINITY);
				if (light_hit._surface < 0)
					valid_lights.push_back(pLight);
			}

			// color shading
			color = pSurface->shading(_ambient_light, valid_lights, -ray.direction, cam_hit);
			// get surface reflecting(mirror) color
			Color k_m = pSurface->getMaterial().getMirror();
			if (!k_m.isZero() && mirror_depth > 0){
				// mirror ray
				Vector3d norm = pSurface->getNorm(cam_hit._hit_point);
				Ray mray;
				mray.origin = cam_hit._hit_point;
				mray.direction = ray.direction - 2 * (ray.direction * norm) * norm;

				color += k_m.times(rayColor(mray, mirror_depth - 1));

			}
		}
	}
	else{
		// clear color (background)
		color = _background;
	}
	return color;
}

void Tracer::trace(const std::string& output)
{
	ofstream img(output);
	img << (_depth_mode?"P2":"P3") << endl;
	img << _pixel_nx << ' ' << _pixel_ny << endl;
	img << (_depth_mode?"65535":"255") << endl;
	// for each pixel
	for (int y = _pixel_ny - 1; y >= 0; y--){
		for (int x = 0; x < _pixel_nx; x++){
			// compute camera ray
			Ray cam_ray = computeRay(x, y);
			Color color = rayColor(cam_ray, _mirror_recursion_depth);

			if (_depth_mode){
				int depth = (int)(color._x * 1000);
				if (depth > 65535)
					depth = 65535;
				img << depth << endl;
			}
			else{
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
		}
		//img << endl;

	}
}

// TODO: change the function name
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