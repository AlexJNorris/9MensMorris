
#include "Board.h"
//This is all preliminary. Feel free to add or remove variables and functions as needed.

using namespace std;

int removeDuplicates(vector<int> arr, int n)
{
	if (n == 0 || n == 1)
		return n;

	vector<int> temp;
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] != arr[i + 1])
			temp.push_back(arr[i]);
	}
	temp.push_back(arr[n - 1]);

	for (int i = 0; i < temp.size(); i++)
	{
		arr[i] = temp[i];
	}
	return arr.size();
}

	bool gameToken::isPlaced()
	{
		if (tokenLocation == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void gameToken::setName(int num)
	{
		tokenName = num;
	}
	void gameToken::setPlayer(bool player)
	{
		tokenPlayer = player;
	}
	void gameToken::setLocation(boardSpace* place)
	{
		tokenLocation = place;
	}
	int gameToken::getName()
	{
		return tokenName;
	}
	bool gameToken::getPlayer()
	{
		return tokenPlayer;
	}
	boardSpace* gameToken::getLocation()
	{
		return tokenLocation;
	}




	bool boardSpace::isEmpty()
	{
		if (placedToken == NULL) //tells if the board space has a token. 
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool boardSpace::isPlayerOne()
	{
		if (placedToken != NULL) {
			if (placedToken->getPlayer() == false) {
				return true;
			}
			return false;
		}
	}
	bool boardSpace::isPlayerTwo()
	{
		if (placedToken != NULL) {
			if (placedToken->getPlayer() == true) {
				return true;
			}
			return false;
		}
	}
	void boardSpace::setName(int num)
	{
		spaceName = num;
	};
	int boardSpace::getName()
	{
		return spaceName;
	};
	void boardSpace::placeToken(gameToken* piece)
	{
		placedToken = piece;
	}
	gameToken* boardSpace::getToken()
	{
		return placedToken; 
	}
	void boardSpace::addAdjacent(boardSpace* Space)
	{
		adjacentSpaces.push_back(Space);
	}
	void boardSpace::addVerticle(boardSpace* Space)
	{
		verticleMill.push_back(Space);
	}
	void boardSpace::addHorizontal(boardSpace* Space)
	{
		horizontalMill.push_back(Space);
	}
	boardSpace* boardSpace::getAdjacent(int i)
	{
		return adjacentSpaces[i];
	}
	boardSpace* boardSpace::getVerticle(int i)
	{
		return verticleMill[i];
	}
	boardSpace* boardSpace::getHorizontal(int i)
	{
		return horizontalMill[i];
	}
	void boardSpace::setY(int num)
	{
		yAxis = num;
	}
	void boardSpace::setX(int num)
	{
		xAxis = num;
	}
	int boardSpace::getX()
	{
		return xAxis;
	}
	int boardSpace::getY()
	{
		return yAxis;
	}

	

	morisGame::morisGame() {
		
	}

	//count pieces
	int morisGame::count(bool b)
	{
		if (b == false)
		{
			return (activePlayer1.size() + toBePlacedP1.size());
		}
		else
		{
			return (activePlayer2.size() + toBePlacedP2.size());
		}
	}

	int morisGame::getTurn()
	{
		return (turns % 2);
	}

	int morisGame::isMovingPhase()
	{
		return movingPhase;
	}

	void morisGame::setBoard()
	{
		gameMode = 0;
		turns = 0;
		movingPhase = 0;
		gameOver = false; //clears all the neccisary vectors and variables. 
		player1Mills = 0;
		player2Mills = 0;
		destroyMode = 0;
		selected = -1;

		validEnd = false;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				p1MillArr[i][j] = -1;
				p2MillArr[i][j] = -1;
			}
		}

		activePlayer1.clear();
		activePlayer2.clear();

		removedPlayer1.clear();
		removedPlayer2.clear();

		toBePlacedP1.clear();
		toBePlacedP2.clear();
		boardSpaces.clear();

		for (int i = 0; i < 9; i++) //generates tokens for player 1.
		{
			gameToken* token = new gameToken;
			token->setName(i);
			token->setLocation(NULL);
			token->setPlayer(false); //Player 1 = false
			toBePlacedP1.push_back(token);

		}

		for (int i = 0; i < 9; i++) //generates tokens for player 2.
		{
			gameToken* token = new gameToken;
			token->setName(i);
			token->setLocation(NULL);
			token->setPlayer(true); //Player 2 = true
			toBePlacedP2.push_back(token);

		}


		for (int i = 0; i < 24; i++) //generates all the board spaces. 
		{
			boardSpace* space = new boardSpace;
			space->setName(i);
			space->placeToken(NULL);
			space->setX(xAxis[i]);
			space->setY(yAxis[i]);
			boardSpaces.push_back(space);
		}

		/*starts creating board and conections. Its a bit long but I am not really sure how else to do this part.
		I'm also assuming that the board spaces are numbered from 0 to 23 going from bottom to top from left to right.
		the piece in the bottom left is 0 the top left is 21, bottom right is 2, and top right is 23 etc etc.
		*/
		//each index of these arrays represents the appropriate information about the targeted space. the targeted place is represented by the index where the data is stored.
		//for example all the data about space 0 is stored in index 0 of all of these arrays. 

		for (int i = 0; i < 24; i++) //adds the information to the space. 
		{
			boardSpace* space = boardSpaces[i];

			space->addVerticle(boardSpaces[verticle1[i]]);
			space->addVerticle(boardSpaces[verticle2[i]]);
			space->addVerticle(boardSpaces[verticle3[i]]);

			space->addHorizontal(boardSpaces[horz1[i]]);
			space->addHorizontal(boardSpaces[horz2[i]]);
			space->addHorizontal(boardSpaces[horz3[i]]);
		}

	}
	void morisGame::consoleOut()
	{
		int xCnt = 0; // count of placements passed on x axis
		int yCnt = 0; // count of placements passed on y axis
		int i = 0;
		boardSpace* space = boardSpaces[i];
		for (int y = 0; y < 13; y++)
		{
			for (int x = 0; x < 14; x++)
			{
				if(i < 24) {
					space = boardSpaces[i];
				}
				if (xAxis[i] == x/2 && yAxis[i] == y/2)
				{
					if (space->isEmpty())
					{
						// << 'X';
						xCnt++;
						i++;
					} 
					else
					{
						// << 'O';
						i++;
						xCnt++;
					}
				}
				else if ((x == 0 || x == 12) || (y % 2 == 1 && x == 6 && (y < 5 || y > 7)) || ((x == 2|| x == 10) && (y < 10 && y > 2)) || ((x == 4 || x == 8) && (y < 8 && y > 4)))
				{
					// << "|";
				}
				else if ( (xCnt>=1 && xCnt !=3 && xCnt<6))
				{
					// << "-";
				}
				else if (x == 13)
				{

					xCnt = 0;
					// << endl;
				}
				else
				{
					// << " ";
				}
			}
		}
	}
	void morisGame::setBoardPiece(int xy)
	{
		if (xy < 0 || boardSpaces.size() == 0)
			throw out_of_range("out of range");

		else
		{
			boardSpace* space = boardSpaces[xy];

			space->placedToken = toBePlacedP1.back();
			activePlayer1.push_back(space->placedToken);
			toBePlacedP1.pop_back();
		}
		
	}
	void morisGame::setBoardPieceP2(int xy)
	{
		if (xy < 0)
			throw out_of_range("out of range");
		else
		{
			boardSpace* space = boardSpaces[xy];
			space->placedToken = toBePlacedP2.back();
			activePlayer2.push_back(space->placedToken);
			toBePlacedP2.pop_back();
		}
	}
	bool morisGame::getGameOver()
	{
		return gameOver;
	}

	bool morisGame::isNewMillMade(int playerNum)
	{
		bool boolin = false;
		int vertChk;
		int horChk;
		int newMill[3] = { -1,-1,-1 };
		for (int i = 0; i < boardSpaces.size(); i++) {
			vertChk = 0;
			horChk = 0;

			if (playerNum == 0)
			{
				if (!boardSpaces[i]->isEmpty())
				{
					if (!boardSpaces[verticle1[i]]->isEmpty() && boardSpaces[verticle1[i]]->isPlayerOne()) { vertChk++; }
					if (!boardSpaces[verticle2[i]]->isEmpty() && boardSpaces[verticle2[i]]->isPlayerOne()) { vertChk++; }
					if (!boardSpaces[verticle3[i]]->isEmpty() && boardSpaces[verticle3[i]]->isPlayerOne()) { vertChk++; }
					if (!boardSpaces[horz1[i]]->isEmpty() && boardSpaces[horz1[i]]->isPlayerOne()) { horChk++; }
					if (!boardSpaces[horz2[i]]->isEmpty() && boardSpaces[horz2[i]]->isPlayerOne()) { horChk++; }
					if (!boardSpaces[horz3[i]]->isEmpty() && boardSpaces[horz3[i]]->isPlayerOne()) { horChk++; }
					if (vertChk == 3)
					{
						newMill[0] = verticle1[i];
						newMill[1] = verticle2[i];
						newMill[2] = verticle3[i];
						boolin = checkNewMill(newMill, playerNum);
						if (boolin)
						{
							break;
						}
					}
					else if (horChk == 3)
					{
						newMill[0] = horz1[i];
						newMill[1] = horz2[i];
						newMill[2] = horz3[i];
						boolin = checkNewMill(newMill, playerNum);
						if (boolin)
						{
							break;
						}
					}
				}
			}
			else
			{
				if (!boardSpaces[i]->isEmpty())
				{
					if (!boardSpaces[verticle1[i]]->isEmpty() && boardSpaces[verticle1[i]]->isPlayerTwo()) { vertChk++; }
					if (!boardSpaces[verticle2[i]]->isEmpty() && boardSpaces[verticle2[i]]->isPlayerTwo()) { vertChk++; }
					if (!boardSpaces[verticle3[i]]->isEmpty() && boardSpaces[verticle3[i]]->isPlayerTwo()) { vertChk++; }
					if (!boardSpaces[horz1[i]]->isEmpty() && boardSpaces[horz1[i]]->isPlayerTwo()) { horChk++; }
					if (!boardSpaces[horz2[i]]->isEmpty() && boardSpaces[horz2[i]]->isPlayerTwo()) { horChk++; }
					if (!boardSpaces[horz3[i]]->isEmpty() && boardSpaces[horz3[i]]->isPlayerTwo()) { horChk++; }
					if (vertChk == 3)
					{
						newMill[0] = verticle1[i];
						newMill[1] = verticle2[i];
						newMill[2] = verticle3[i];
						boolin = checkNewMill(newMill, playerNum);
						if (boolin)
						{
							break;
						}
					}
					else if (horChk == 3)
					{
						newMill[0] = horz1[i];
						newMill[1] = horz2[i];
						newMill[2] = horz3[i];
						boolin = checkNewMill(newMill, playerNum);
						if (boolin)
						{
							break;
						}
					}
				}
			}
		}
		return boolin;
	}
	bool morisGame::checkNewMill(int Arr[3], int player)
	{
		int millChk;
		int emptyChk;
		
		if (player == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				millChk = 0;
				emptyChk = 0;
				for (int j = 0; j < 3; j++)
				{
					if (Arr[j] == p1MillArr[i][j]) { millChk++; }
					else if (p1MillArr[i][j] == -1) { emptyChk++; }
				}
				if (millChk == 3) { return false; }
				else if (emptyChk == 3)
				{
					for (int j = 0; j < 3; j++)
					{
						p1MillArr[i][j] = Arr[j];
					}

					return true;
				}
			}
			return false;
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				millChk = 0;
				emptyChk = 0;
				for (int j = 0; j < 3; j++)
				{
					if (Arr[j] == p2MillArr[i][j]) { millChk++; }
					else if (p2MillArr[i][j] == -1) { emptyChk++; }
				}
				if (millChk == 3) { return false; }
				else if (emptyChk == 3)
				{
					for (int j = 0; j < 3; j++)
					{
						p2MillArr[i][j] = Arr[j];
					}

					return true;
				}
			}

			return false;
		}
	}
			
	bool morisGame::isInP1MillArr(int num) {
	
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (num == p1MillArr[i][j]) { return true; }
				else if (p1MillArr[i][j] == -1) { return false; }
			}
		}
		return false;
	}
	bool morisGame::isInP2MillArr(int num) {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (num == p2MillArr[i][j]) { return true; }
				else if (p2MillArr[i][j] == -1) { return false; }
			}
		}
		return false;
	}
	bool morisGame::isAdjacentToSelected(int pos) {
		if (pos == adj1[selected] || pos == adj2[selected] || pos == adj3[selected] || pos == adj4[selected])
		{
			return true;
		}
		return false;
	}
	void morisGame::removePiece(int num) {
		boardSpace* space = boardSpaces[num];
		if (space->placedToken == NULL)
		{
			space->placedToken = NULL;
		}
		else
		{
			if (space->isPlayerOne())
			{
				if (activePlayer1.size() == 0)
					throw out_of_range("out of range");
				else
				{
					removedPlayer1.push_back(new gameToken());
					activePlayer1.pop_back();
					space->placedToken = NULL;
				}

			}
			else
			{
				if (activePlayer2.size() == 0)
					throw out_of_range("out of range");
				else
				{
					removedPlayer2.push_back(new gameToken());
					activePlayer2.pop_back();
					space->placedToken = NULL;
				}

			}
		}
	}
	void morisGame::moveSelectedToPos(int pos) {
		if (pos == -1)
			throw out_of_range("out of range");
		else
		{
			boardSpaces[pos]->placedToken = boardSpaces[selected]->getToken();

			boardSpaces[selected]->placedToken = NULL;
			selected = -1;
		}
	}
	bool morisGame::isMillBroken(int playerNum) {
		int millCnt = 0;
		int removedMill = -1;
		bool cornBoolio = false;

		if (playerNum == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (p1MillArr[i][0] != -1) { millCnt++; }
				else { break; }
				for (int j = 0; j < 3; j++)
				{
					// << boardSpaces[p1MillArr[i][j]]->isEmpty();
					if (boardSpaces[p1MillArr[i][j]]->isEmpty())
					{
						cornBoolio = true;
						removedMill = millCnt;
						p1MillArr[i][0] = -1;
						p1MillArr[i][1] = -1;
						p1MillArr[i][2] = -1;
						break;
					}
				}
			}
		}

		else if (playerNum == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				if (p2MillArr[i][0] != -1) { millCnt++; }
				else { break; }
				for (int j = 0; j < 3; j++)
				{
					if (boardSpaces[p2MillArr[i][j]]->isEmpty())
					{
						cornBoolio = true;
						removedMill = millCnt;
						p2MillArr[i][0] = -1;
						p2MillArr[i][1] = -1;
						p2MillArr[i][2] = -1;
						break;
					}
				}
			}
		}

		if (cornBoolio == true) {
			if (playerNum == 0)
			{
				if (!(millCnt == removedMill))
				{
					for (int i = removedMill - 1; i < millCnt - 1; i++)
					{
							p1MillArr[i][0] = p1MillArr[i + 1][0];
							p1MillArr[i][1] = p1MillArr[i + 1][1];
							p1MillArr[i][2] = p1MillArr[i + 1][2];
					}

						p1MillArr[millCnt-1][0] = -1;
						p1MillArr[millCnt-1][1] = -1;
						p1MillArr[millCnt-1][2] = -1;
				}
			}

			else if (playerNum == 1)
			{
				if (!(millCnt == removedMill))
				{
					for (int i = removedMill - 1; i < millCnt - 1; i++)
					{
						
						p2MillArr[i][0] = p2MillArr[i + 1][0];
						p2MillArr[i][1] = p2MillArr[i + 1][1];
						p2MillArr[i][2] = p2MillArr[i + 1][2];
					
					}

					p2MillArr[millCnt-1][0] = -1;
					p2MillArr[millCnt-1][1] = -1;
					p2MillArr[millCnt-1][2] = -1;
					
				}
			}
		}

		return cornBoolio;
		
	}
	bool morisGame::allActiveP1InMill() {
		int n = 0;
		bool oneMatch;
		for (int k = 0; k < 24; k++)
		{
			oneMatch = false;
			for (int i = 0; i < 3; i++)
			{
				if (oneMatch == true) { break; }
				if (p1MillArr[i][0] != -1)
				{
					for (int j = 0; j < 3; j++)
					{

						if (p1MillArr[i][j] == k)
						{
							n++;
							oneMatch = true;
							break;
						}
					}
				}
			}
		}

		//// << n << endl;
		//// << activePlayer1.size() << endl;
		if (n == activePlayer1.size())
		{
			return true;
		}
		return false;
	}
	bool morisGame::allActiveP2InMill() {
		int n = 0;
		bool oneMatch;
		for (int k = 0; k < 24; k++)
		{
			oneMatch = false;
			for (int i = 0; i < 3; i++)
			{
				if (oneMatch == true) { break; }
				if (p2MillArr[i][0] != -1)
				{
					for (int j = 0; j < 3; j++)
					{

						if (p2MillArr[i][j] == k)
						{
							n++;
							oneMatch = true;
							break;
						}
					}
				}
			}
		}

		//// << n << endl;
		//// << activePlayer2.size() << endl;
		if (n == activePlayer2.size())
		{
			return true;
		}
		return false;
	}

	void morisGame::manageGame(int pos_) {
		int playerNum = (getTurn() % 2);
		//  // << "  " << pos_ << endl;
		if (gameMode == 0)
		{
			gameMode = pos_;
		}
		else if (gameMode == 1)
		{
			if (pos_ < 24 && pos_ >= 0 && gameOver == false)
			{
				if (destroyMode == 0)
				{
					if (movingPhase == 0)
					{
						if (toBePlacedP2.size() != 0)
						{
							if (boardSpaces[pos_]->isEmpty())
							{
								if (playerNum == 0)
								{
									setBoardPiece(pos_);
									if (isNewMillMade(playerNum))
									{
										destroyMode = 1;
									}
									else
									{
										turns++;
									}
								}
								else
								{
									setBoardPieceP2(pos_);
									if (isNewMillMade(playerNum))
									{
										destroyMode = 2;
									}
									else
									{
										if (toBePlacedP2.size() == 0)
										{
											noValidMoves();
										}
										turns++;
									}
									if (toBePlacedP2.size() == 0)
									{
										movingPhase = 1;
										// << movingPhase;
									}
								}
							}
						}
					}
					else
					{
						if (!isAdjacentToSelected(pos_) || pos_ == selected || !boardSpaces[pos_]->isEmpty())
						{
							if (playerNum == 0)
							{
								if (activePlayer1.size() < 4 && (selected > -1 && selected < 24))
								{
									if (boardSpaces[pos_]->isEmpty())
									{
										moveSelectedToPos(pos_);
										if (isNewMillMade(playerNum))
										{
											destroyMode = 1;
										}
										else
										{
											turns++;
										}
										isMillBroken(playerNum);
									}
								}
								else if (boardSpaces[pos_]->isPlayerOne() && !boardSpaces[pos_]->isEmpty())
								{
									selected = pos_;
								}
							}
							else if (playerNum == 1)
							{
								if (activePlayer2.size() < 4 && (selected > -1 && selected < 24))
								{
									if (boardSpaces[pos_]->isEmpty())
									{
										moveSelectedToPos(pos_);
										if (isNewMillMade(playerNum))
										{
											destroyMode = 2;
										}
										else
										{
											turns++;
										}
										isMillBroken(playerNum);

									}
								}
								else if (boardSpaces[pos_]->isPlayerTwo() && !boardSpaces[pos_]->isEmpty())
								{
									selected = pos_;
								}
							}
						}
						else
						{
							if (playerNum == 0)
							{
								if (boardSpaces[pos_]->isEmpty() && (selected > -1 && selected < 24))
								{
									moveSelectedToPos(pos_);

									if (isNewMillMade(playerNum))
									{
										destroyMode = 1;
									}
									else
									{
										turns++;
									}

									isMillBroken(playerNum);
								}
							}
							else if (playerNum == 1)
							{
								if (boardSpaces[pos_]->isEmpty() && (selected > -1 && selected < 24))
								{
									moveSelectedToPos(pos_);

									if (isNewMillMade(playerNum))
									{
										destroyMode = 2;
									}
									else
									{
										turns++;
									}

									isMillBroken(playerNum);
								}
							}
						}

					}
				}
				else if ((pos_ < 24 && pos > -1)&&((!boardSpaces[pos_]->isEmpty() && destroyMode == 1 && boardSpaces[pos_]->isPlayerTwo() && !isInP2MillArr(pos_)) || (!boardSpaces[pos_]->isEmpty() && destroyMode == 2 && boardSpaces[pos_]->isPlayerOne() && !isInP1MillArr(pos_))))
				{
					removePiece(pos_);
					destroyMode = 0;
					if ((activePlayer1.size() < 3 && toBePlacedP1.size() == 0) || (activePlayer2.size() < 3 && toBePlacedP2.size() == 0))
					{
						gameOver = true;
					}
					else
					{
						turns++;
					}

				}
				else if ((pos_ < 24 && pos > -1) && ((!boardSpaces[pos_]->isEmpty() && destroyMode == 1 && boardSpaces[pos_]->isPlayerTwo() && allActiveP2InMill()) || (!boardSpaces[pos_]->isEmpty() && destroyMode == 2 && boardSpaces[pos_]->isPlayerOne() && allActiveP1InMill())))
				{
					removePiece(pos_);
					isMillBroken((turns % 2));
					destroyMode = 0;
					if ((activePlayer1.size() < 3 && toBePlacedP1.size() == 0) || (activePlayer2.size() < 3 && toBePlacedP2.size() == 0))
					{
						gameOver = true;
					}
					else
					{
						turns++;
						isMillBroken((turns % 2));
					}

				}
			}
			else if (pos_ == 25)
			{
				setBoard();
			}
		}
		else if (gameMode == 2)
		{
		if (pos_ < 24 && pos_ >= 0 && gameOver == false)
		{
			if (destroyMode == 0)
			{
				if (movingPhase == 0)
				{
					if (toBePlacedP2.size() != 0)
					{
						if (boardSpaces[pos_]->isEmpty())
						{
							if (playerNum == 0)
							{
								setBoardPiece(pos_);
								if (isNewMillMade(playerNum))
								{
									destroyMode = 1;
								}
								else
								{
									turns++;
								}
							}
							else
							{
								setBoardPieceP2(pos_);
								if (isNewMillMade(playerNum))
								{
									destroyMode = 2;
								}
								else
								{
									if (toBePlacedP2.size() == 0)
									{
										noValidMoves();
									}
									turns++;
								}
								if (toBePlacedP2.size() == 0)
								{
									movingPhase = 1;
									//// << movingPhase;
								}
							}
						}
					}
				}
				else
				{
					if (!isAdjacentToSelected(pos_) || pos_ == selected || !boardSpaces[pos_]->isEmpty())
					{
						if (playerNum == 0)
						{
							if (activePlayer1.size() < 4 && (selected > -1 && selected < 24))
							{
								if (boardSpaces[pos_]->isEmpty() && (selected > -1 && selected < 24))
								{
									moveSelectedToPos(pos_);
									if (isNewMillMade(playerNum))
									{
										destroyMode = 1;
									}
									else
									{
										turns++;
									}
									isMillBroken(playerNum);
								}
							}
							else if (boardSpaces[pos_]->isPlayerOne() && !boardSpaces[pos_]->isEmpty())
							{
								selected = pos_;
							}
						}
						else if (playerNum == 1)
						{
							if (activePlayer2.size() < 4 && (selected > -1 && selected < 24))
							{
								if (boardSpaces[pos_]->isEmpty())
								{
									moveSelectedToPos(pos_);
									if (isNewMillMade(playerNum))
									{
										destroyMode = 2;
									}
									else
									{
										turns++;
									}
									isMillBroken(playerNum);

								}
							}
							else if (boardSpaces[pos_]->isPlayerTwo() && !boardSpaces[pos_]->isEmpty())
							{
								selected = pos_;
							}
						}
					}
					else
					{
						if (playerNum == 0)
						{
							if (boardSpaces[pos_]->isEmpty() && (selected > -1 && selected < 24))
							{
								moveSelectedToPos(pos_);

								if (isNewMillMade(playerNum))
								{
									destroyMode = 1;
								}
								else
								{
									turns++;
								}

								isMillBroken(playerNum);
							}
						}
						else if (playerNum == 1 && (selected > -1 && selected < 24))
						{
							if (boardSpaces[pos_]->isEmpty())
							{
								moveSelectedToPos(pos_);

								if (isNewMillMade(playerNum))
								{
									destroyMode = 2;
								}
								else
								{
									turns++;
								}

								isMillBroken(playerNum);
							}
						}
					}

				}
			}
			else if ((pos_ < 24 && pos > -1) && (((!boardSpaces[pos_]->isEmpty() && destroyMode == 1 && boardSpaces[pos_]->isPlayerTwo() && !isInP2MillArr(pos_)) || (!boardSpaces[pos_]->isEmpty() && destroyMode == 2 && boardSpaces[pos_]->isPlayerOne() && !isInP1MillArr(pos_)))))
			{
				removePiece(pos_);
				destroyMode = 0;
				if ((activePlayer1.size() < 3 && toBePlacedP1.size() == 0) || (activePlayer2.size() < 3 && toBePlacedP2.size() == 0))
				{
					gameOver = true;
				}
				else
				{
					turns++;
				}

			}
			else if ((pos_ < 24 && pos > -1) && (((!boardSpaces[pos_]->isEmpty() && destroyMode == 1 && boardSpaces[pos_]->isPlayerTwo() && allActiveP2InMill()) || (!boardSpaces[pos_]->isEmpty() && destroyMode == 2 && boardSpaces[pos_]->isPlayerOne() && allActiveP1InMill()))))
			{
				removePiece(pos_);
				isMillBroken((turns % 2));
				destroyMode = 0;
				if ((activePlayer1.size() < 3 && toBePlacedP1.size() == 0) || (activePlayer2.size() < 3 && toBePlacedP2.size() == 0))
				{
					gameOver = true;
				}
				else
				{
					turns++;
					isMillBroken((turns % 2));
				}

			}
		}
		else if (pos_ == 25)
		{
			setBoard();
		}
		}
	}
	void morisGame::noValidMoves() {
		int playerNum = turns % 2;
		int validMove = 0;
		if (playerNum == 0)
		{
			for (int i = 0; i < 24; i++)
			{
				if (boardSpaces[i]->isPlayerOne() && !boardSpaces[i]->isEmpty())
				{
					if (adj1[i] != -1)
					{
						if (boardSpaces[adj1[i]]->isEmpty()) { validMove++; }
					}
					if (adj2[i] != -1)
					{
						if (boardSpaces[adj2[i]]->isEmpty()) { validMove++; }
					}
					if (adj3[i] != -1)
					{
						if (boardSpaces[adj3[i]]->isEmpty()) { validMove++; }
					}
					if (adj4[i] != -1)
					{
						if (boardSpaces[adj4[i]]->isEmpty()) { validMove++; }
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 24; i++)
			{
				if (boardSpaces[i]->isPlayerTwo() && !boardSpaces[i]->isEmpty())
				{
					if (adj1[i] != -1)
					{
						if (boardSpaces[adj1[i]]->isEmpty()) { validMove++; }
					}
					if (adj2[i] != -1)
					{
						if (boardSpaces[adj2[i]]->isEmpty()) { validMove++; }
					}
					if (adj3[i] != -1)
					{
						if (boardSpaces[adj3[i]]->isEmpty()) { validMove++; }
					}
					if (adj4[i] != -1)
					{
						if (boardSpaces[adj4[i]]->isEmpty()) { validMove++; }
					}
				}
			}
		}
		if (validMove == 0)
		{
			turns++;
			validEnd = true;
			gameOver = true;
		}
	}
	void morisGame::copyBoard(morisGame* Temp)
	{
		temp->turns = turns;
		temp->movingPhase = movingPhase;
		temp->destroyMode = destroyMode;
		temp->selected = selected;
		gameToken* token;
		for (int i = 0; i < activePlayer1.size(); i++)
		{
			token = new gameToken();
			token->setPlayer(false);
			temp->activePlayer1.push_back(token);
		}

		for (int i = 0; i < activePlayer2.size(); i++)
		{

			token = new gameToken();
			token->setPlayer(true);
			temp->activePlayer2.push_back(token);
		}

		for (int i = 0; i < toBePlacedP1.size(); i++)
		{
			token = new gameToken();
			token->setPlayer(false);
			temp->toBePlacedP1.push_back(token);
		}

		for (int i = 0; i < toBePlacedP2.size(); i++)
		{
			token = new gameToken();
			token->setPlayer(true);
			temp->toBePlacedP2.push_back(token);
		}

		for (int i = 0; i < 24; i++)
		{
			temp->boardSpaces[i]->placedToken = boardSpaces[i]->getToken();
		}


		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp->p1MillArr[i][j] = p1MillArr[i][j];
				temp->p2MillArr[i][j] = p2MillArr[i][j];
			}
		}
	}
	