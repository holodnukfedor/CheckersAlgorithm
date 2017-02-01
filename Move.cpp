#include "Move.h"

Move::Move(const unsigned char &firstPosition)
{

}

Move::Move(const unsigned char &firstPosition, const bool &isBattle) : _first(0), _second(0)
{
	char firstPosMask = 63;
	_count = 1;
	_first |= firstPosition & firstPosMask;
	_isBattle = isBattle;
}

Move::Move(const Move &move) {
	_count = move._count;
	_first = move._first;
	_second = move._second;
	_isBattle = move._isBattle;
}


Move & Move::operator=(const Move &move)
{
	if (this != &move) {
		_count = move._count;
		_first = move._first;
		_second = move._second;
		_isBattle = move._isBattle;
	}
	return *this;
}
void Move::addPosition(const unsigned char &x, const unsigned char &y)
{
	int degree;
	unsigned int bitsShift;
	if (_count < 5) {
		degree = _count * _bitsOnPosition;
		bitsShift = pow((float)2, degree);
		_first |= x * bitsShift;
		_first |= y * bitsShift * 8;
	}
	else {
		degree = (_count - 5) * _bitsOnPosition;
		bitsShift = pow((float)2, degree);
		_second |= x * bitsShift;
		_second |= y * bitsShift * 8;
	}
	++_count;
}

Position Move::getPosition(const unsigned char &index){
	Position position;
	if (index >= 0 && index <= _count) { //возможно стоит выбрасывать исключения, если выходим за пределы памяти 
		unsigned char maskX = 7;
		unsigned char maskY = 56;

		int degree;
		if (index <= 5) {
			degree = (index - 1) * _bitsOnPosition;
			unsigned int bitsShift = pow((float)2, degree);
			position._x = (_first & (maskX * bitsShift)) / bitsShift;
			position._y = (_first & (maskY * bitsShift)) / (bitsShift * 8);
		}
		else {
			degree = (index - 6) * _bitsOnPosition;
			unsigned int bitsShift = pow((float)2, degree);
			position._x = (_second & (maskX * bitsShift)) / bitsShift;
			position._y = (_second & (maskY * bitsShift)) / (bitsShift * 8);
		}
	}
	return position;
}

bool Move::isBattleMove()
{
	return _isBattle;
}

void Move::printMove()
{
	for (int i = 1; i <= this->Length(); ++i) {
		this->getPosition(i).print();
	}
	cout << endl;
}

void Move::strToMove(const char *str, const bool &isBattle)
{
	int countOfSymbolsInPosition = 2;
	int strLength = strlen(str);
	for (int i = 0; i < strLength; i += countOfSymbolsInPosition) {
		char x = str[i] - 'a';
		char y = str[i + 1] - '1';
		this->addPosition(x, y);
	}
	_isBattle = isBattle;
}