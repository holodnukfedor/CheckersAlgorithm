#include "Position.h"

void Position::print() {
	cout << (char)(_x + 'a');
	cout << _y + 1 << ":";
}