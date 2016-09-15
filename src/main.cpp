#include <iostream>
#include "Parser.h"
#include "Tracer.h"
#include "World.h"

using namespace std;

int main()
{
	cout << "Ray tracing start ..." << endl;
	World world;
	Tracer tracer(&world);
	Parser parser(&world, &tracer);
	parser.readSource();
	tracer.trace();
	cout << "Done!" << endl;
	return 0;
}