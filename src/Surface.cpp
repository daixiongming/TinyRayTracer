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
						Vector3d camera_direction, const HitRecord& rec)
{
	Vector3d norm = this->getNorm(rec._hit_point);

	Color L = Color(0.0, 0.0, 0.0);
	
	int light_num = (int)lights.size();
	for (int i = 0; i < light_num; i++){
		// skip the shadowed light
		if (!lights[i])
			continue;

		Color Ii = lights[i]->_color;
		Vector3d ldi = -lights[i]->_direction;
		// diffuse reflection
		L += _material._k_d.times(Ii) * std::max(0.0, norm * ldi);

		// specular reflection
		Vector3d h = (ldi + camera_direction).norm();
		L += _material._k_s.times(Ii) * pow(std::max(0.0, norm * h), _material._p);
	}
	// ambient light
	L += _material._k_a.times(ambient_light);

	return L;
}