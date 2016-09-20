#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.hpp"
#include "Ray.hpp"

class Camera{
	Vector3f _u, _v, _w;	// coordination
	Point3f _position;

	int _pixel_nx, _pixel_ny;
	float _viewport_left, _viewport_right, _viewport_top, _viewport_bottom;	// film size
	bool _orthographic;
	float _fd;		// focal distance

	Color* _film;

public:
	Camera();
	Camera(Vector3f u, Vector3f v, Vector3f w, Point3f position,
		float viewport_left, float viewport_right, float viewport_top, float viewport_bottom,
		float focal_distance, bool orthographic, 
		int film_width, int film_heiht);

	Camera(Vector3f direction, float angle, Point3f position,
		float focal_distance, float fov_angle, bool orthographic,
		int film_width, int film_heiht);
	~Camera();

	void setPixel(int x, int y, Color color);
	void setPixel(int pixel_id, Color color);

	//void getFrame(Vector3f& u, Vector3f& v, Vector3f& w);
	//Vector3f getPosition();

	bool getRay(int id, Ray& ray);
	const Color* getFilm(int& width, int& height);
};

#endif