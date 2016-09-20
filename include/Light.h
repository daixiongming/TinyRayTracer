#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3.hpp"

class Light{
public:
	Light();
	Light(Color color, Vector3f direction);
	Color _color;
	Vector3f _direction;
};

#endif