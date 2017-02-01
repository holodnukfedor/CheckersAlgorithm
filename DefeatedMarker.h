#pragma once
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

class DefeatedMarker
{
private:
	unsigned short _whiteMarker;
	unsigned short _blackMarker;
	void defineSide(unsigned short *&sideMarker, const bool &forBlack);
public:
	DefeatedMarker() : _whiteMarker(0), _blackMarker(0) {}
	void markKnockedDown(const char &index, const bool &forBlack);
	void unmarkKnockedDown(const char &index, const bool &forBlack);
	bool isKnockedDown(const char &index, const bool &forBlack);
};

