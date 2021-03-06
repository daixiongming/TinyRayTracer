#ifndef _WORLD_H_
#define _WORLD_H_

#include <string>
#include <map>
#include "Vector3.hpp"
#include "Light.h"
#include "Surface.h"
#include "Material.h"
#include "Camera.h"

class World{
	friend class Parser;

	std::vector<Light*> _lights;
	std::vector<Surface*> _models;	// models
	std::map<std::string, Material*> _materials;

	Camera* _camera;

public:
	World();
	~World();
	
	Light* getLight(int index);
	Surface* getSurface(int index);
	Material* getMaterial(const std::string& name);
	Camera* getCamera();
};

#include "Parser.h"

#endif