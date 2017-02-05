#include "Checkers.h"

void Checkers::parseCheckersString(char * str, unsigned char *& array, bool isBlack) {
	unsigned char checkersCount = strlen(str) / 3;
	array = new unsigned char[checkersCount];

	for (char i = 0; i < checkersCount; ++i) {
		unsigned char checker = 0;
		checker |= (str[i * NUMB_IN_STR_FOR_ONE_CHECKER] - 'a');
		checker |= (str[i * NUMB_IN_STR_FOR_ONE_CHECKER + 1] - '1') * 8;
		if (str[i * NUMB_IN_STR_FOR_ONE_CHECKER + 2] == '1')
			checker |= QUEEN_FLAG;
		if (isBlack){
			checker |= BLACK_COLOR_FLAG;
			_blackCheckersCount = checkersCount;
		}
		else {
			_whiteCheckersCount = checkersCount;
		}

		array[i] = checker;
	}
}

char Checkers::getXCoor(const unsigned char &checker)
{
	return checker & 7;
}

char Checkers::getYCoor(const unsigned char &checker)
{
	return (checker & 56) / 8;
}

bool Checkers::inMap(const char &x, const char &y)
{
	return (x < FIELD_ROW_SIZE && y < FIELD_ROW_SIZE && x >= 0 && y >= 0);
}

bool Checkers::isEmptyField(const char &x, const char &y)
{
	return _checkersField[x + FIELD_ROW_SIZE * y] == NULL;
}

bool  Checkers::isEnemy(const unsigned char &checker, const bool &forBlack)
{
	return (forBlack ^ ((checker & BLACK_COLOR_FLAG) / BLACK_COLOR_FLAG));
}

unsigned char Checkers::getChecker(const char &x, const char &y)//опасная функция не проверяет пустое ли поле
{
	return (*_checkersField[x + FIELD_ROW_SIZE * y]);
}

//опасная функция не проверяет пустое ли поле
bool Checkers::canExecBattleMove(const char &x, const char &y, const char &xNext, const char &yNext, const bool &forBlack)
{
	unsigned char checker = getChecker(x, y);//опасная функция не проверяет пустое ли поле
	return isEnemy(checker, forBlack) && (getUndefeatedCheckerIndex(x, y, !forBlack) != -1) && inMap(xNext, yNext) && isEmptyField(xNext, yNext);
}

bool Checkers::checkerBecameQueen(const char &y, const bool &forBlack)
{
	return (forBlack && y == 0) || (!forBlack && y == (FIELD_ROW_SIZE - 1));
}

bool Checkers::canPawnSilentMoveInDirection(const bool &forBlack, const char &yShift)
{
	return (forBlack && yShift < 0) || (!forBlack && yShift > 0);
}

bool Checkers::onField(const char &index, const bool &isBlack)// заменено isEmptyFields в generateMoves
{
	return !_defeatedMarker.isKnockedDown(index, isBlack);
}

void Checkers::defineSideArr(unsigned char *&checkersArr, const bool &isBlack)
{
	if (isBlack) checkersArr = _blackCheckers;
	else checkersArr = _whiteCheckers;
}

unsigned char Checkers::defineSideArrLength(const bool &isBlack)
{
	if (isBlack) return _blackCheckersCount;
	else return _whiteCheckersCount;
}

char Checkers::getUndefeatedCheckerIndex(const char &x, const char &y, const bool &fromBlack)
{
	unsigned char checker = getChecker(x, y);
	unsigned char *checkersArr;
	defineSideArr(checkersArr, fromBlack);
	unsigned char arrLength = defineSideArrLength(fromBlack);

	for (char i = 0; i < arrLength; ++i)
	{
		if (checkersArr[i] == checker && !_defeatedMarker.isKnockedDown(i, fromBlack)) return i;
	}
	return -1;
}

char Checkers::calculateShift(const char &firstCord, const char &secondCord)
{
	return (secondCord - firstCord > 0 ? 1 : -1);
}

void Checkers::setStartDepth(const char startDepth)
{
	if (startDepth < 1) _startDepth = 1;
	else _startDepth = startDepth;
}

