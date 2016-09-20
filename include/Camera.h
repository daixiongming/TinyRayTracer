#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.hpp"

class Camera{
	Vector3f _u, _v, _w;	// coordination
	Point3f _position;
public:
	Camera();
	Camera(Vector3f u, Vector3f v, Vector3f w, Point3f position);
	Camera(Vector3f direction, float angle, Point3f position);

	void getFrame(Vector3f& u, Vector3f& v, Vector3f& w);
	Vector3f getPosition();
};

#endif