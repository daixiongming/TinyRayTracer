#include <string>
#include <map>
#include "World.h"
#include "Material.h"

using namespace std;

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
