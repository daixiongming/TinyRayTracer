#include "Material.h"

Material::Material()
:_k_a(0.2f, 0.2f, 0.2f), _k_d(0.4f, 0.4f, 0.4f), _k_s(0.5f, 0.5f, 0.5f), _k_m(0.1f, 0.1f, 0.1f), _p(32.0f)
{

}

Material::Material(Color ambient, Color diffuse, Color specular, Color mirror, float phong_exp)
:_k_a(ambient), _k_d(diffuse), _k_s(specular), _k_m(mirror), _p(phong_exp)
{

}

Color Material::getMirror()
{
	return _k_m;
}