// CheckersAlgorithm.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <cstdlib>
#include "Checkers.h"

int main(int argc, char* argv[])
{

	/*checkersTest();
	return 0;*/
	/*int difficultyLevel = strtol("4", NULL, 10);
	char * whiteCheckers = "a10c10e10g10b20d20f20h20a30c30e30g30";
	char * blackCheckers = "b80d80f80h80a70c70e70g70b60d60f60h60";
	bool isPlayerMove = false;
	bool isPlayerColorblack = false;
	char * playerMoveStr = "b4c5";
	bool isBattleMove = 0;*/
	//argc = 9;

	/*for (int i = 0; i < argc; ++i) cout << argv[i] << " ";
	cout << endl;*/
	int difficultyLevel = strtol(argv[1], NULL, 10);
	char * whiteCheckers = argv[2];
	char * blackCheckers = argv[3];
	bool isPlayerMove = strtol(argv[4], NULL, 10);
	bool isPlayerColorblack = strtol(argv[5], NULL, 10);

	Checkers checkers(whiteCheckers, blackCheckers, difficultyLevel - 1);
	if (isPlayerMove) {
		checkers.printAvailableMoves(isPlayerColorblack);
	}
	else {
		try {
			if (argc > 7) {
				char * playerMoveStr = argv[6];
				bool isBattleMove = strtol(argv[7], NULL, 10);
				//checkers.printCheckersField();
				checkers.makeMoveFromString(playerMoveStr, isBattleMove, isPlayerColorblack);
				//checkers.printCheckersField();
			}
			checkers.computerMoveInfo(!isPlayerColorblack);
			//checkers.printCheckersField();
		}
		catch (exception &e) {
			cout << e.what() << endl;
			checkers.printGameStateInStr();
		}
	}
	return 0;
}

