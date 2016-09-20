#include <cmath>
#include "Camera.h"
#include "Vector3.hpp"

const float PI = 3.14159265359f;
#ifndef NULL
#define NULL 0
#endif

Camera::Camera()
:_u(1.0f, 0.0f, 0.0f), _v(0.0f, 0.0f, 1.0f), _w(0.0f, -1.0f, 0.0f),
_pixel_nx(300), _pixel_ny(300),
_viewport_left(-0.1f), _viewport_right(0.1f), _viewport_top(0.1f), _viewport_bottom(-0.1f),
_orthographic(false),
_fd(0.2f)
{
	_film = new Color[_pixel_nx * _pixel_ny];
}

Camera::Camera(Vector3f u, Vector3f v, Vector3f w, Point3f position,
	float viewport_left, float viewport_right, float viewport_top, float viewport_bottom,
	float focal_distance, bool orthographic,
	int film_width, int film_heiht)
	:_u(u), _v(v), _w(w),
	_viewport_left(viewport_left), _viewport_right(viewport_right), 
	_viewport_top(viewport_top), _viewport_bottom(viewport_bottom),
	_orthographic(orthographic),
	_fd(focal_distance),
	_pixel_nx(film_width), _pixel_ny(film_heiht)
{
	_film = new Color[_pixel_nx * _pixel_ny];
}

Camera::Camera(Vector3f direction, float angle, Point3f position,
	float focal_distance, float fov_angle, bool orthographic,
	int film_width, int film_heiht)
	:_position(position),
	_orthographic(orthographic),
	_fd(focal_distance),
	_pixel_nx(film_width), _pixel_ny(film_heiht)
{
	_w = -direction.normal();
	_u = Vector3f(1.0f, -_w._x / _w._y, 0.0f).normal();
	_v = _w.cross(_u).normal();

	float ratio = float(_pixel_nx) / _pixel_ny;
	float half_width = _fd * tan(0.5 * fov_angle * PI / 180);
	_viewport_left = -half_width;
	_viewport_right = half_width;
	_viewport_top = half_width / ratio;
	_viewport_bottom = -half_width / ratio;

	_film = new Color[_pixel_nx * _pixel_ny];
}

Camera::~Camera()
{
	if (_film){
		delete _film;
		_film = NULL;
	}
}


bool Camera::getRay(int id, Ray& ray)
{
	if (id >= _pixel_nx * _pixel_ny)
		return false;
	int x = id % _pixel_nx;
	int y = id / _pixel_nx;

	float u = _viewport_left + (_viewport_right - _viewport_left)*(x + 0.5f) / _pixel_nx;
	float v = _viewport_bottom + (_viewport_top - _viewport_bottom)*(y + 0.5f) / _pixel_ny;

	if (_orthographic){
		ray.direction = -_w;
		ray.direction = ray.direction.normal();
		ray.origin = _position + u * _u + v * _v;
	}
	else{
		ray.direction = -_fd * _w + u * _u + v * _v;
		ray.direction = ray.direction.normal();
		ray.origin = _position;
	}
	return true;
}

void Camera::setPixel(int x, int y, Color color)
{
	_film[x + _pixel_nx * y] = color;
}

void Camera::setPixel(int pixel_id, Color color)
{
	_film[pixel_id] = color;
}

const Color* Camera::getFilm(int& width, int& height)
{
	width = _pixel_nx;
	height = _pixel_ny;
	return _film;
}