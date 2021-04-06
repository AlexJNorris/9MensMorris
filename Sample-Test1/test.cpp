#include<Windows.h>    
#include "pch.h"
#include "../9MensMorris/Board.h"

<<<<<<< Updated upstream:Sample-Test1/test.cpp
TEST(TestRedPlacement, TestName) {
=======
//AC 1.1 Test will initilzie game and it will be player 1's turn
//After player 1 is done will then initialize player 2
TEST(PlayerTurn, Player1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 0);
	Board->turns++;
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 1.2 Test will initilzie game 
//After player 1 makes a move it will be player 2's turn
TEST(PlayerTurn, Player2) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 1.3 Test will incorrectly initilzie game
//It will be player 2's turn without player 1 making a valid move
TEST(PlayerTurn, SkipPlayer1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 0);
}

//AC 1.4 Test will incorrectly initilzie game
//When it should be player 2's turn, the game will still recognize it as player 1's turn
TEST(PlayerTurn, SkipPlayer2) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 1);
}


//AC 3.1 Test placing a red piece at location 0
//After succesful placement should be Player 2's turn
TEST(TestPlacement, RedPlacement) {
>>>>>>> Stashed changes:Sample-Test1/PlacementTests.cpp
	  morisGame* Board = new morisGame;
	  Board->setBoard();
	  Board->setBoardPiece(0);
	  bool chk = Board->boardSpaces[0]->isPlayerOne();
	  EXPECT_EQ(chk, true);
	  Board->turns++;
	  int playerNum = (Board->getTurn() % 2);
	  ASSERT_EQ(playerNum, 1);
}

//AC 3.2 Test placing a black piece at location 0
//After succesful placement should be Player 1's turn
TEST(TestPlacement, BlackPlacement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}

//AC 3.3 Test placing a red piece on location out of range
//Test should cause an exception to be trown since placement is out of range
/*TEST(TestPlacement, InvalidRedPlacement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(-1);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}*/

//AC 3.4 Test placing a red piece on a black piece
//The placement should not be made, and will contunie being player 1's turn.
TEST(TestPlacement, InvalidRedPlacementOnBlack) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	Board->setBoardPieceP2(0);
	Board->turns++;
	bool chk;
	if (Board->boardSpaces[0]->isEmpty()) {
		Board->setBoardPiece(0);
		chk = false;
	}
	else {
		chk = true;
	}
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 1);

}

//AC 3.5 Test placing a black piece on location out of range
//Test should cause an exception to be trown since placement is out of range
/*TEST(TestPlacement, InvalidBlackPlacement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	Board->setBoardPieceP2(-1);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}*/

//AC 3.6 Test placing a black piece on a red piece
//The placement should not be made, and will contunie being player 2's turn.
TEST(TestPlacement, InvalidBlackPlacementOnRed) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	bool chk;
	if (Board->boardSpaces[0]->isEmpty()) {
		Board->setBoardPieceP2(0);
		chk = false;
	}
	else {
		chk = true;
	}
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 0);

}

TEST(TestFailedRedPlacement, TestName1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, false);
}

<<<<<<< Updated upstream:Sample-Test1/test.cpp
TEST(TestBlackPlacement, TestName) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}
=======
>>>>>>> Stashed changes:Sample-Test1/PlacementTests.cpp

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