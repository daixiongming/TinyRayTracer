#include <limits>
#include "Polygon.h"
#include "Vector3.hpp"

Polygon::Polygon(const std::vector<Point3d>& points)
:_points(points)
{
	preProjection();
}

Polygon::~Polygon()
{

}

void Polygon::preProjection()
{

	double min_x = INFINITY, min_y = INFINITY, min_z = INFINITY;
	double neg_inf = -std::numeric_limits<double>::infinity();
	double max_x = neg_inf, max_y = neg_inf, max_z = neg_inf;

	for (int i = 0; i < _points.size(); i++){
		Vector3d& p = _points[i];
		if (p._x > min_x)
			min_x = p._x;
		if (p._y > min_y)
			min_y = p._y;
		if (p._z > min_z)
			min_z = p._z;

		if (p._x < max_x)
			max_x = p._x;
		if (p._y < max_y)
			max_y = p._y;
		if (p._z < max_z)
			max_z = p._z;
	}

	double dx = max_x - min_x;
	double dy = max_y - min_y;
	double dz = max_z - min_z;

	// project to 2d
	if (dx < dy && dx < dz){
		// yz plane
		_index_u = 1;
		_index_v = 2;
	}
	else if (dy < dz){
		// xz plane
		_index_u = 0;
		_index_v = 2;
	}
	else{
		// xy plane
		_index_u = 0;
		_index_v = 1;
	}

}

bool Polygon::hit(const Ray& ray, double t0, double t1, HitRecord& rec)
{
	Vector3d n = (_points[1] - _points[0]).cross(_points[2] - _points[1]).norm();
	double t = (_points[0] - ray.origin) * n / (ray.direction * n);

	if (t < t0 || t > t1)
		return false;

	Point3d hitp = ray.origin + t * ray.direction;
	double hitu = _index_u == 0 ? hitp._x : hitp._y;
	double hitv = _index_v == 1 ? hitp._y : hitp._z;

	int pnum = (int)_points.size();

	int hit_edge_num = 0;
	for (int i = 0; i < pnum; i++){
		Vector3d& p1 = _points[i];
		Vector3d& p2 = _points[(i + 1) % pnum];

		double u1 = _index_u == 0 ? p1._x : p1._y;
		double v1 = _index_v == 1 ? p1._y : p1._z;
		double u2 = _index_u == 0 ? p2._x : p2._y;
		double v2 = _index_v == 1 ? p2._y : p2._z;

		// check the ray intersection with segment
		double k = (hitv - v1) / (v2 - v1);
		double s = (u2 - u1) * (hitv - v1) / (v2 - v1) + u1 - hitu;

		if (k > 0 && k < 1 && s > 0){
			// hit
			hit_edge_num++;
		}
	}
	if (hit_edge_num % 2){
		// odd	means inside polygon
		rec._t = t;
		rec._hit_point = ray.origin + t * ray.direction;
		return true;
	}

	return false;
}

Vector3d Polygon::getNorm(Point3d p)
{
	return (_points[1] - _points[0]).cross(_points[2] - _points[1]).norm();
}