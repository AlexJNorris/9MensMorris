#include<Windows.h>    
#include "pch.h"
#include "../9MensMorris/9MensMorris.cpp"
using namespace std;

TEST(TestCaseName, TestName) {
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  ASSERT_EQ(chk, true);
}