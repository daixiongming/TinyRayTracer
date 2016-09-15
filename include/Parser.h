#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include "Tracer.h"
#include "World.h"

class Parser{
	World* _world;
	Tracer* _tracer;
public:
	Parser(World* world, Tracer* tracer);
	void readSource(const std::string& filename);
};

#endif