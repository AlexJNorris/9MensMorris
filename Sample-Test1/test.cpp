#include<Windows.h>    
#include "pch.h"
#include "../9MensMorris/Board.h"

TEST(TestRedPlacement, TestName) {
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  ASSERT_EQ(chk, true);
}

TEST(TestFailedRedPlacement, TestName1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, false);
}

TEST(TestBlackPlacement, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

TEST(TestFailedBlackPlacement, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_EQ(chk, false);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}