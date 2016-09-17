#include <iostream>
#include "Exception.hpp"
#include "Parser.h"
#include "Tracer.h"
#include "World.h"

using namespace std;

int main(int argc, char *argv[])
{

	string source, output;
	if (argc == 3){
		source = argv[1];
		output = argv[2];
	}
	else if (argc == 1){
		source = "world.txt";
		output = "output.ppm";
	}
	else{
		std::cerr << "Usage: tray [world file] [output image name]" << std::endl;
		return 1;
	}
	try{
		cout << "Ready ..." << endl;
		World world;
		Tracer tracer(&world);
		Parser parser(&world, &tracer);
		cout << "Building world ..." << endl;
		parser.readSource(source);
		cout << "Ray tracing ..." << endl;
		tracer.trace(output);
		cout << "Done!" << endl;
	}
	catch (Error e){
		cerr << "An Error occurred:" << endl;
		cerr << e.what() << endl;
		system("pause");
	}
	catch (...){
		cerr << "Unknow error" << endl;
		system("pause");
	}
	return 0;
}