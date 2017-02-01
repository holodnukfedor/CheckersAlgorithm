#pragma once
#include "Position.h"
#include <math.h>
#include <fstream>

class Move
{
private:
	const static unsigned char _bitsOnPosition = 6;
	unsigned int _first;
	unsigned int _second;
	unsigned char _count;
	bool _isBattle;
public:
	Move() : _first(0), _second(0), _count(0), _isBattle(0) {}
	Move(const unsigned char &firstPosition, const bool &isBattle);
	Move(const Move &move);
	Move & operator=(const Move &move);
	void addPosition(const unsigned char &x, const unsigned char &y);
	Position getPosition(const unsigned char &index);
	unsigned char Length() { return _count; }
	bool isBattleMove();
	Move(const unsigned char &firstPosition);
	void printMove();
	void strToMove(const char *str, const bool &isBattle); //строка формата c3d4 два числа на позицию без разделителя
};

