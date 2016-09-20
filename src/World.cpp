#include <string>
#include <map>
#include "World.h"
#include "Material.h"

using namespace std;

World::World()
{

}

World::~World()
{
	for (vector<Light*>::iterator it = _lights.begin();
		it != _lights.end();
		it++){
		if (*it){
			delete *it;
			*it = NULL;
		}
	}
	for (vector<Surface*>::iterator it = _models.begin();
		it != _models.end();
		it++){
		if (*it){
			delete *it;
			*it = NULL;
		}
	}
	for (map<std::string, Material*>::iterator it = _materials.begin();
		it != _materials.end();
		it++){
		if (it->second){			
			delete it->second;
			it->second = NULL;
		}
	}

}

Light* World::getLight(int index)
{
	if (index < _lights.size())
		return _lights[index];
	
	return NULL;
}

Surface* World::getSurface(int index)
{
	if (index < _models.size())
		return _models[index];

	return NULL;
}

Material* World::getMaterial(const string& name)
{
	map<string, Material*>::iterator it_key = _materials.find(name);
	if (it_key != _materials.end())
		return it_key->second;

	return NULL;
}

Camera* World::getCamera()
{
	return &_camera;
}