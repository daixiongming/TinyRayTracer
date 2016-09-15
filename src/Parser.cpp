#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"

using namespace std;

Parser::Parser(World* world, Tracer* tracer)
:_world(world), _tracer(tracer)
{

}

void Parser::readSource()
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
			_tracer->_camera_u = u.norm();
			_tracer->_camera_v = v.norm();
			_tracer->_camera_w = w.norm();
			_tracer->_camera_pos = pos;
		}
		else if (obj_name == "viewport"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			_tracer->_viewport_left = v1;
			_tracer->_viewport_right = v2;
			_tracer->_viewport_top = v3;
			_tracer->_viewport_bottom = v4;
		}
		else if (obj_name == "focal_distance"){
			worldfs >> v1;
			_tracer->_fd = v1;
		}
		else if (obj_name == "resolution"){
			worldfs >> _tracer->_pixel_nx >> _tracer->_pixel_ny;
		}
		else if (obj_name == "depth_mode"){
			string sv;
			worldfs >> sv;
			if (sv == "true")
				_tracer->_depth_mode = true;
		}
		else if (obj_name == "background"){
			worldfs >> v1 >> v2 >> v3;
			_tracer->_background = Color(v1, v2, v3);
		}
		else if (obj_name == "ambient_light"){
			worldfs >> v1 >> v2 >> v3;
			_tracer->_ambient_light = Color(v1, v2, v3);
		}
		else if (obj_name == "mirror_recursion_depth"){
			worldfs >> _tracer->_mirror_recursion_depth;
		}
		else if (obj_name == "light"){
			worldfs >> v1 >> v2 >> v3;
			Color c(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3d d(v1, v2, v3);
			Light* light = new Light(c, d.norm());
			_world->_lights.push_back(light);
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
			_world->_materials[material_name] = material;
		}
		else if (obj_name == "sphere"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Surface* sphere = new Sphere(Point3d(v1, v2, v3), v4);
			worldfs >> material_name;
			sphere->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(sphere);
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
			triangle->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(triangle);
		}
		else if (obj_name == "plane"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Vector3d n(v1, v2, v3);
			double d = v4;
			Plane* plane = new Plane(n.norm(), v4);
			worldfs >> material_name;
			plane->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(plane);
		}
	};
}