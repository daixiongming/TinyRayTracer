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

	void setMaterial(double ambient, double diffuse, double specular, double phong_exp);

	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec) =0;
	virtual Vector3d getNorm(Point3d p) =0;

	// NOTE: lights_direction and norm must be unit vector
	virtual double shading(double ambient_intensity, std::vector<Light*> lights,
			Vector3d camera_direction, const HitRecord& rec);

protected:

	double _k_a;	// ambient coefficient
	double _k_d;	// diffuse coefficient
	double _k_s;	// specular coefficient
	double _p;		// phong exponent

};

#endif