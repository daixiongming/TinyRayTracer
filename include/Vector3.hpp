#ifndef _VECTOR3_H_
#define _VECTOR3_H_

template <typename T = double>
class Vector3{
public:
	Vector3::Vector3()
		:_x(0.0), _y(0.0), _z(0.0)
	{
	}

	Vector3::Vector3(T x, T y, T z)
		: _x(x), _y(y), _z(z)
	{
	}

	Vector3<T> operator-()
	{
		return Vector3(-_x, -_y, -_z);
	}

	Vector3<T> operator+(Vector3<T> a)
	{
		return Vector3(_x + a._x, _y + a._y, _z + a._z);
	}
public:
	T _x, _y, _z;
};

template <typename T = double>
Vector3<T> operator*(T a, Vector3<T> v)
{
	return Vector3<T>(a * v._x, a * v._y, a * v._z);
}

typedef Vector3<double> Point3d;
typedef Vector3<double> Vector3d;

#endif