void Checkers::placeCheckersOnField()
{
	for (char i = 0; i < FIELD_LENGTH; ++i) {
		//_defeatedMarker.markKnockedDown(i, true);
		//_defeatedMarker.markKnockedDown(i, false);
	}
	for (char i = 0; i < _whiteCheckersCount; ++i) {
		unsigned char x = getXCoor(_whiteCheckers[i]);
		unsigned char y = getYCoor(_whiteCheckers[i]);
		_checkersField[x + FIELD_ROW_SIZE * y] = &_whiteCheckers[i];
		//_defeatedMarker.unmarkKnockedDown(x + FIELD_ROW_SIZE * y, false);
	}
	for (char i = 0; i < _blackCheckersCount; ++i) {
		unsigned char x = getXCoor(_blackCheckers[i]);
		unsigned char y = getYCoor(_blackCheckers[i]);
		_checkersField[x + FIELD_ROW_SIZE * y] = &_blackCheckers[i];
		//_defeatedMarker.unmarkKnockedDown(x + FIELD_ROW_SIZE * y, true);
	}
}

void Checkers::printCheckersField()
{
	int maxNumber = FIELD_ROW_SIZE;
	for (char i = FIELD_ROW_SIZE - 1; i >= 0; --i)
	{
		cout << maxNumber << " ";
		for (char j = 0; j < FIELD_ROW_SIZE; ++j)
		{
			if (_checkersField[j + FIELD_ROW_SIZE * i] == NULL) cout << '-';
			else {
				unsigned char currentChecker = (*_checkersField[j + FIELD_ROW_SIZE * i]);
				if (currentChecker & QUEEN_FLAG) {
					if (currentChecker & BLACK_COLOR_FLAG) cout << 4;
					else cout << 3;
				}
				else {
					if (currentChecker & BLACK_COLOR_FLAG) cout << 1;
					else cout << 0;
				}
			}
			/*if (_checkersField[j + FIELD_ROW_SIZE * i] == NULL) cout << setw(3) << "---";
			else cout << setw(3) << (int) (*_checkersField[j + FIELD_ROW_SIZE * i]);*/
		}
		cout << endl;
		--maxNumber;
	}
	cout << "  ";
	char firstLetter = 'a';
	for (int i = 0; i < FIELD_ROW_SIZE; ++i) {
		cout << firstLetter;
		++firstLetter;
	}
	cout << endl;
}

Checkers::Checkers(char * whiteChekersStr, char * blackCheckersStr, char startDepth)
{
	_whiteCheckers = NULL;
	_blackCheckers = NULL;
	for (int i = 0; i < FIELD_LENGTH; ++i) _checkersField[i] = NULL;
	//_checkersField = NULL;
	parseCheckersString(whiteChekersStr, _whiteCheckers, 0);
	parseCheckersString(blackCheckersStr, _blackCheckers, 1);
	placeCheckersOnField();
	setStartDepth(startDepth);
}

//возможно функцию getPosition стоит сделать const
//может стоит вражеские позиции для сбиваемых пешек отмечать во время хода
void Checkers::makeMove(Move &move, const bool &isBlack, char &index, unsigned char &oldValue, Stack<char> &defeatedCheckersIndexes)
{
	unsigned char * currentColorCheckers;
	defineSideArr(currentColorCheckers, isBlack);

	Position position = move.getPosition(1);

	oldValue = (*_checkersField[position._x + FIELD_ROW_SIZE * position._y]);
	index = removeFromField(position._x, position._y, isBlack);

	char enemyX;
	char enemyY;
	bool checkerIsQueen = oldValue & QUEEN_FLAG;
	if (move.isBattleMove()) {
		Position newPosition;
		for (int i = 2; i <= move.Length(); ++i) { //для move.Length что то еще сделать
			newPosition = move.getPosition(i);
			if (checkerIsQueen) {
				char xShift = calculateShift(position._x, newPosition._x);//можно вынести в отдельную inline функцию
				char yShift = calculateShift(position._y, newPosition._y);
				enemyX = position._x + xShift;
				enemyY = position._y + yShift;
				while (enemyX != newPosition._x) {
					if (!isEmptyField(enemyX, enemyY) && isEnemy(getChecker(enemyX, enemyY), isBlack)) {
						defeatedCheckersIndexes.push(removeFromField(enemyX, enemyY, !isBlack));
					}
					enemyX += xShift;
					enemyY += yShift;
				}
			}
			else {
				enemyX = position._x + calculateShift(position._x, newPosition._x);
				enemyY = position._y + calculateShift(position._y, newPosition._y);
				defeatedCheckersIndexes.push(removeFromField(enemyX, enemyY, !isBlack));
			}
			position = newPosition;
			checkerIsQueen |= this->checkerBecameQueen(position._y, isBlack);
		}
	}
	position = move.getPosition(move.Length());
	checkerIsQueen |= this->checkerBecameQueen(position._y, isBlack);

	unsigned char newChecker = position._x | position._y * 8;
	newChecker |= checkerIsQueen * QUEEN_FLAG | isBlack * BLACK_COLOR_FLAG;
	currentColorCheckers[index] = newChecker;
	addToField(index, isBlack);
}

