#include "DefeatedMarker.h"

void DefeatedMarker::defineSide(unsigned short *&sideMarker, const bool &forBlack)
{
	if (forBlack) sideMarker = &_blackMarker;
	else sideMarker = &_whiteMarker;
}

void DefeatedMarker::markKnockedDown(const char &index, const bool &forBlack)
{
	unsigned short *sideMarker;
	defineSide(sideMarker, forBlack);
	unsigned short bitNumber = pow(2, index);
	(*sideMarker) |= bitNumber;
}

void DefeatedMarker::unmarkKnockedDown(const char &index, const bool &forBlack)
{
	unsigned short *sideMarker;
	defineSide(sideMarker, forBlack);
	unsigned short bitNumber = pow(2, index);
	(*sideMarker) &= ~bitNumber;
}

bool DefeatedMarker::isKnockedDown(const char &index, const bool &forBlack)
{
	unsigned short *sideMarker;
	defineSide(sideMarker, forBlack);
	unsigned short bitNumber = pow(2, index);
	return (*sideMarker) & bitNumber;
}
