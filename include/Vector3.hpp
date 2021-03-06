#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

template <typename T>
class Vector3{
public:
	Vector3()
		:_x(T()), _y(T()), _z(T())
	{
	}

	Vector3(T x, T y, T z)
		: _x(x), _y(y), _z(z)
	{
	}

	bool isZero()
	{
		return _x == T() && _y == T() && _z == T();
	}

	Vector3<T> operator-() const
	{
		return Vector3(-_x, -_y, -_z);
	}
	T& operator[](size_t i)
	{
		return (&_x)[i];
	}
	Vector3<T> operator+(const Vector3<T>& a) const
	{
		return Vector3(_x + a._x, _y + a._y, _z + a._z);
	}

	Vector3<T> operator-(const Vector3<T>& a) const
	{
		return Vector3(_x - a._x, _y - a._y, _z - a._z);
	}

	T operator*(const Vector3<T>& a) const
	{
		return _x * a._x + _y * a._y + _z * a._z;
	}

	Vector3& operator+=(const Vector3<T>& a)
	{
		_x += a._x;
		_y += a._y;
		_z += a._z;
		return *this;
	}

	Vector3<T> normal() const
	{
		T inv_length = 1 / sqrt(_x * _x + _y * _y + _z * _z);
		return Vector3(_x * inv_length, _y * inv_length, _z * inv_length);
	}

	Vector3<T> times(const Vector3<T>& a) const
	{
		return Vector3<T>(_x * a._x, _y * a._y, _z * a._z);
	}

	Vector3<T> cross(const Vector3<T>& a) const
	{
		return Vector3<T>(_y*a._z - _z*a._y, _z*a._x - _x*a._z, _x*a._y - _y*a._x);
	}

public:
	T _x, _y, _z;
};

template <typename T>
Vector3<T> operator*(T a, Vector3<T> v)
{
	return Vector3<T>(a * v._x, a * v._y, a * v._z);
}

template <typename T>
Vector3<T> operator*(Vector3<T> v, T a)
{
	return Vector3<T>(a * v._x, a * v._y, a * v._z);
}

//typedef Vector3<double> Point3d;
//typedef Vector3<double> Vector3d;

typedef Vector3<float> Point3f;
typedef Vector3<float> Vector3f;
typedef Vector3<float> Color;

#endif