void Checkers::makeMoveInGame(Move &move, const bool &isBlack)
{
	unsigned char * currentColorCheckers;
	defineSideArr(currentColorCheckers, isBlack);

	Position position = move.getPosition(1);

	unsigned char oldValue = (*_checkersField[position._x + FIELD_ROW_SIZE * position._y]);
	char index = removeFromField(position._x, position._y, isBlack);

	char enemyX;
	char enemyY;
	bool checkerIsQueen = oldValue & QUEEN_FLAG;
	if (move.isBattleMove()) {
		Position newPosition;
		for (int i = 2; i <= move.Length(); ++i) { //для move.Length что то еще сделать
			newPosition = move.getPosition(i);
			if (checkerIsQueen) {
				char xShift = calculateShift(position._x, newPosition._x);//можно вынести в отдельную inline функцию
				char yShift = calculateShift(position._y, newPosition._y);
				enemyX = position._x + xShift;
				enemyY = position._y + yShift;
				while (enemyX != newPosition._x) {
					if (!isEmptyField(enemyX, enemyY) && isEnemy(getChecker(enemyX, enemyY), isBlack)) {
						removeFromField(enemyX, enemyY, !isBlack);
					}
					enemyX += xShift;
					enemyY += yShift;
				}
			}
			else {
				enemyX = position._x + calculateShift(position._x, newPosition._x);
				enemyY = position._y + calculateShift(position._y, newPosition._y);
				removeFromField(enemyX, enemyY, !isBlack);
			}
			position = newPosition;
			checkerIsQueen |= this->checkerBecameQueen(position._y, isBlack);
		}
	}
	position = move.getPosition(move.Length());
	checkerIsQueen |= this->checkerBecameQueen(position._y, isBlack);

	unsigned char newChecker = position._x | position._y * 8;
	newChecker |= checkerIsQueen * QUEEN_FLAG | isBlack * BLACK_COLOR_FLAG;
	currentColorCheckers[index] = newChecker;
	addToField(index, isBlack);
}

void Checkers::unmakeMove(const bool &isBlack, char &index, unsigned char &oldValue, Stack<char> &defeatedCheckersIndexes)
{
	while (!defeatedCheckersIndexes.isEmpty()) addToField(defeatedCheckersIndexes.pop(), !isBlack);

	unsigned char * currentColorCheckers;
	if (isBlack) currentColorCheckers = _blackCheckers;
	else currentColorCheckers = _whiteCheckers;

	unsigned char newValue = currentColorCheckers[index];

	removeFromField(getXCoor(newValue), getYCoor(newValue), isBlack);
	currentColorCheckers[index] = oldValue;
	addToField(index, isBlack);
}

//проверка на отсутсвия ходов противоположной стороны при трети фигурах это продположение, предположение о цене дамки
char Checkers::evaluate(const bool &forBlack)
{
	char thirdFigures = 4; //проверка на отсутсвия ходов противоположной стороны при трети фигур
	char queenEvaluation = 3; //предположительная оценка дамки, возможно ее стоит менять от кол. фигур или обстановки на поле

	char blackPawnCount = 0;
	char whitePawnCount = 0;
	char blackQueenCount = 0;
	char whiteQueenCount = 0;

	for (char i = 0; i < FIELD_LENGTH; ++i) {
		if (_checkersField[i] != NULL) {
			unsigned char currentChecker = (*_checkersField[i]);
			if (currentChecker & BLACK_COLOR_FLAG) {
				if (currentChecker & QUEEN_FLAG) ++blackQueenCount;
				else ++blackPawnCount;
			}
			else {
				if (currentChecker & QUEEN_FLAG) ++whiteQueenCount;
				else ++whitePawnCount;
			}
		}
	}

	char superiorityDifference = (blackPawnCount + blackQueenCount * queenEvaluation) - (whitePawnCount + whiteQueenCount * queenEvaluation);
	if (forBlack) return superiorityDifference;
	else return -superiorityDifference;
}

