#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

template <typename T = double>
class Vector3{
public:
	Vector3()
		:_x(0.0), _y(0.0), _z(0.0)
	{
	}

	Vector3(T x, T y, T z)
		: _x(x), _y(y), _z(z)
	{
	}

	bool isZero()
	{
		return _x == 0.0 && _y == 0.0 && _z == 0.0;
	}

	Vector3<T> operator-() const
	{
		return Vector3(-_x, -_y, -_z);
	}

	Vector3<T> operator+(Vector3<T> a) const
	{
		return Vector3(_x + a._x, _y + a._y, _z + a._z);
	}

	Vector3<T> operator-(Vector3<T> a) const
	{
		return Vector3(_x - a._x, _y - a._y, _z - a._z);
	}

	T operator*(Vector3<T> a) const
	{
		return _x * a._x + _y * a._y + _z * a._z;
	}

	Vector3& operator+=(Vector3<T> a)
	{
		_x += a._x;
		_y += a._y;
		_z += a._z;
		return *this;
	}

	Vector3<T> norm() const
	{
		T length = sqrt(_x * _x + _y * _y + _z * _z);
		return Vector3(_x / length, _y / length, _z / length);
	}

	Vector3<T> times(const Vector3<T>& a) const
	{
		return Vector3<T>(_x * a._x, _y * a._y, _z * a._z);
	}
public:
	T _x, _y, _z;
};

template <typename T = double>
Vector3<T> operator*(T a, Vector3<T> v)
{
	return Vector3<T>(a * v._x, a * v._y, a * v._z);
}

template <typename T = double>
Vector3<T> operator*(Vector3<T> v, T a)
{
	return Vector3<T>(a * v._x, a * v._y, a * v._z);
}

typedef Vector3<double> Point3d;
typedef Vector3<double> Vector3d;

typedef Vector3<double> Color;

#endif