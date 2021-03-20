
#include "Board.h"
//This is all preliminary. Feel free to add or remove variables and functions as needed.

using namespace std;


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
		turns = 0;
		movingPhase = 0;
		gameOver = false; //clears all the neccisary vectors and variables. 
		player1Mills = 0;
		player2Mills = 0;

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
			space->addAdjacent(boardSpaces[adj1[i]]);
			space->addAdjacent(boardSpaces[adj2[i]]);
			if (adj3[i] >= 0)//checks to make sure that space actually has a 3rd or 4th adjacency instead of just 2. 
				space->addAdjacent(boardSpaces[adj3[i]]);
			if (adj4[i] >= 0)
				space->addAdjacent(boardSpaces[adj4[i]]);

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
						cout << 'X';
						xCnt++;
						i++;
					} 
					else
					{
						cout << 'O';
						i++;
						xCnt++;
					}
				}
				else if ((x == 0 || x == 12) || (y % 2 == 1 && x == 6 && (y < 5 || y > 7)) || ((x == 2|| x == 10) && (y < 10 && y > 2)) || ((x == 4 || x == 8) && (y < 8 && y > 4)))
				{
					cout << "|";
				}
				else if ( (xCnt>=1 && xCnt !=3 && xCnt<6))
				{
					cout << "-";
				}
				else if (x == 13)
				{

					xCnt = 0;
					cout << endl;
				}
				else
				{
					cout << " ";
				}
			}
		}
	}
	void morisGame::setBoardPiece(int xy)
	{
		boardSpace* space = boardSpaces[xy];

		space->placedToken = toBePlacedP1.back();
		activePlayer1.push_back(space->placedToken);
		toBePlacedP1.pop_back();
	}
	void morisGame::setBoardPieceP2(int xy)
	{
		boardSpace* space = boardSpaces[xy];

		space->placedToken = toBePlacedP2.back();
		activePlayer2.push_back(space->placedToken);
		toBePlacedP2.pop_back();
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
			if (!boardSpaces[i]->isEmpty()) {
				if (!boardSpaces[verticle1[i]]->isEmpty()) { vertChk++; }
				if (!boardSpaces[verticle2[i]]->isEmpty()) { vertChk++; }
				if (!boardSpaces[verticle3[i]]->isEmpty()) { vertChk++; }
				if (!boardSpaces[horz1[i]]->isEmpty()) { horChk++; }
				if (!boardSpaces[horz2[i]]->isEmpty()) { horChk++; }
				if (!boardSpaces[horz3[i]]->isEmpty()) { horChk++; }
				if (vertChk == 3)
				{
					newMill[0] = verticle1[i];
					newMill[1] = verticle2[i];
					newMill[2] = verticle3[i];
					boolin = checkNewMill(newMill, playerNum);
					break;
				} 
				else if (horChk == 3)
				{
					newMill[0] = horz1[i];
					newMill[1] = horz2[i];
					newMill[2] = horz3[i];
					boolin = checkNewMill(newMill, playerNum);
					break;
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
			

