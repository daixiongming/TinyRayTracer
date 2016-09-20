#include <limits>
#include "Polygon.h"
#include "Vector3.hpp"

Polygon::Polygon(const std::vector<Point3f>& points)
:_points(points)
{
	preProjection();
}

Polygon::~Polygon()
{

}

void Polygon::preProjection()
{
	float INF = std::numeric_limits<float>::infinity();
	float NEG_INF = -std::numeric_limits<float>::infinity();
	float min_x = INF, min_y = INF, min_z = INF;
	
	float max_x = NEG_INF, max_y = NEG_INF, max_z = NEG_INF;

	for (int i = 0; i < _points.size(); i++){
		Vector3f& p = _points[i];
		if (p._x < min_x)
			min_x = p._x;
		if (p._y < min_y)
			min_y = p._y;
		if (p._z < min_z)
			min_z = p._z;

		if (p._x > max_x)
			max_x = p._x;
		if (p._y > max_y)
			max_y = p._y;
		if (p._z > max_z)
			max_z = p._z;
	}

	float dx = max_x - min_x;
	float dy = max_y - min_y;
	float dz = max_z - min_z;

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

bool Polygon::hit(const Ray& ray, float t0, float t1, HitRecord& rec)
{
	Vector3f n = (_points[1] - _points[0]).cross(_points[2] - _points[1]).normal();
	float t = (_points[0] - ray.origin) * n / (ray.direction * n);

	if (t < t0 || t > t1)
		return false;

	Point3f hitp = ray.origin + t * ray.direction;
	float hitu = _index_u == 0 ? hitp._x : hitp._y;
	float hitv = _index_v == 1 ? hitp._y : hitp._z;

	int pnum = (int)_points.size();

	int hit_edge_num = 0;
	for (int i = 0; i < pnum; i++){
		Vector3f& p1 = _points[i];
		Vector3f& p2 = _points[(i + 1) % pnum];

		float u1 = _index_u == 0 ? p1._x : p1._y;
		float v1 = _index_v == 1 ? p1._y : p1._z;
		float u2 = _index_u == 0 ? p2._x : p2._y;
		float v2 = _index_v == 1 ? p2._y : p2._z;

		// check the ray intersection with segment
		float k = (hitv - v1) / (v2 - v1);
		float s = (u2 - u1) * (hitv - v1) / (v2 - v1) + u1 - hitu;

		if (k > 0.0f && k < 1.0f && s > 0.0f){
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

Vector3f Polygon::getNormal(Point3f p)
{
	return (_points[1] - _points[0]).cross(_points[2] - _points[1]).normal();
}