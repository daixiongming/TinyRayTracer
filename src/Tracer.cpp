#include <iostream>
#include <fstream>
#include <string>
#include "Tracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace std;

Tracer::Tracer()
:_pixel_nx(300), _pixel_ny(300),
_viewport_left(-0.1), _viewport_right(0.1), _viewport_top(0.1), _viewport_bottom(-0.1),
_camera_u(1.0, 0.0, 0.0), _camera_v(0.0, 0.0, 1.0), _camera_w(0.0, -1.0, 0.0),
_camera_pos(0.0, 0.0, 1.0),
_perspective(true),
_fd(0.2),
_ambient_light(0.3, 0.3, 0.3),
_background(0.0, 0.0, 0.0),
_mirror_recursion_depth(1)
{

}


void Tracer::buildWorld()
{
	// reading world file
	string obj_name;
	ifstream worldfs("world.txt");
	double v1, v2, v3, v4;
	string material_name;
	while (worldfs >> obj_name && !worldfs.eof()){
		char trim;
		if (obj_name[0] == '#'){
			do{
				worldfs.get(trim);
			} while (trim != '\n' && !worldfs.eof());
		}
		else if (obj_name == "camera"){
			worldfs >> v1 >> v2 >> v3;
			Vector3d u(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3d v(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3d w(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3d pos(v1, v2, v3);
			_camera_u = u.norm();
			_camera_v = v.norm();
			_camera_w = w.norm();
			_camera_pos = pos;
		}
		else if (obj_name == "viewport"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			_viewport_left = v1;
			_viewport_right = v2;
			_viewport_top = v3;
			_viewport_bottom = v4;
		}
		else if (obj_name == "focal_distance"){
			worldfs >> v1;
			_fd = v1;
		}
		else if (obj_name == "resolution"){
			worldfs >> _pixel_nx >> _pixel_ny;
		}
		else if (obj_name == "background"){
			worldfs >> v1 >> v2 >> v3;
			_background = Color(v1, v2, v3);
		}
		else if (obj_name == "ambient_light"){
			worldfs >> v1 >> v2 >> v3;
			_ambient_light = Color(v1, v2, v3);
		}
		else if (obj_name == "mirror_recursion_depth"){
			worldfs >> _mirror_recursion_depth;
		}
		else if(obj_name == "light"){
			worldfs >> v1 >> v2 >> v3;
			Color c(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3d d(v1, v2, v3);
			Light* light = new Light(c, d.norm());
			_lights.push_back(light);
		}
		else if (obj_name == "material"){
			worldfs >> material_name;
			worldfs >> v1 >> v2 >> v3;
			Color k_a(v1, v2, v3);	// ambient coefficient
			worldfs >> v1 >> v2 >> v3;
			Color k_d(v1, v2, v3);	// diffuse coefficient
			worldfs >> v1 >> v2 >> v3;
			Color k_s(v1, v2, v3);	// specular coefficient
			worldfs >> v1 >> v2 >> v3;
			Color k_m(v1, v2, v3); // mirror coefficient
			worldfs >> v1;
			double p = v1;		// phong exponent
			Material* material = new Material(k_a, k_d, k_s, k_m, p);
			_materials[material_name] = material;
		}
		else if (obj_name == "sphere"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Surface* sphere = new Sphere(Point3d(v1, v2, v3), v4);
			worldfs >> material_name;
			sphere->setMaterial(*_materials[material_name]);
			_models.push_back(sphere);
		}
		else if (obj_name == "triangle"){
			worldfs >> v1 >> v2 >> v3;
			Point3d a(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Point3d b(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Point3d c(v1, v2, v3);

			Triangle* triangle = new Triangle(a, b, c);
			worldfs >> material_name;
			triangle->setMaterial(*_materials[material_name]);
			_models.push_back(triangle);
		}
		else if (obj_name == "plane"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Vector3d n(v1, v2, v3);
			double d = v4;
			Plane* plane = new Plane(n.norm(), v4);
			worldfs >> material_name;
			plane->setMaterial(*_materials[material_name]);
			_models.push_back(plane);
		}
	};
}

// TODO: destroy world
//


HitRecord Tracer::hitSurface(Ray ray, double t0, double t1)
{
	HitRecord hitr;
	hitr._surface = -1;
	hitr._t = INFINITY;
	// check all models
	for (int i = 0; i < _models.size(); i++){
		HitRecord h;
		if (_models[i]->hit(ray, t0, t1, h)){
			if (h._t < hitr._t){
				hitr = h;
				hitr._surface = i;
			}
		}
	}
	return hitr;
}

Color Tracer::rayColor(Ray ray, int mirror_depth)
{
	// hit test
	HitRecord cam_hit = hitSurface(ray, 0.0001, INFINITY);

	Color color;
	// shading
	if (cam_hit._surface >= 0){

		vector<Light*> valid_lights = _lights;

		// check for shadow
		Point3d hit_point = cam_hit._hit_point;
		for (int i = 0; i < _lights.size(); i++){
			Ray light_ray;
			light_ray.origin = hit_point;
			light_ray.direction = -_lights[i]->_direction;
			HitRecord light_hit = hitSurface(light_ray, 0.00001, INFINITY);
			if (light_hit._surface >= 0)
				valid_lights[i] = NULL;
		}

		// color shading
		color = _models[cam_hit._surface]->shading(_ambient_light, valid_lights, -ray.direction, cam_hit);
		// get surface reflecting(mirror) color
		Color k_m = _models[cam_hit._surface]->getMaterial().getMirror();
		if (!k_m.isZero() && mirror_depth > 0){
			// mirror ray
			Vector3d norm = _models[cam_hit._surface]->getNorm(cam_hit._hit_point);
			Ray mray;
			mray.origin = cam_hit._hit_point;
			mray.direction = ray.direction - 2 * (ray.direction * norm) * norm;

			color += k_m.times(rayColor(mray, mirror_depth - 1));

		}
			
	}
	else{
		// clear color (background)
		color = _background;
	}
	return color;
}

void Tracer::trace()
{
	ofstream img("output.ppm");
	img << "P3" << endl;
	img << _pixel_nx << ' ' << _pixel_ny << endl;
	img << "255" << endl;
	// for each pixel
	for (int y = _pixel_ny - 1; y >= 0; y--){
		for (int x = 0; x < _pixel_nx; x++){
			// compute camera ray
			Ray cam_ray = computeRay(x, y);
			Color color = rayColor(cam_ray, _mirror_recursion_depth);
			int cx = (int)(color._x * 255);
			int cy = (int)(color._y * 255);
			int cz = (int)(color._z * 255);
			if (cx > 255)
				cx = 255;
			if (cy > 255)
				cy = 255;
			if (cz > 255)
				cz = 255;

			img << cx << ' ' << cy << ' ' << cz << endl;

		}
		img << endl;

	}
}

// TODO: change the function name
Ray Tracer::computeRay(int x, int y)
{
	double u = _viewport_left + (_viewport_right - _viewport_left)*(x + 0.5) / _pixel_nx;
	double v = _viewport_bottom + (_viewport_top - _viewport_bottom)*(y + 0.5) / _pixel_ny;
	Ray ray;
	if (_perspective){
		ray.direction = -_fd * _camera_w + u * _camera_u + v * _camera_v;
		ray.direction = ray.direction.norm();
		ray.origin = _camera_pos;
	}else{
		ray.direction = -_camera_w;
		ray.direction = ray.direction.norm();
		ray.origin = _camera_pos + u * _camera_u + v * _camera_v;
	}
	return ray;
}