#pragma once
#include <random>
#include <vector>
#include <map>
#include "Board.h"

using namespace std;

class Computer
{
public:
	Computer();
	int makeMove(morisGame* Board);
private:

	int maxDepth = 6;
	int turn;

	mt19937 random;
	map<long long, pair<long long, int>> stateValues_;
	boardSpace* tmpState_[24];
	vector<int> nextMoves;


	long long minimax(long long currentBoard);
	pair<long long, int> minimax(long long currentBoard, int depth, int a, int b);


};

