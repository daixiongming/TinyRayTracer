#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3.hpp"

class Light{
public:
	Light();
	Light(double intensity, Vector3d direction);
	double _intensity;
	Vector3d _direction;
};

#endif