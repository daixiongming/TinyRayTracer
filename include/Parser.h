#ifndef _PARSER_H_
#define _PARSER_H_

#include "Tracer.h"
#include "World.h"

class Parser{
	World* _world;
	Tracer* _tracer;
public:
	Parser(World* world, Tracer* tracer);
	void readSource();
};

#endif