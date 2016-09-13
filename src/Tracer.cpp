#include <iostream>
#include <fstream>
#include "Tracer.h"
#include "Sphere.h"
#include "Plane.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::vector;

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
	Light* light1 = new Light(Color(1.0, 1.0, 1.0), Vector3d(5.0, 1.0, -2.0).norm());
	//Light* light2 = new Light(Color(0.4, 0.1, 0.5), Vector3d(-1.0, -2.0, -5.0).norm());
	_lights.push_back(light1);
	//_lights.push_back(light2);

	Surface* sphere1 = new Sphere(Point3d(-0.6, 2.0, 1.0), 0.3);
	Surface* sphere2 = new Sphere(Point3d(0.2, 1.5, 1.0), 0.3);
	Plane* plane1 = new Plane(Vector3d(0.0, 0.0, 1.0).norm(), Point3d(0.0, 0.0, 0.7));
	_models.push_back(sphere1);
	_models.push_back(sphere2);
	_models.push_back(plane1);
}

// TODO: destroy world
//


HitRecord Tracer::hitSurface(Ray ray, double t0, double t1)
{
	HitRecord hitr;
	hitr._surface = -1;
	hitr._t = INFINITY;
	// check all models
	for (int i = 0; i < _models.size(); i++){
		HitRecord h;
		if (_models[i]->hit(ray, t0, t1, h)){
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
	HitRecord cam_hit = hitSurface(ray, 0.25, INFINITY);

	Color color;
	// shading
	if (cam_hit._surface >= 0){

		vector<Light*> valid_lights = _lights;

		// check for shadow
		Point3d hit_point = cam_hit._hit_point;
		for (int i = 0; i < _lights.size(); i++){
			Ray light_ray;
			light_ray.origin = hit_point;
			light_ray.direction = -_lights[i]->_direction;
			HitRecord light_hit = hitSurface(light_ray, 0.001, INFINITY);
			if (light_hit._surface >= 0)
				valid_lights[i] = NULL;
		}

		// color shading
		color = _models[cam_hit._surface]->shading(Color(0.3, 0.3, 0.3), valid_lights, -ray.direction, cam_hit);
		// get surface reflecting(mirror) color
		Color k_m = _models[cam_hit._surface]->getMirrorColor();
		if (!k_m.isZero() && mirror_depth > 0){
			// mirror ray
			Vector3d norm = _models[cam_hit._surface]->getNorm(cam_hit._hit_point);
			Ray mray;
			mray.origin = cam_hit._hit_point;
			mray.direction = ray.direction - 2 * (ray.direction * norm) * norm;

			color += k_m.times(rayColor(mray, mirror_depth - 1));

		}
			
	}
	else{
		// clear color
		color = Color(0.0, 0.0, 0.0);
	}
	return color;
}

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
			Ray cam_ray = computeRay(x, y);
			Color color = rayColor(cam_ray, 2);
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
		img << endl;

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