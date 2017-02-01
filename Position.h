#pragma once
#include <iostream>

using std::cout;
using std::endl;

struct Position
{
public:
	char _x;
	char _y;
	void print();
	Position() : _x(0), _y(0) { }
	Position(char x, char y) : _x(x), _y(y) { }
};

