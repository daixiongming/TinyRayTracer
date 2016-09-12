#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3.hpp"

class Light{
public:
	Light();
	Light(Color color, Vector3d direction);
	Color _color;
	Vector3d _direction;
};

#endif