#include "pch.h"
#include "../9MensMorris/Board.h"
#include "../9MensMorris/Computer.h"

//AC 1.1 Test will initialize game and it will be player 1's turn
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

//AC 1.2 Test will initialize game 
//After player 1 makes a move it will be player 2's turn
TEST(PlayerTurn, Player2) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 1.3 Test will incorrectly initialize game
//It will be player 2's turn without player 1 making a valid move
TEST(PlayerTurn, SkipPlayer1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 0);
}

//AC 1.4 Test will incorrectly initialize game
//When it should be player 2's turn, the game will still recognize it as player 1's turn
TEST(PlayerTurn, SkipPlayer2) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 1);
}

//AC 2.1 Successfully create game and should be player 1's turn
TEST(GameboardCreation, Successful) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}

//AC 2.2 Unsuccessfully create new game
//Test should cause an exception to be thrown since the game board was unsuccessfully created.
TEST(GameboardCreation, Unsuccessful) {
	morisGame* Board = new morisGame;
	ASSERT_ANY_THROW(Board->setBoardPiece(0););
	int playerNum = (Board->getTurn() % 2);
	ASSERT_NE(playerNum, 0);
}

//AC 3.1 Test placing a red piece at location 0
//After succesful placement should be Player 2's turn
TEST(TestPlacement, RedPlacement) {
	morisGame * Board = new morisGame;
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
//Test should cause an exception to be thrown since placement is out of range
TEST(TestPlacement, InvalidRedPlacement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	ASSERT_ANY_THROW(Board->setBoardPiece(-1););
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}

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
TEST(TestPlacement, InvalidBlackPlacement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	ASSERT_ANY_THROW(Board->setBoardPieceP2(-1););
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

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

//AC 4.1 Successfully move a red piece to a valid location
TEST(PieceMovement, ValidRedMove) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	Board->moveSelectedToPos(1);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_NE(chk, true);
	chk = Board->boardSpaces[1]->isPlayerOne();
	ASSERT_EQ(chk, true);
}

//AC 4.2 Successfully move a black piece to a valid location
TEST(PieceMovement, ValidBlackMove) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	Board->moveSelectedToPos(1);
	chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_NE(chk, true);
	chk = Board->boardSpaces[1]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 4.3 Unsuccessfully choose a location without a red piece
TEST(PieceMovement, InvalidRedChosen) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(1);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_NE(chk, true);
}

//AC 4.4 Unsuccessfully move a red piece to an invalid location
//Test should cause an exception to be thrown since location to move to is out of range
TEST(PieceMovement, InvalidRedMovement) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	EXPECT_ANY_THROW(Board->moveSelectedToPos(-1));
}

//AC 4.5 Unsuccessfully move a red piece to a location occupied by a black piece
//Piece should not move from the original position and black’s piece will not change
TEST(PieceMovement, InvalidRedMovementOntoBlack) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->setBoardPieceP2(1);
	bool chk = Board->boardSpaces[1]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	if (Board->boardSpaces[1]->isEmpty()){
		Board->moveSelectedToPos(1);
	}
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[1]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 4.6 Unsuccessfully choose a location without a black piece
TEST(PieceMovement, InvalidBlackChosen) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(1);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_NE(chk, true);
}

//AC 4.7 Unsuccessfully move a black piece to an invalid location
//Test should cause an exception to be thrown since location to move to is out of range
TEST(PieceMovement, InvalidRedMovement2) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	ASSERT_ANY_THROW(Board->moveSelectedToPos(-1););
}

//AC 4.8 Unsuccessfully move a Black piece to a location occupied by a Red piece
//Piece should not move from the original position and red’s piece will not change
TEST(PieceMovement, InvalidBlackMovementOntoRed) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	Board->setBoardPiece(1);
	bool chk = Board->boardSpaces[1]->isPlayerOne();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	if (Board->boardSpaces[1]->isEmpty()) {
		Board->moveSelectedToPos(1);
	}
	chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[1]->isPlayerOne();
	ASSERT_EQ(chk, true);
}
 
//AC 5.1 Fly red across board
TEST(Flying, RedFlying) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	Board->moveSelectedToPos(23);
	chk = Board->boardSpaces[23]->isPlayerOne();
	ASSERT_EQ(chk, true);
}

