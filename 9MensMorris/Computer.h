#pragma once
#include <vector>
#include <map>
#include "Board.h"

using namespace std;

class Computer
{
public:
	Computer();
	int makeMove(morisGame* Board);
	int greedy(morisGame* Board);
private:

	int maxDepth = 2;
	int turn;

	map<long long, pair<long long, int>> stateValues_;
	boardSpace* tmpState_[24];
	vector<int> nextMoves;


};


