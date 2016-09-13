#include "Material.h"

Material::Material()
:_k_a(0.2, 0.2, 0.2), _k_d(0.4, 0.4, 0.4), _k_s(0.5, 0.5, 0.5), _k_m(0.1, 0.1, 0.1), _p(32.0)
{

}

Material::Material(Color ambient, Color diffuse, Color specular, Color mirror, double phong_exp)
:_k_a(ambient), _k_d(diffuse), _k_s(specular), _k_m(mirror), _p(phong_exp)
{

}

Color Material::getMirror()
{
	return _k_m;
}