//AC 5.2 Fly black across board
TEST(Flying, BlackFlying) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	Board->moveSelectedToPos(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 5.3 Fail to choose red to fly across board
TEST(Flying, RedFailChoose) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->setBoardPieceP2(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 22;
	if (Board->boardSpaces[22]->isEmpty())
	{
		Board->moveSelectedToPos(1);
	}
	chk = Board->boardSpaces[22]->isEmpty();
	ASSERT_EQ(chk, true);
	chk = Board->boardSpaces[1]->isEmpty();
	ASSERT_EQ(chk, true);
}

//AC 5.4 & 5.5 Fail to Fly red across board
TEST(Flying, RedFailFlying) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->setBoardPieceP2(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 0;
	if (Board->boardSpaces[23]->isEmpty())
	{
		Board->moveSelectedToPos(23);
	}
	chk = Board->boardSpaces[23]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 5.6 Fail to choose black to fly across board
TEST(Flying, BlackFailChoose) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->setBoardPieceP2(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 22;
	if (Board->boardSpaces[22]->isEmpty())
	{
		Board->moveSelectedToPos(1);
	}
	chk = Board->boardSpaces[22]->isEmpty();
	ASSERT_EQ(chk, true);
	chk = Board->boardSpaces[1]->isEmpty();
	ASSERT_EQ(chk, true);
}

//AC 5.7 & 5.8 Fail to Fly black across board
TEST(Flying, BlackFailFlying) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->setBoardPieceP2(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = 23;
	if (Board->boardSpaces[0]->isEmpty())
	{
		Board->moveSelectedToPos(0);
	}
	chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, true);
}

//AC 6.1 Successfully remove a black piece
TEST(Removal, BlackRemoval) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->removePiece(0);
	chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_NE(chk, true);
}

//AC 6.2 Successfully remove a red piece
TEST(Removal, RedRemoval) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->removePiece(0);
	chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_NE(chk, true);
}

//AC 6.3 Unsuccessfully removal of a black piece when an invalid position is chosen for removal
//Test should cause an exception to be thrown since location to remove does not have a piece to remove
TEST(Removal, InvalidBlackRemoval) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	ASSERT_ANY_THROW(Board->removePiece(1););
	chk = Board->boardSpaces[1]->isPlayerTwo();
	ASSERT_NE(chk, true);
}

//AC 6.4 Unsuccessfully removal of a black piece when an invalid position is chosen for removal
TEST(Removal, InvalidRedRemovalByRed) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	if (!Board->boardSpaces[0]->isPlayerOne()) {
		Board->removePiece(0);
	}
	chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_NE(chk, false);
}

//AC 6.5 Unsuccessfully removal of a red piece when an invalid position is chosen for removal
//Test should cause an exception to be thrown since location to remove does not have a piece to remove
TEST(Removal, InvalidRedRemoval) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->removePiece(1);
	chk = Board->boardSpaces[1]->isPlayerOne();
	ASSERT_NE(chk, true);
}


//AC 6.6 Unsuccessfully removal of a black piece when an invalid position is chosen for removal
TEST(Removal, InvalidBlackRemovalByBlack) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	if (!Board->boardSpaces[0]->isPlayerTwo()) {
		Board->removePiece(0);
	}
	chk = Board->boardSpaces[0]->isPlayerTwo();
	ASSERT_NE(chk, false);
}

//AC 7.1 and 7.3 Distinguish red piece
TEST(Distinguish, DistinguishRed) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, false);

}
//AC 7.2 and 7.4 Distinguish black piece
TEST(Distinguish, DistinguishBlack) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPieceP2(0);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, false);
}

//Test failing to place a red piece at location 0
/*TEST(TestFailedRedPlacement, TestName1) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	ASSERT_EQ(chk, false);
}*/

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

//Test new mill placement for both players
TEST(TestMill, TestMillOperations) {
	morisGame* Board = new morisGame;
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->setBoardPiece(9);
	Board->setBoardPiece(21);
	bool chk = Board->isNewMillMade(0);
	ASSERT_EQ(chk, true);
	Board->setBoardPieceP2(3);
	Board->setBoardPieceP2(4);
	Board->setBoardPieceP2(5);
	chk = Board->isNewMillMade(1);
	ASSERT_EQ(chk, true);
	Board->setBoardPiece(1);
	Board->setBoardPiece(2);
	chk = Board->isNewMillMade(0);
	ASSERT_EQ(chk, true);
	Board->removePiece(0);
	chk = Board->isMillBroken(0);
	ASSERT_EQ(chk, true);
	ASSERT_EQ(Board->p1MillArr[0][0], -1);
	ASSERT_EQ(Board->p1MillArr[1][0], -1);
	ASSERT_NE(Board->p2MillArr[0][0], -1);
	ASSERT_EQ(Board->p2MillArr[1][0], -1);
}

//AC 8.1 Test computer placing a black piece after a valid Player move
//Will then be player's turn.
TEST(ComputerPlacement, ValidPlacement) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->turns++;
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}

