#pragma once
#include <string.h>
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Move.h"
#include "Stack.h"
#include "DefeatedMarker.h"
#include <vector>
#include <string>
#include "VictoryException.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

class Checkers
{
private:
	const static unsigned char QUEEN_FLAG = 64;
	const static unsigned char BLACK_COLOR_FLAG = 128;
	enum Directions
	{
		NE = 1,
		SE = 2,
		SW = 4,
		NW = 8
	};
	const static char NUMB_IN_STR_FOR_ONE_CHECKER = 3;
	const static char FIELD_ROW_SIZE = 8;
	static const char FIELD_LENGTH = 64;
	static const int INF_SUPERIORITY = 32767;
	static const char NO_MOVES = 127;
	static const char DEPTH_VALUE = 100;
	unsigned char * _checkersField[FIELD_LENGTH];
	unsigned char * _whiteCheckers;
	unsigned char * _blackCheckers;
	unsigned char _whiteCheckersCount;
	unsigned char _blackCheckersCount;
	DefeatedMarker _defeatedMarker;
	bool wasBattleMove;
	char _startDepth;

	void parseCheckersString(char * str, unsigned char *& array, bool isBlack);
	void placeCheckersOnField();

	void checkMoveOnDirection(Queue<Move> &moveQueue, const char &x, const char &y, const unsigned char &direction, const unsigned char &currentChecker, const bool &forBlack);
	void checkQueenMoveOnDirection(Queue<Move> &moveQueue, const char &x, const char &y, const unsigned char &direction, const unsigned char &currentChecker, const bool &forBlack);
	void generateBattleMove(Queue<Move> &moveQueue, Move &move, const char &x, const char &y, const bool &forBlack);
	bool checkPependicular(Queue<Move> &moveQueue, Move &move, const char &x, const char &y, const unsigned char &direction, const bool &forBlack);
	char removeFromField(const unsigned char &x, const unsigned char &y, const bool &fromBlack);
	void addToField(const char &index, const bool &fromBlack);
	void getPerpendicularDirections(const unsigned char &direction, unsigned char &leftDirection, unsigned char &rightDirection);
	bool checkBattleMoveOnDirection(Queue<Move> &moveQueue, Move move, const unsigned char &direction, const char &x, const char &y, const bool &forBlack);

	Queue<Move> * generateMoves(const bool &forBlack);
	void makeMove(Move &move, const bool &isBlack, char &index, unsigned char &oldValue, Stack<char> &defeatedCheckersIndexes);
	void makeMoveInGame(Move &move, const bool &isBlack);
	void unmakeMove(const bool &isBlack, char &index, unsigned char &oldValue, Stack<char> &defeatedCheckersIndexes);
	int search(const bool forBlack, short alpha, short beta, char depth);
	char evaluate(const bool &forBlack);

	inline char getXCoor(const unsigned char &checker);
	inline char getYCoor(const unsigned char &checker);
	Position getDirectionShift(const unsigned char &direction);
	inline bool inMap(const char &x, const char &y);
	inline bool isEnemy(const unsigned char &checker, const bool &forBlack);
	inline bool isEmptyField(const char &x, const char &y);//опасная функция не проверяет на выход за карту
	inline unsigned char getChecker(const char &x, const char &y);//опасная функция не проверяет пустое ли поле и выход за карту
	bool canExecBattleMove(const char &x, const char &y, const char &xNext, const char &yNext, const bool &forBlack);//опасная функция не проверяет пустое ли поле и выход за карту
	inline bool checkerBecameQueen(const char &y, const bool &forBlack);
	inline bool canPawnSilentMoveInDirection(const bool &forBlack, const char &yShift);
	inline bool onField(const char &index, const bool &isBlack);
	inline char calculateShift(const char &firstCord, const char &secondCord);

	inline void defineSideArr(unsigned char *&checkersArr, const bool &isBlack);
	inline unsigned char defineSideArrLength(const bool &isBlack);
	char getUndefeatedCheckerIndex(const char &x, const char &y, const bool &fromBlack);

	bool playerMoveConsole(const bool &forBlack);
	void computerMoveConsole(const bool &forBlack);


public:
	Checkers(char * whiteChekersStr, char * blackCheckersStr, char startDepth = 3); //если строка не корректна вернуть exception
	~Checkers();
	Move getNextMove(const bool &isBlack);
	void printCheckersField();
	void playTestConsole(const bool &forBlackSide);
	void setStartDepth(const char startDepth);
	void printAvailableMoves(const bool &forBlack);
	void computerMoveInfo(const bool &forBlack);

	void makeMoveFromString(const char * moveStr, const bool &isBattle, const bool &forBlack);
	void printGameStateInStr();
};

