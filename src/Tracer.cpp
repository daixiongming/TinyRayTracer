#include <iostream>
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
:_ambient_light(0.3f, 0.3f, 0.3f),
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
	// hit test, for the first time camera hit, _use min_visial
	float min_vis = (mirror_depth == _mirror_recursion_depth ? _min_visual : 0.00001f);
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
				// 0.001f * cam_hit._t  adaptive adjust
				HitRecord light_hit = hitSurface(light_ray, 0.0001f * cam_hit._t, _max_visual);
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
				// prevent ray cross himself
				mray.origin += 0.0001f * cam_hit._t * mray.direction;
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

void Tracer::trace()
{
	// for each camera ray
	Ray cam_ray;
	Camera* camera = _world->getCamera();
	for (int i = 0; camera->getRay(i, cam_ray); i++){

			Color color = rayColor(cam_ray, _mirror_recursion_depth);
			camera->setPixel(i, color);
	}
}