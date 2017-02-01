#pragma once
#include <exception>

using std::exception;

class VictoryException :
	public exception
{
public:
	virtual const char* what() const throw()
	{
		return "victory";
	}
};

