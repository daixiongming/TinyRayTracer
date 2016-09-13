#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Vector3.hpp"

class Material{
	friend class Surface;
	Color _k_a;	// ambient coefficient
	Color _k_d;	// diffuse coefficient
	Color _k_s;	// specular coefficient
	Color _k_m; // mirror coefficient
	double _p;		// phong exponent

public:
	Material();
	Material(Color ambient, Color diffuse, Color specular, Color mirror, double phong_exp);
	Color getMirror();
};

#include "Surface.h"

#endif