int Checkers::search(const bool forBlack, short alpha, short beta, char depth)
{
	wasBattleMove = false;
	short score = -NO_MOVES;
	short tmp = alpha;

	if (depth <= 0) return evaluate(forBlack);

	Queue<Move> * moveQueue = generateMoves(forBlack);
	while (!moveQueue->isEmpty() && alpha < beta) {
		Move move = moveQueue->dequeue();
		if (!wasBattleMove || move.isBattleMove()) {
			char index;
			unsigned char oldValue;
			Stack<char> defeatedCheckersIndexes;
			bool currentWasBattleMove = wasBattleMove;

			/*	cout << "forBlack = " << forBlack << ", depth = " << (int) depth << endl;
			this->printCheckersField();
			move.printMove();*/

			makeMove(move, forBlack, index, oldValue, defeatedCheckersIndexes);
			/*this->printCheckersField();
			cout << endl;*/

			//tmp = -search(!forBlack, -(alpha + 1), -alpha, depth - 1);
			//if (tmp > alpha && tmp < beta) {
				tmp = -search(!forBlack, -beta, -tmp, depth - 1);
			//}

			unmakeMove(forBlack, index, oldValue, defeatedCheckersIndexes);
			wasBattleMove = currentWasBattleMove;

			if (tmp > score) score = tmp;
			if (score > alpha) alpha = score;
		}
	}
	delete moveQueue;
	return score - DEPTH_VALUE * depth;
}

Move Checkers::getNextMove(const bool &isBlack)//нужно правильно описать, если первый ход лучший
{
	wasBattleMove = false;
	short score = -INF_SUPERIORITY;
	short tmp = -INF_SUPERIORITY;

	short alpha = -INF_SUPERIORITY;
	short beta = INF_SUPERIORITY;


	Queue<Move> * moveQueue = generateMoves(isBlack);
	Move bestMove;

	if (moveQueue->isEmpty()) {
		throw VictoryException();
	}

	while (!moveQueue->isEmpty() && alpha < beta) {
		Move move = moveQueue->dequeue();
		if (!wasBattleMove || move.isBattleMove()) {
			char index;
			unsigned char oldValue;
			Stack<char> defeatedCheckersIndexes;
			bool currentWasBattleMove = wasBattleMove;

			/*	this->printCheckersField();
			move.printMove();*/

			makeMove(move, isBlack, index, oldValue, defeatedCheckersIndexes);
			/*	cout << "after move forBlack = " << isBlack << ", depth = " << startDepth + 1 << endl;
			this->printCheckersField();
			cout << endl;*/

			//tmp = -search(!isBlack, -(alpha + 1), -alpha, _startDepth);
			//if (tmp > alpha && tmp < beta) {
				tmp = -search(!isBlack, -beta, -tmp, _startDepth);
			//}

			unmakeMove(isBlack, index, oldValue, defeatedCheckersIndexes);
			wasBattleMove = currentWasBattleMove;

			if (tmp > score) {
				score = tmp;
				bestMove = move;
			}
			if (score > alpha) alpha = score;
			/*move.printMove();
			cout << (int)tmp << endl;*/
		}
	}
	delete moveQueue;

	return bestMove;
}

Queue<Move> *Checkers::generateMoves(const bool &forBlack)
{
	unsigned char * currentColorCheckers;
	defineSideArr(currentColorCheckers, forBlack);
	unsigned char currentColorCheckersCount = defineSideArrLength(forBlack);

	Queue<Move> *moveQueue = new Queue<Move>();
	for (char i = 0; i < currentColorCheckersCount; ++i) {
		unsigned char currentChecker = currentColorCheckers[i];

		char x = getXCoor(currentChecker);
		char y = getYCoor(currentChecker);

		if (onField(i, forBlack) && !isEmptyField(x, y))
			if (currentChecker & QUEEN_FLAG) {
				checkQueenMoveOnDirection((*moveQueue), x, y, NE, currentChecker, forBlack);
				checkQueenMoveOnDirection((*moveQueue), x, y, NW, currentChecker, forBlack);
				checkQueenMoveOnDirection((*moveQueue), x, y, SE, currentChecker, forBlack);
				checkQueenMoveOnDirection((*moveQueue), x, y, SW, currentChecker, forBlack);
			}
			else {
				checkMoveOnDirection((*moveQueue), x, y, NE, currentChecker, forBlack); //можно тут проверять направление в зависимости от цвета
				checkMoveOnDirection((*moveQueue), x, y, NW, currentChecker, forBlack);
				checkMoveOnDirection((*moveQueue), x, y, SE, currentChecker, forBlack);
				checkMoveOnDirection((*moveQueue), x, y, SW, currentChecker, forBlack);
			}
	}
	return moveQueue;
}

