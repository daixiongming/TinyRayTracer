#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Polygon.h"
#include "Exception.hpp"
#include "Camera.h"

using namespace std;

Parser::Parser(World* world, Tracer* tracer)
:_world(world), _tracer(tracer)
{

}

void Parser::readSource(const string& filename)
{
	// reading world file
	string obj_name, pre_objname;
	ifstream worldfs(filename);
	float v1, v2, v3, v4;
	string material_name;
	while (worldfs >> obj_name && !worldfs.eof()){
		pre_objname = obj_name;
		char trim;
		if (obj_name[0] == '#'){
			do{
				worldfs.get(trim);
			} while (trim != '\n' && !worldfs.eof());
		}
		else if (obj_name == "camera"){
			worldfs >> v1 >> v2 >> v3;
			Vector3f u(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3f v(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3f w(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Vector3f pos(v1, v2, v3);

			Camera cam(u.normal(), v.normal(), w.normal(), pos);
			_world->_camera = cam;
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
		else if (obj_name == "view_distance"){
			worldfs >> v1 >> v2;
			_tracer->_min_visual = v1;
			_tracer->_max_visual = v2;
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
			Vector3f d(v1, v2, v3);
			Light* light = new Light(c, d.normal());
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
			float p = v1;		// phong exponent
			Material* material = new Material(k_a, k_d, k_s, k_m, p);
			_world->_materials[material_name] = material;
		}
		else if (obj_name == "sphere"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Surface* sphere = new Sphere(Point3f(v1, v2, v3), v4);
			worldfs >> material_name;
			sphere->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(sphere);
		}
		else if (obj_name == "triangle"){
			worldfs >> v1 >> v2 >> v3;
			Point3f a(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Point3f b(v1, v2, v3);
			worldfs >> v1 >> v2 >> v3;
			Point3f c(v1, v2, v3);

			Triangle* triangle = new Triangle(a, b, c);
			worldfs >> material_name;
			triangle->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(triangle);
		}
		else if (obj_name == "plane"){
			worldfs >> v1 >> v2 >> v3 >> v4;
			Vector3f n(v1, v2, v3);
			float d = v4;
			Plane* plane = new Plane(n.normal(), v4);
			worldfs >> material_name;
			plane->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(plane);
		}
		else if (obj_name == "polygon"){
			int vertex_num = 0;
			worldfs >> vertex_num;
			vector<Point3f> points;
			for (int i = 0; i < vertex_num; i++){
				worldfs >> v1 >> v2 >> v3;
				points.push_back(Point3f(v1, v2, v3));
			}
			worldfs >> material_name;

			Polygon* polygon = new Polygon(points);
			polygon->setMaterial(*_world->_materials[material_name]);
			_world->_models.push_back(polygon);
		}
	};
	//when parser failed
	if (!worldfs.eof()){
		throw Error("Parser failed on " + pre_objname);
	}
}