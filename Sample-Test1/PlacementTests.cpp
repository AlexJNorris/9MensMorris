#include "pch.h"
#include "../9MensMorris/Board.h"


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

		//AC 2.1 Successfully create game and should be player 1's turn
		TEST(GameboardCreation, Successful) {
		morisGame* Board = new morisGame;
		Board->setBoard();
		int playerNum = (Board->getTurn() % 2);
		ASSERT_EQ(playerNum, 0);
	}

			//AC 2.2 Unsuccessfully create new game
			//Test should cause an exception to be thrown since the game board was unsuccessfully created.
			/*TEST(GameboardCreation, Unsuccessful) {
				morisGame* Board = new morisGame;
				Board->setBoardPiece(0);
				int playerNum = (Board->getTurn() % 2);
				ASSERT_NE(playerNum, 0);
			}*/

	//AC 3.1 Test placing a red piece at location 0
	//After succesful placement should be Player 2's turn
		TEST(TestPlacement, RedPlacement2) {
			morisGame* Board = new morisGame;
			Board->setBoard();
			Board->setBoardPiece(0);
			bool chk = Board->boardSpaces[0]->isPlayerOne();
			EXPECT_EQ(chk, true);
			Board->turns++;
			int playerNum = (Board->getTurn() % 2);
			ASSERT_EQ(playerNum, 1);
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
					//AC 3.3 Test placing a red piece on location out of range
					//Test should cause an exception to be thrown since placement is out of range
					/*TEST(TestPlacement, InvalidRedPlacement) {
						morisGame* Board = new morisGame;
						Board->setBoard();
						Board->setBoardPiece(-1);
						int playerNum = (Board->getTurn() % 2);
						ASSERT_EQ(playerNum, 0);
					}*/

					//AC 3.4 Test placing a red piece on a black piece
					//The placement should not be made, and will contunie being player 1's turn.
					TEST(TestPlacement, InvalidRedPlacementOnBlack2) {
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
				//Test should cause an exception to be thrown since placement is out of range
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
				TEST(TestPlacement, InvalidBlackPlacementOnRed2) {
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
				/*TEST(PieceMovement, InvalidRedMovement) {
					morisGame* Board = new morisGame;
					Board->setBoard();
					Board->setBoardPiece(0);
					bool chk = Board->boardSpaces[0]->isPlayerOne();
					EXPECT_EQ(chk, true);
					Board->selected = 0;
					Board->moveSelectedToPos(-1);
				}*/

				//AC 4.5 Unsuccessfully move a red piece to a location occupied by a black piece
				//Piece should not move from the original position and blacks piece will not change
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
					if (Board->boardSpaces[1]->isEmpty()) {
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
				/*TEST(PieceMovement, InvalidRedMovement) {
					morisGame* Board = new morisGame;
					Board->setBoard();
					Board->setBoardPieceP2(0);
					bool chk = Board->boardSpaces[0]->isPlayerTwo();
					EXPECT_EQ(chk, true);
					Board->selected = 0;
					Board->moveSelectedToPos(-1);
				}*/

				//AC 4.8 Unsuccessfully move a Black piece to a location occupied by a Red piece
				//Piece should not move from the original position and reds piece will not change
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
				/*TEST(Removal, InvalidBlackRemoval) {
					morisGame* Board = new morisGame;
					Board->setBoard();
					Board->setBoardPieceP2(0);
					bool chk = Board->boardSpaces[0]->isPlayerTwo();
					EXPECT_EQ(chk, true);
					Board->removePiece(1);
					chk = Board->boardSpaces[1]->isPlayerTwo();
					ASSERT_NE(chk, true);
				}*/

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
				/*TEST(Removal, InvalidRedRemoval) {
					morisGame* Board = new morisGame;
					Board->setBoard();
					Board->setBoardPiece(0);
					bool chk = Board->boardSpaces[0]->isPlayerOne();
					EXPECT_EQ(chk, true);
					Board->removePiece(1);
					chk = Board->boardSpaces[1]->isPlayerOne();
					ASSERT_NE(chk, true);
				}*/

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

			//Test new mill placement for player 1
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

			int main(int argc, char** argv)
			{
				::testing::InitGoogleTest(&argc, argv);
				return RUN_ALL_TESTS();
			}