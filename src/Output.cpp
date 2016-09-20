#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Output.h"

using namespace std;

Output::Output(const std::string& filename)
:_filename(filename)
{

}

void Output::outputImage(int width, int height, const Color* image)
{
	bool _depth_mode = false;	// TODO: implement depth mode
	ofstream img(_filename, ios::binary);
	ostringstream header;
	header << (_depth_mode ? "P5" : "P6") << endl;

	header << width << ' ' << height << endl;
	header << (_depth_mode ? "65535" : "255") << endl;
	string hear_str = header.str();
	img.write(hear_str.c_str(), hear_str.size());

	for (int i = height - 1; i >= 0; i--){
		for (int j = 0; j < width; j++){
			Color color = image[i * width + j];
			if (_depth_mode){
				int depth = min((int)(color._x * 1000), 65535);
				unsigned char d[2];
				// NOTICE: big ending, unknow reason, it just works
				d[0] = (unsigned char)((depth >> 8) & 0xff);
				d[1] = (unsigned char)(depth & 0xff);
				img.write((char*)d, sizeof(d));
			}
			else{
				unsigned char rgb[3];
				rgb[0] = (unsigned char)min((int)(color._x * 255), 255);
				rgb[1] = (unsigned char)min((int)(color._y * 255), 255);
				rgb[2] = (unsigned char)min((int)(color._z * 255), 255);

				img.write((char*)rgb, sizeof(rgb));
			}
		}
	}

}