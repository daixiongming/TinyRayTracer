#include "Camera.h"

Camera::Camera()
:_u(1.0f, 0.0f, 0.0f), _v(0.0f, 0.0f, 1.0f), _w(0.0f, -1.0f, 0.0f)
{

}

Camera::Camera(Vector3f u, Vector3f v, Vector3f w, Point3f position)
: _u(u.normal()), _v(v.normal()), _w(w.normal()), _position(position)
{
	
}

Camera::Camera(Vector3f direction, float angle, Point3f position)
: _w(-direction.normal()), _position(position)
{
	_u = Vector3f(1.0f, -_w._x / _w._y, 0.0f).normal();
	_v = _w.cross(_u).normal();
}

void Camera::getFrame(Vector3f& u, Vector3f& v, Vector3f& w)
{
	u = _u;
	v = _v;
	w = _w;
}

Vector3f Camera::getPosition()
{
	return _position;
}