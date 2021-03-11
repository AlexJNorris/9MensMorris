#ifndef BOARD_CPP
#define BOARD_CPP


#include<Windows.h>    
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder   
#include<iostream>
#include<vector>
#include <thread>
#include <mutex>
#include "TextRenderer.cpp"

using namespace std;

//This is all preliminary. Feel free to add or remove variables and functions as needed.

class gameToken;
class boardSpace;
class morisGame;

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
	}

private:
	int tokenName;
	bool tokenPlayer;
	boardSpace* tokenLocation;
};


class boardSpace {

public: 

	gameToken* placedToken;

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
	bool isPlayerOne()
	{
		if (placedToken != NULL) {
			if (placedToken->getPlayer() == false) {
				return true;
			}
			return false;
		}
	}
	bool isPlayerTwo()
	{
		if (placedToken != NULL) {
			if (placedToken->getPlayer() == true) {
				return true;
			}
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
	vector<boardSpace*> adjacentSpaces; //holds spaces physicly adjacent to this one.
	vector<boardSpace*> verticleMill; //holds spaces needed for a verticle mill with this one. 
	vector<boardSpace*> horizontalMill; // holds spcaes needed for a horizontal mill with this one. 

};


class morisGame
{
public:
	vector<boardSpace*> boardSpaces; //holds all the placeable board spaces. 

	vector<gameToken*> activePlayer1; //Vectors for the active tokens.
	vector<gameToken*> activePlayer2;
	vector<gameToken*> removedPlayer1; //Vectors for the removed tokens.
	vector<gameToken*> removedPlayer2;
	vector<gameToken*> toBePlacedP1; //Vectors for tokens that still need to be placed.
	vector<gameToken*> toBePlacedP2;
	int turns;
	int movingPhase;

	TextRenderer tr;

	int pos;
	bool updateScene = true;
	bool playing = true;

	int selected;
	int previousSelected;
	int deleted;
	int whitePlayer;
	int blackPlayer;
	int winner = EMPTY;

	

	morisGame(){
		this->setBoard();
	}
	//count pieces
	int count(bool b)
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

	int getTurn() 
	{
		return (turns % 2);
	}

	int isMovingPhase()
	{
		return movingPhase;
	}

	void setBoard()
	{
		turns = 0;
		movingPhase = 0;
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

	};
	void consoleOut() 
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
	void setBoardPiece(int xy)
	{
		boardSpace* space = boardSpaces[xy];

		space->placedToken = toBePlacedP1.back();
		toBePlacedP1.pop_back();
	}
	void setBoardPieceP2(int xy)
	{
		boardSpace* space = boardSpaces[xy];

		space->placedToken = toBePlacedP2.back();
		toBePlacedP2.pop_back();
	}
	bool getGameOver()
	{
		return gameOver;
	}

	void display() {
		if (!updateScene) {
			return;
		}
		updateScene = false;
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glScalef(SCREEN_SHRINK_RATIO / SCREEN_WIDTH,
			-SCREEN_SHRINK_RATIO / SCREEN_HEIGHT,
			1);

		glTranslatef(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0);

		// Compute the extra colors needed to draw the board
		// 1 -> selected
		// 2 -> previously selected
		// 3 -> deleted
		array<int, 24> extraColors;
		extraColors.fill(0);
		if (selected >= 0) {
			extraColors[selected] = 1;
		}
		if (previousSelected >= 0) {
			extraColors[previousSelected] = 2;
		}
		if (deleted >= 0) {
			extraColors[deleted] = 3;
		}
		//this->draw(gameState_, extraColors);

		// glutSwapBuffers();
		if (winner != EMPTY) {
			glColor4f(1, 1, 1, 0.3);
			glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(BOARD_WIDTH, 0);
			glVertex2f(BOARD_WIDTH, BOARD_HEIGHT);
			glVertex2f(0, BOARD_HEIGHT);
			glEnd();

			string winnerText = "";
			if (winner == WHITE) {
				winnerText = "White";
			}
			else {
				winnerText = "Black";
			}
			winnerText += " Won!";

			tr.printCenter(BOARD_WIDTH / 2, 250, winnerText, 3);
		}

		glFlush();
	}

			
private:

	bool gameOver; 

	int player1Mills;
	int player2Mills;

	int adj1[24] = { 9,4,4,10,7,13,11,8,12,21,18,15,17,20,23,16,19,12,19,22,13,22,23,14 }; //Holds the number for the nodes adjacent to the targeted space going in a clockwise direction 
	int adj2[24] = { 1,2,1,4,5,4,7,4,7,0,11,6,13,14,2,11,17,16,10,20,19,9,19,22 }; //that starts with the node verticle to the target node if applicable. 
	int adj3[24] = { -1,0,-1,-1,1,-1,-1,6,-1,-1,4,10,8,5,13,-1,15,-1,-1,16,-1,-1,21,-1 }; //-1 means not applicable.
	int adj4[24] = { -1,-1,-1,-1,3,-1,-1,-1,-1,-1,9,-1,-1,12,0,-1,-1,-1,-1,18,-1,-1,-1,-1 };
	int verticle1[24] = { 21,7,23,18,7,20,15,7,17,21,18,15,17,20,23,15,22,17,18,22,20,21,22,23 }; //holds the top most space needed to make a mill with the target space
	int verticle2[24] = { 9,4,14,10,4,13,11,4,12,9,10,11,12,13,14,11,19,12,10,19,13,9,19,14 }; //holds the  middle most space needed to form a verticle mill with the target space
	int verticle3[24] = { 0,1,2,3,1,5,6,1,8,0,3,6,8,5,2,6,16,8,3,16,5,0,16,2 };  //holds the bottom most space needed to form a mill with the target space. 
	int horz1[24] = { 0,0,0,3,3,3,6,6,6,9,9,9,12,12,12,15,15,15,18,18,18,21,21,21 }; //holds leftmost space needed to make a mill with the target node
	int horz2[24] = { 1,1,1,4,4,4,7,7,7,10,10,10,13,13,13,16,16,16,19,19,19,22,22,22 }; // holds the middle space needed to make a horizontal mill with the target
	int horz3[24] = { 2,2,2,5,5,5,8,8,8,11,11,11,14,14,14,17,17,17,20,20,20,23,23,23 };//holds the right most space needed to make a mill with the target. 

	int xAxis[24] = { 0,3,6,1,3,5,2,3,4,0,1,2,4,5,6,2,3,4,1,3,5,0,3,6 }; //loads coordinates for X and Y axis
	int yAxis[24] = { 0,0,0,1,1,1,2,2,2,3,3,3,3,3,3,4,4,4,5,5,5,6,6,6 };//assuming bottom to top, left to right. 

};
#endif // !BOARD_CPP