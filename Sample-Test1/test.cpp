#include "pch.h"
#include "../9MensMorris/Board.h"

TEST(TestCaseName, TestName) {
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  ASSERT_EQ(chk, true);
}