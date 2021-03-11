#include "pch.h"
#include "../9MensMorris/Board.h"
#include "Board.h"

TEST(TestCaseName, TestName) {
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  ASSERT_EQ(chk, true);
}

TEST(TestCaseName1, TestName1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, false);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
