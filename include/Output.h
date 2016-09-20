#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <string>
#include "Vector3.hpp"

class Output{
	std::string _filename;
public:
	Output(const std::string& filename);
	virtual void outputImage(int width, int height,const Color* image);
};

#endif