Position Checkers::getDirectionShift(const unsigned char &direction) {
	Position shift;
	switch (direction) {
	case NE:
		shift._x = 1;
		shift._y = 1;
		break;
	case SE:
		shift._x = 1;
		shift._y = -1;
		break;
	case SW:
		shift._x = -1;
		shift._y = -1;
		break;
	case NW:
		shift._x = -1;
		shift._y = 1;
		break;
	}
	return shift;
}

void Checkers::getPerpendicularDirections(const unsigned char &direction, unsigned char &leftDirection, unsigned char &rightDirection)
{
	switch (direction)
	{
	case NE:
		leftDirection = NW;
		rightDirection = SE;
		break;
	case SE:
		leftDirection = NE;
		rightDirection = SW;
		break;
	case SW:
		leftDirection = SE;
		rightDirection = NW;
		break;
	case NW:
		leftDirection = SW;
		rightDirection = NE;
		break;
	}
}

void Checkers::checkMoveOnDirection(Queue<Move> &moveQueue, const char &x, const char &y, const unsigned char &direction, const unsigned char &currentChecker, const bool &forBlack)
{
	Position shift = getDirectionShift(direction);

	char xWithShift = x + shift._x;
	char yWithShift = y + shift._y;

	if (inMap(xWithShift, yWithShift)) {
		if (isEmptyField(xWithShift, yWithShift)) {
			if (canPawnSilentMoveInDirection(forBlack, shift._y) && !wasBattleMove) {
				Move newMove(currentChecker, false);
				newMove.addPosition(xWithShift, yWithShift);
				moveQueue.enqueue(newMove);
			}
		}
		else {
			char xWithShiftNext = xWithShift + shift._x;
			char yWithShiftNext = yWithShift + shift._y;

			if (canExecBattleMove(xWithShift, yWithShift, xWithShiftNext, yWithShiftNext, forBlack)) {
				wasBattleMove = true;
				Move newMove(currentChecker, true);
				newMove.addPosition(xWithShiftNext, yWithShiftNext);

				char defeatedIndex = getUndefeatedCheckerIndex(xWithShift, yWithShift, !forBlack);
				_defeatedMarker.markKnockedDown(defeatedIndex, !forBlack);

				//this->printCheckersField();
				char warriorCheckerIndex = removeFromField(x, y, forBlack);
				if (checkerBecameQueen(yWithShiftNext, forBlack)) {
					unsigned char leftDirection;
					unsigned char rightDirection;
					getPerpendicularDirections(direction, leftDirection, rightDirection);
					bool hasNoEnemyOnperpendicular = true;
					hasNoEnemyOnperpendicular &= checkPependicular(moveQueue, newMove, xWithShiftNext, yWithShiftNext, leftDirection, forBlack);
					hasNoEnemyOnperpendicular &= checkPependicular(moveQueue, newMove, xWithShiftNext, yWithShiftNext, rightDirection, forBlack);
					if (hasNoEnemyOnperpendicular) moveQueue.enqueue(newMove);
				}
				else generateBattleMove(moveQueue, newMove, xWithShiftNext, yWithShiftNext, forBlack);

				addToField(warriorCheckerIndex, forBlack);
				_defeatedMarker.unmarkKnockedDown(defeatedIndex, !forBlack);
				//addToField(defeatedIndex, !forBlack);
				//this->printCheckersField();
			}
		}
	}
}

