#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <limits>
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
_viewport_left(-0.1f), _viewport_right(0.1f), _viewport_top(0.1f), _viewport_bottom(-0.1f),
_perspective(true),
_fd(0.2f),
_ambient_light(0.3f, 0.3f, 0.3f),
_background(0.0f, 0.0f, 0.0f),
_mirror_recursion_depth(1),
_depth_mode(false),
_min_visual(0.1f),
_max_visual(50),
_world(world)
{
	
}


void Tracer::setWorld(World* world)
{
	_world = world;
}


HitRecord Tracer::hitSurface(Ray ray, float t0, float t1)
{
	HitRecord hitr;
	hitr._surface = -1;
	hitr._t = numeric_limits<float>::infinity();
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
	float min_vis = mirror_depth == _mirror_recursion_depth ? _min_visual : 0.00001f;
	HitRecord cam_hit = hitSurface(ray, min_vis, _max_visual);

	Color color;
	// shading
	if (cam_hit._surface >= 0){
		
		// the Surface
		Surface* pSurface = _world->getSurface(cam_hit._surface);

		if (_depth_mode){

			// depth mode
			float intensity = sqrt((cam_hit._t * ray.direction) * (cam_hit._t * ray.direction));
			color = Color(intensity, intensity, intensity);
		}
		else{
			
			// normal mode
			vector<Light*> valid_lights;

			// check for shadow
			Point3f hit_point = cam_hit._hit_point;
			Light* pLight;
			for (int i = 0; pLight = _world->getLight(i); i++){
				Ray light_ray;
				light_ray.origin = hit_point;
				light_ray.direction = -pLight->_direction;
				HitRecord light_hit = hitSurface(light_ray, 0.00001f, _max_visual);
				if (light_hit._surface < 0)
					valid_lights.push_back(pLight);
			}

			// color shading
			color = pSurface->shading(_ambient_light, valid_lights, -ray.direction, cam_hit);
			// get surface reflecting(mirror) color
			Color k_m = pSurface->getMaterial().getMirror();
			if (!k_m.isZero() && mirror_depth > 0){
				// mirror ray
				Vector3f normal = pSurface->getNormal(cam_hit._hit_point);
				Ray mray;
				mray.origin = cam_hit._hit_point;
				mray.direction = ray.direction - 2 * (ray.direction * normal) * normal;

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
	ofstream img(output,ios::binary);
	ostringstream header;
	header << (_depth_mode ? "P5" : "P6") << endl;
	header << _pixel_nx << ' ' << _pixel_ny << endl;
	header << (_depth_mode ? "65535" : "255") << endl;
	string hear_str = header.str();
	img.write(hear_str.c_str(), hear_str.size());
	
	// for each pixel
	for (int y = _pixel_ny - 1; y >= 0; y--){
		for (int x = 0; x < _pixel_nx; x++){
			// compute camera ray
			Ray cam_ray = computeRay(x, y);
			Color color = rayColor(cam_ray, _mirror_recursion_depth);

			if (_depth_mode){
				int depth = min((int)(color._x * 1000), 65535);
				unsigned char d[2];
				// NOTICE: big ending, unknow reason, it just works
				d[0] = (unsigned char)((depth >> 8) & 0xff);
				d[1] = (unsigned char)(depth & 0xff);
				img.write((char*)d, sizeof(d));
			}
			else{
				unsigned char rgb[3];
				rgb[0] = (unsigned char)min((int)(color._x * 255), 255);
				rgb[1] = (unsigned char)min((int)(color._y * 255), 255);
				rgb[2] = (unsigned char)min((int)(color._z * 255), 255);
				
				img.write((char*)rgb, sizeof(rgb));
			}
		}

	}
}

// TODO: change the function name
Ray Tracer::computeRay(int x, int y)
{
	float u = _viewport_left + (_viewport_right - _viewport_left)*(x + 0.5f) / _pixel_nx;
	float v = _viewport_bottom + (_viewport_top - _viewport_bottom)*(y + 0.5f) / _pixel_ny;
	Vector3f cam_u, cam_v, cam_w;
	_world->getCamera()->getFrame(cam_u, cam_v, cam_w);
	Vector3f cam_pos = _world->getCamera()->getPosition();
	Ray ray;
	if (_perspective){
		ray.direction = -_fd * cam_w + u * cam_u + v * cam_v;
		ray.direction = ray.direction.normal();
		ray.origin = cam_pos;
	}else{
		ray.direction = -cam_w;
		ray.direction = ray.direction.normal();
		ray.origin = cam_pos + u * cam_u + v * cam_v;
	}
	return ray;
}