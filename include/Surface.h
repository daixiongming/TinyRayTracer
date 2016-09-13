#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <vector>
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Vector3.hpp"
#include "Light.h"

class Surface{
public:
	Surface();
	virtual ~Surface();

	void setMaterial(Color ambient, Color diffuse, Color specular, double phong_exp);

	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec) =0;
	virtual Vector3d getNorm(Point3d p) =0;

	// NOTE: lights_direction and norm must be unit vector
	virtual Color shading(Color ambient_light, std::vector<Light*> lights,
			Vector3d camera_direction, const HitRecord& rec);

protected:

	Color _k_a;	// ambient coefficient
	Color _k_d;	// diffuse coefficient
	Color _k_s;	// specular coefficient
	double _p;		// phong exponent

};

#endif