void Checkers::checkQueenMoveOnDirection(Queue<Move> &moveQueue, const char &x, const char &y, const unsigned char &direction, const unsigned char &currentChecker, const bool &forBlack)
{
	bool wasBattleMoveLocal = false;
	Position shift = getDirectionShift(direction);
	char warriorCheckerIndex = removeFromField(x, y, forBlack);

	char xWithShift = x + shift._x;
	char yWithShift = y + shift._y;
	char lastEnemiesXPos = x;
	bool noEnemiesOnPerpendicular = true;
	Stack<char> defeatedIndexesStack;

	unsigned char leftPerpendicularDirection;
	unsigned char rightPerpendicularDirection;
	getPerpendicularDirections(direction, leftPerpendicularDirection, rightPerpendicularDirection);

	while (inMap(xWithShift, yWithShift)) {
		if (isEmptyField(xWithShift, yWithShift)) {
			if (lastEnemiesXPos != x) {
				Move newMove(currentChecker, true);
				newMove.addPosition(xWithShift, yWithShift);
				noEnemiesOnPerpendicular &= checkPependicular(moveQueue, newMove, xWithShift, yWithShift, leftPerpendicularDirection, forBlack);
				noEnemiesOnPerpendicular &= checkPependicular(moveQueue, newMove, xWithShift, yWithShift, rightPerpendicularDirection, forBlack);
			}
		}
		else if (canExecBattleMove(xWithShift, yWithShift, xWithShift + shift._x, yWithShift + shift._y, forBlack)) {
			wasBattleMove = true;
			wasBattleMoveLocal = true;
			lastEnemiesXPos = xWithShift;
			char defeatedIndex = getUndefeatedCheckerIndex(xWithShift, yWithShift, !forBlack);
			_defeatedMarker.markKnockedDown(defeatedIndex, !forBlack);
			defeatedIndexesStack.push(defeatedIndex);
		}
		else break;
		xWithShift += shift._x;
		yWithShift += shift._y;
	}

	if ((noEnemiesOnPerpendicular || defeatedIndexesStack.Length() > 1) && (wasBattleMoveLocal || !wasBattleMove)) {
		xWithShift -= shift._x;
		yWithShift -= shift._y;
		while (xWithShift != lastEnemiesXPos) {
			Move newMove(currentChecker, wasBattleMoveLocal);
			newMove.addPosition(xWithShift, yWithShift);
			moveQueue.enqueue(newMove);
			xWithShift -= shift._x;
			yWithShift -= shift._y;
		}
	}
	while (defeatedIndexesStack.Length() > 0) _defeatedMarker.unmarkKnockedDown(defeatedIndexesStack.pop(), !forBlack);
	addToField(warriorCheckerIndex, forBlack);
}

char Checkers::removeFromField(const unsigned char &x, const unsigned char &y, const bool &fromBlack) {
	char index = getUndefeatedCheckerIndex(x, y, fromBlack);
	_defeatedMarker.markKnockedDown(index, fromBlack);
	_checkersField[x + FIELD_ROW_SIZE * y] = NULL;
	return index;
}
void Checkers::addToField(const char &index, const bool &fromBlack) {
	_defeatedMarker.unmarkKnockedDown(index, fromBlack);
	unsigned char * checkersArr;
	defineSideArr(checkersArr, fromBlack);
	char x = getXCoor(checkersArr[index]);
	char y = getYCoor(checkersArr[index]);
	_checkersField[x + FIELD_ROW_SIZE * y] = &checkersArr[index];
}

//можно оптимизировать не заходить в одно из направлений
void Checkers::generateBattleMove(Queue<Move> &moveQueue, Move &move, const char &x, const char &y, const bool &forBlack)
{
	bool noEnemyOnDirection = true;

	noEnemyOnDirection &= checkBattleMoveOnDirection(moveQueue, move, NE, x, y, forBlack);
	noEnemyOnDirection &= checkBattleMoveOnDirection(moveQueue, move, SE, x, y, forBlack);
	noEnemyOnDirection &= checkBattleMoveOnDirection(moveQueue, move, SW, x, y, forBlack);
	noEnemyOnDirection &= checkBattleMoveOnDirection(moveQueue, move, NW, x, y, forBlack);

	if (noEnemyOnDirection)	moveQueue.enqueue(move);
}

