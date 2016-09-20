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

	virtual bool hit(const Ray& ray, float t0, float t1, HitRecord& rec) = 0;
	virtual Vector3f getNormal(Point3f p) = 0;

	// NOTE: lights_direction and normal must be unit vector
	virtual Color shading(Color ambient_light, std::vector<Light*> lights,
		Vector3f camera_direction, const HitRecord& rec);

	
protected:

	Material _material;

};

#endif