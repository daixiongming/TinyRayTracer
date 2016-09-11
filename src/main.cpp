#include <iostream>
#include "Tracer.h"

using namespace std;

int main()
{
	cout << "Ray tracing start ..." << endl;
	Tracer tracer;
	tracer.buildWorld();
	tracer.trace();
	cout << "Done!" << endl;
	return 0;
}