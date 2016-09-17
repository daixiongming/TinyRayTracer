#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>

class Error{
	std::string _info;
public:
	Error(const std::string& info)
		:_info(info)
	{
		
	}
	std::string what()
	{
		return _info;
	}
};


#endif