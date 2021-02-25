#include<iostream>
#include<vector>

using namespace std;

//This is all preliminary. Feel free to add or remove variables and functions as needed.

class gameToken;
class boardSpace;
class morisGame;

class boardSpace
{
public: 
	bool isEmpty()
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
	void setName(int num)
	{
		spaceName = num;
	};
	int getName()
	{
		return spaceName;
	};
	void placeToken(gameToken* piece)
	{
		placedToken = piece;
	}
	gameToken* getToken()
	{
		return placedToken; 
	}
	void addAdjacent(boardSpace* Space)
	{
		adjacentSpaces.push_back(Space);
	}
	void addVerticle(boardSpace* Space)
	{
		verticleMill.push_back(Space);
	}
	void addHorizontal(boardSpace* Space)
	{
		horizontalMill.push_back(Space);
	}
	boardSpace* getAdjacent(int i)
	{
		return adjacentSpaces[i];
	}
	boardSpace* getVerticle(int i)
	{
		return verticleMill[i];
	}
	boardSpace* getHorizontal(int i)
	{
		return horizontalMill[i];
	}
	void setY(int num)
	{
		yAxis = num;
	}
	void setX(int num)
	{
		xAxis = num;
	}
	int getX()
	{
		return xAxis;
	}
	int getY()
	{
		return yAxis;
	}

private:

	int spaceName;
	int xAxis;
	int yAxis;
	gameToken* placedToken;
	vector<boardSpace*> adjacentSpaces; //holds spaces physicly adjacent to this one.
	vector<boardSpace*> verticleMill; //holds spaces needed for a verticle mill with this one. 
	vector<boardSpace*> horizontalMill; // holds spcaes needed for a horizontal mill with this one. 

};

class gameToken
{
public:
	bool isPlaced()
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
	void setName(int num)
	{
		tokenName = num;
	}
	void setPlayer(bool player)
	{
		tokenPlayer = player;
	}
	void setLocation(boardSpace* place)
	{
		tokenLocation = place; 
	}
	int getName()
	{
		return tokenName;
	}
	bool getPlayer()
	{
		return tokenPlayer;
	}
	boardSpace* getLocation()
	{
		return tokenLocation;
	};

private:
	int tokenName;
	bool tokenPlayer;
	boardSpace* tokenLocation;
};

class morisGame
{
public:
	void setBoard()
	{
		gameOver = false; //clears all the neccisary vectors and variables. 
		player1Mills = 0;
		player2Mills = 0;

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
			token->setPlayer = false; //Player 1 = false
			toBePlacedP1.push_back(token);

		}

		for (int i = 0; i < 9; i++) //generates tokens for player 2.
		{
			gameToken* token = new gameToken;
			token->setName(i);
			token->setLocation(NULL);
			token->setPlayer = true; //Player 2 = true
			toBePlacedP2.push_back(token);

		}

		int xAxis[24] = { 0,3,6,1,3,5,2,3,4,0,1,2,4,5,6,2,3,4,1,3,5,0,3,6 }; //loads coordinates for X and Y axis
		int yAxis[24] = { 0,0,0,1,1,1,2,2,2,3,3,3,3,3,3,4,4,4,5,5,5,6,6,6 };//assuming bottom to top, left to right. 

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
		int adj1[24] = {9,4,4,10,7,13,11,8,12,21,18,15,17,20,23,16,19,12,19,22,13,22,23,14}; //Holds the number for the nodes adjacent to the targeted space going in a clockwise direction 
		int adj2[24] = {1,2,1,4,5,4,7,4,7,0,11,6,13,14,2,11,17,16,10,20,19,9,19,22}; //that starts with the node verticle to the target node if applicable. 
		int adj3[24] = {-1,0,-1,-1,1,-1,-1,6,-1,-1,4,10,8,5,13,-1,15,-1,-1,16,-1,-1,21,-1}; //-1 means not applicable.
		int adj4[24] = {-1,-1,-1,-1,3,-1,-1,-1,-1,-1,9,-1,-1,12,0,-1,-1,-1,-1,18,-1,-1,-1,-1};
		int verticle1[24] = {21,7,23,18,7,20,15,7,17,21,18,15,17,20,23,15,22,17,18,22,20,21,22,23}; //holds the top most space needed to make a mill with the target space
		int verticle2[24] = {9,4,14,10,4,13,11,4,12,9,10,11,12,13,14,11,19,12,10,19,13,9,19,14}; //holds the  middle most space needed to form a verticle mill with the target space
		int verticle3[24] = {0,1,2,3,1,5,6,1,8,0,3,6,8,5,2,6,16,8,3,16,5,0,16,2};  //holds the bottom most space needed to form a mill with the target space. 
		int horz1[24] = {0,0,0,3,3,3,6,6,6,9,9,9,12,12,12,15,15,15,18,18,18,21,21,21}; //holds leftmost space needed to make a mill with the target node
		int horz2[24] = {1,1,1,4,4,4,7,7,7,10,10,10,13,13,13,16,16,16,19,19,19,22,22,22}; // holds the middle space needed to make a horizontal mill with the target
		int horz3[24] = {2,2,2,5,5,5,8,8,8,11,11,11,14,14,14,17,17,17,20,20,20,23,23,23};//holds the right most space needed to make a mill with the target. 

		for (int i = 0; i < 24; i++) //adds the information to the space. 
		{
			boardSpace* space = boardspaces[i];
			space->addAdjacent(boardspaces[adj1[i]]);
			space->addAdjacent(boardspaces[adj2[i]]);
			if (adj3[i] >= 0)//checks to make sure that space actually has a 3rd or 4th adjacency instead of just 2. 
				space->addAdjacent(boardspaces[adj3[i]]);
			if (adj4[i] >= 0)
				space->addAdjacent(boardspaces[adj4[i]]);

			space->addVerticle(boardspaces[verticle1[i]]);
			space->addVerticle(boardspaces[verticle2[i]]);
			space->addVerticle(boardspaces[verticle3[i]]);

			space->addHorizontal(boardspaces[horz1[i]]);
			space->addHorizontal(boardspaces[horz2[i]]);
			space->addHorizontal(boardspaces[horz3[i]]);
		}

	};

private:

	bool gameOver; 

	vector<gameToken*> activePlayer1; //Vectors for the active tokens.
	vector<gameToken*> activePlayer2; 
	vector<gameToken*> removedPlayer1; //Vectors for the removed tokens.
	vector<gameToken*> removedPlayer2;
	vector<gameToken*> toBePlacedP1; //Vectors for tokens that still need to be placed.
	vector<gameToken*> toBePlacedP2;

	vector<boardSpace*> boardSpaces; //holds all the placeable board spaces. 

	int player1Mills;
	int player2Mills;

};
