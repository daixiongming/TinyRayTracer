#include <algorithm>
#include "Surface.h"

Surface::Surface()
{

}

Surface::Surface(Material material)
:_material(material)
{

}

Surface::~Surface()
{

}

void Surface::setMaterial(Material material)
{
	_material = material;
}

Material Surface::getMaterial()
{
	return _material;
}

Color Surface::shading(Color ambient_light, std::vector<Light*> lights,
	Vector3f camera_direction, const HitRecord& rec)
{
	Vector3f normal = this->getNormal(rec._hit_point);

	Color L = Color(0.0f, 0.0f, 0.0f);
	
	int light_num = (int)lights.size();
	for (int i = 0; i < light_num; i++){
		// skip the shadowed light
		if (!lights[i])
			continue;

		Color Ii = lights[i]->_color;
		Vector3f ldi = -lights[i]->_direction;
		// diffuse reflection
		L += _material._k_d.times(Ii) * std::max(0.0f, normal * ldi);

		// specular reflection
		Vector3f h = (ldi + camera_direction).normal();
		L += _material._k_s.times(Ii) * pow(std::max(0.0f, normal * h), _material._p);
	}
	// ambient light
	L += _material._k_a.times(ambient_light);

	return L;
}