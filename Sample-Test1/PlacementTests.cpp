 
#include "pch.h"
#include "../9MensMorris/Board.h"

//Test placing a red piece at location 0
TEST(TestRedPlacement, TestName) {
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  ASSERT_EQ(chk, true);
}

//Test failing to place a red piece at location 0
/*TEST(TestFailedRedPlacement, TestName1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, false);
}*/

//Test placing a black piece at location 0
TEST(TestBlackPlacement, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//Test failing to place a black piece at location 0
/*TEST(TestFailedBlackPlacement, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_EQ(chk, false);
}*/

//Test new mill placement for player 1
TEST(TestRedMill, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->setBoardPiece(9);
	Board->setBoardPiece(21);
	bool chk = Board->isNewMillMade(0);
	ASSERT_EQ(chk, true);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}