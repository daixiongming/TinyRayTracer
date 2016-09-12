#include <algorithm>
#include "Surface.h"

Surface::Surface()
:_k_a(0.2), _k_d(0.3), _k_s(0.5), _p(16.0)
{

}

Surface::~Surface()
{

}

void Surface::setMaterial(double ambient, double diffuse, double specular, double phong_exp)
{
	_k_a = ambient;
	_k_d = diffuse;
	_k_s = specular;
	_p = phong_exp;
}

Color Surface::shading(Color ambient_color, std::vector<Light*> lights,
						Vector3d camera_direction, const HitRecord& rec)
{
	Vector3d norm = this->getNorm(rec._hit_point);

	Color L = Color(0.0, 0.0, 0.0);
	int light_num = (int)lights.size();
	for (int i = 0; i < light_num; i++){
		Color Ii = lights[i]->_color;
		Vector3d ldi = -lights[i]->_direction;
		// diffuse reflection
		L += _k_d * Ii * std::max(0.0, norm * ldi);

		// specular reflection
		Vector3d h = (ldi + camera_direction).norm();
		L += _k_s * Ii * pow(std::max(0.0, norm * h), _p);
	}
	// ambient light
	L += _k_a * ambient_color;

	return L;
}