#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <vector>
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Vector3.hpp"
#include "Light.h"
#include "Material.h"

class Surface{
public:
	Surface();
	Surface(Material material);
	virtual ~Surface();

	void setMaterial(Material material);
	Material getMaterial();

	virtual bool hit(const Ray& ray, double t0, double t1, HitRecord& rec) =0;
	virtual Vector3d getNorm(Point3d p) =0;

	// NOTE: lights_direction and norm must be unit vector
	virtual Color shading(Color ambient_light, std::vector<Light*> lights,
			Vector3d camera_direction, const HitRecord& rec);

	
protected:

	Material _material;

};

#endif