//потом изменить порядок, два раза один код
bool Checkers::checkPependicular(Queue<Move> &moveQueue, Move &move, const char &x, const char &y, const unsigned char &direction, const bool &forBlack)
{
	Position shift = getDirectionShift(direction);

	unsigned char leftPerpendicularDirection;
	unsigned char rightPerpendicularDirection;
	getPerpendicularDirections(direction, leftPerpendicularDirection, rightPerpendicularDirection);

	char lastEnemiesXPos = x;
	bool noEnemiesOnPerpendicular = true;

	Stack<char> defeatedIndexesStack;

	char xWithShift = x + shift._x;
	char yWithShift = y + shift._y;

	while (inMap(xWithShift, yWithShift)) {
		if (isEmptyField(xWithShift, yWithShift)) {
			if (lastEnemiesXPos != x) {
				Move newMove = move;
				newMove.addPosition(xWithShift, yWithShift);
				noEnemiesOnPerpendicular &= checkPependicular(moveQueue, newMove, xWithShift, yWithShift, leftPerpendicularDirection, forBlack);
				noEnemiesOnPerpendicular &= checkPependicular(moveQueue, newMove, xWithShift, yWithShift, rightPerpendicularDirection, forBlack);
			}
		}
		else if (canExecBattleMove(xWithShift, yWithShift, xWithShift + shift._x, yWithShift + shift._y, forBlack)) {
			lastEnemiesXPos = xWithShift;
			char defeatedIndex = getUndefeatedCheckerIndex(xWithShift, yWithShift, !forBlack);
			_defeatedMarker.markKnockedDown(defeatedIndex, !forBlack);
			defeatedIndexesStack.push(defeatedIndex);
		}
		else break;

		xWithShift += shift._x;
		yWithShift += shift._y;
	}

	if ((noEnemiesOnPerpendicular && lastEnemiesXPos != x) || defeatedIndexesStack.Length() > 1) {
		xWithShift -= shift._x;
		yWithShift -= shift._y;
		while (xWithShift != lastEnemiesXPos) {
			Move newMove = move;
			newMove.addPosition(xWithShift, yWithShift);
			moveQueue.enqueue(newMove);
			xWithShift -= shift._x;
			yWithShift -= shift._y;
		}
		while (defeatedIndexesStack.Length() > 0) _defeatedMarker.unmarkKnockedDown(defeatedIndexesStack.pop(), !forBlack);
		return false;
	}
	while (defeatedIndexesStack.Length() > 0) _defeatedMarker.unmarkKnockedDown(defeatedIndexesStack.pop(), !forBlack);//потом изменить порядок
	return lastEnemiesXPos == x;
}

bool Checkers::checkBattleMoveOnDirection(Queue<Move> &moveQueue, Move move, const char unsigned &direction, const char &x, const char &y, const bool &forBlack) {
	Position shift = getDirectionShift(direction);

	char xWithShift = x + shift._x;
	char yWithShift = y + shift._y;

	char xWithShiftNext = xWithShift + shift._x;
	char yWithShiftNext = yWithShift + shift._y;

	if (inMap(xWithShift, yWithShift) && !isEmptyField(xWithShift, yWithShift) && canExecBattleMove(xWithShift, yWithShift, xWithShiftNext, yWithShiftNext, forBlack)) {
		move.addPosition(xWithShiftNext, yWithShiftNext);

		char defeatedIndex = getUndefeatedCheckerIndex(xWithShift, yWithShift, !forBlack);
		_defeatedMarker.markKnockedDown(defeatedIndex, !forBlack);
		//	this->printCheckersField();
		generateBattleMove(moveQueue, move, xWithShiftNext, yWithShiftNext, forBlack);
		_defeatedMarker.unmarkKnockedDown(defeatedIndex, !forBlack);
		//	this->printCheckersField();
		return false;
	}
	return true;
}

Checkers::~Checkers()
{
	delete[] _whiteCheckers;
	delete[] _blackCheckers;
}

void Checkers::printAvailableMoves(const bool &forBlack)
{
	wasBattleMove = false;
	int moveIndex = 1;

	Queue<Move> * moveQueue = generateMoves(forBlack);
	vector<Move> moveVector;
	while (!moveQueue->isEmpty()) {
		Move move = moveQueue->dequeue();
		if (!wasBattleMove || move.isBattleMove()){
			move.printMove();
			moveVector.push_back(move);
			++moveIndex;
		}
	}
}