//AC 8.2 Test computer placing an invalid black piece after a valid Player move
//Will stay computer's turn.
TEST(ComputerPlacement, InvalidPlacement) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = -1;
	EXPECT_ANY_THROW(Board->setBoardPieceP2(pos_););
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 8.3 Test computer placing an invalid black piece on a player's ocupided piece after a valid Player move
//Will stay computer's turn.
TEST(ComputerPlacement, InvalidPlacementOnPlayer) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = 1;
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[0]->isPlayerTwo();
	EXPECT_NE(chk, true);
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}
//AC 9.1 Test computer placing an invalid black piece on a player's ocupided piece after a valid Player move
TEST(ComputerMovement, ValidMovement) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	//check if it's comp's turn
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	Board->setBoardPieceP2(1);
	//check if comp placed a piece on space 1;
	bool chk = Board->boardSpaces[1]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	//generates a point to move to.
	int pos_ = cmp->makeMove(Board);
	Board->selected = 1;
	Board->moveSelectedToPos(pos_);
	//check if comp placed a piece on space 1;
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 9.2 Computer unsuccessfully chooses a piece to move
TEST(ComputerMovement, InvalidPieceChosen) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	Board->setBoardPieceP2(1);
	bool chk = Board->boardSpaces[2]->isPlayerTwo();
	ASSERT_NE(chk, true);
}

//AC 9.3 Computer unsuccessfully moves a piece to a location occupied by a player's piece
//Piece should not move from the original position and player's piece will not change
TEST(ComputerMovement, InvalidCompMovementOntoPlayer) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	//create board and place a piece for player
	Board->setBoard();
	Board->setBoardPiece(0);
	//computer generates a spot to place piece at
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	//check if the space is occupided by computer
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	//check if space 0 is occupied by player
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	//select computers piece to move
	Board->selected = pos_;
	if (Board->boardSpaces[0]->isEmpty()) {
		Board->moveSelectedToPos(0);
	}
	//will check if player's piece was removed
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	//will check if computers piece was moved
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 9.4 Computer unsuccessfully move a piece to an invalid location
//Test should cause an exception to be thrown since location to move to is out of range
TEST(ComputerMovement, InvalidMovement) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	Board->selected = pos_;
	EXPECT_ANY_THROW(Board->moveSelectedToPos(-1));
}

//AC 10.1 Fly Computers piece across board
TEST(ComputerFlying, ValidFly) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = pos_;
	Board->moveSelectedToPos(23);
	chk = Board->boardSpaces[23]->isPlayerTwo();
	ASSERT_EQ(chk, true);
}

//AC 10.2 Computer unsuccessfully chooses a piece to move
//Then no piece will move and the computer's turn will continue
TEST(ComputerFlying, InvalidChoice) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->turns++;
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	//invalid choice
	Board->selected = pos_+1;
	if (Board->boardSpaces[pos_ + 1]->isEmpty())
	{
		Board->moveSelectedToPos(1);
	}
	chk = Board->boardSpaces[pos_ + 1]->isEmpty();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 10.3 Computer unsuccessfully flies to an invalid place
TEST(ComputerFlying, InvalidFly) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->turns++;
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = pos_;
	ASSERT_ANY_THROW(Board->moveSelectedToPos(-1););
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	int playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 10.4 Computer unsuccessfully flies to a player occupied space
TEST(ComputerFlying, InvalidFlyOntoPlayer) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	Board->selected = pos_;
	if (Board->boardSpaces[0]->isEmpty()) 
	{
		Board->moveSelectedToPos(0);
	}
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 11.1 Computer successfully removes a player piece
TEST(ComputerRemoval, SuccessfulRemoval) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->removePiece(0);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_NE(chk, true);
	Board->turns++;
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 0);
}

//AC 11.2 Computer unsuccessfully chooses invalid player piece to remove
//Piece chosen will not be removed, and it will remain computers turn
TEST(ComputerRemoval, InvalidRemoval) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(0);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	bool chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	Board->removePiece(1);
	chk = Board->boardSpaces[0]->isPlayerOne();
	EXPECT_EQ(chk, true);
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC 11.3 Computer unsuccessfully chooses own piece to remove
//Piece chosen will not be removed, and it will remain computers turn
TEST(ComputerRemoval, InvalidRemovalOfOwn) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	if (!Board->boardSpaces[pos_]->isPlayerTwo())
	{
		Board->removePiece(pos_);
	}
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	playerNum = (Board->getTurn() % 2);
	ASSERT_EQ(playerNum, 1);
}

//AC Test computer placing a black piece after a valid Player move
//Will then be player's turn.
//Needs to be finished
TEST(ComputerMillPlacement, ValidMillPlacement) {
	morisGame* Board = new morisGame;
	Computer* cmp = new Computer();
	Board->setBoard();
	Board->setBoardPiece(1);
	Board->turns++;
	int playerNum = (Board->getTurn() % 2);
	EXPECT_EQ(playerNum, 1);
	int pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	bool chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	pos_ = cmp->makeMove(Board);
	Board->setBoardPieceP2(pos_);
	chk = Board->boardSpaces[pos_]->isPlayerTwo();
	EXPECT_EQ(chk, true);
	chk = Board->isNewMillMade(1);
	ASSERT_NE(chk, true);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