bool Checkers::playerMoveConsole(const bool &forBlack)
{
	wasBattleMove = false;
	int moveIndex = 1;

	Queue<Move> * moveQueue = generateMoves(forBlack);
	vector<Move> moveVector;

	cout << "Available moves: " << endl;
	if (moveQueue->isEmpty()) {
		cout << "Your have no moves!!!" << endl;
		return false;
	}

	while (!moveQueue->isEmpty()) {
		Move move = moveQueue->dequeue();
		if (!wasBattleMove || move.isBattleMove()){
			cout << moveIndex << ": ";
			move.printMove();
			moveVector.push_back(move);
			++moveIndex;
		}
	}

	cout << "Enter move index: ";
	cin >> moveIndex;
	makeMoveInGame(moveVector[moveIndex - 1], forBlack);

	printCheckersField();
	cout << endl;
	delete moveQueue;
	return true;
}

void Checkers::computerMoveConsole(const bool &forBlack)
{
	Move computerMove = getNextMove(!forBlack);
	if (&computerMove == NULL) return;

	cout << "Computer move - ";
	computerMove.printMove();
	makeMoveInGame(computerMove, !forBlack);
	this->printCheckersField();
}
void Checkers::makeMoveFromString(const char * moveStr, const bool &isBattle, const bool &forBlack)
{
	Move move;
	move.strToMove(moveStr, isBattle);
	makeMoveInGame(move, forBlack);
	printGameStateInStr();
}
void Checkers::computerMoveInfo(const bool &forBlack)
{
	Move computerMove = getNextMove(forBlack);
	computerMove.printMove();
	makeMoveInGame(computerMove, forBlack);
	printGameStateInStr();

	this->printAvailableMoves(!forBlack);
}

void Checkers::printGameStateInStr()
{
	////вывести новое состояние поля доступное для php скрипта
	////вывод белых
	//for (int i = 0; i < _whiteCheckersCount; ++i) {
	//	//превратить в строку и вывести
	//	unsigned char checker = _whiteCheckers[i];
	//	char x = getXCoor(checker);
	//	char y = getYCoor(checker);
	//	int isQueen = checker & QUEEN_FLAG;
	//	if (_checkersField[x + FIELD_ROW_SIZE * y] != NULL && !_defeatedMarker.isKnockedDown(x + FIELD_ROW_SIZE * y, false)) {
	//		//выводить на экран позицию
	//		cout << (char)(x + 'a') << y + 1 << (isQueen ? 1 : 0);
	//	}
	//}
	//cout << endl;

	////вывод черных
	//for (int i = 0; i < _blackCheckersCount; ++i) {
	//	//превратить в строку и вывести
	//	unsigned char checker = _blackCheckers[i];
	//	char x = getXCoor(checker);
	//	char y = getYCoor(checker);
	//	int isQueen = checker & QUEEN_FLAG;
	//	if (_checkersField[x + FIELD_ROW_SIZE * y] != NULL && !_defeatedMarker.isKnockedDown(x + FIELD_ROW_SIZE * y, true)) {
	//		//выводить на экран позицию
	//		cout << (char)(x + 'a') << y + 1 << (isQueen ? 1 : 0);
	//	}
	//}
	//cout << endl;
	string whiteCheckers = "";
	string blackCheckers = "";
	for (char i = 0; i < FIELD_ROW_SIZE; ++i)
	{
		for (char j = 0; j < FIELD_ROW_SIZE; ++j)
		{
			if (_checkersField[i + FIELD_ROW_SIZE * j] != NULL) {
				unsigned char currentChecker = (*_checkersField[i + FIELD_ROW_SIZE * j]);
				if (currentChecker & BLACK_COLOR_FLAG) {
					blackCheckers += (char)(i + 'a');
					blackCheckers += (char)(j + 1 + '0');
					blackCheckers += ((currentChecker & QUEEN_FLAG) ? '1' : '0');
				}
				else {
					whiteCheckers += (char)(i + 'a');
					whiteCheckers += (char)(j + 1 + '0');
					whiteCheckers += ((currentChecker & QUEEN_FLAG) ? '1' : '0');
				}
			}
		}
	}
	cout << whiteCheckers << endl;
	cout << blackCheckers << endl;
}

void Checkers::playTestConsole(const bool &forBlackSide)
{
	printCheckersField();
	cout << endl;

	if (forBlackSide) {
		do {
			computerMoveConsole(forBlackSide);
		} while (playerMoveConsole(forBlackSide));
	}
	else {
		while (playerMoveConsole(forBlackSide)) computerMoveConsole(forBlackSide);
	}
}