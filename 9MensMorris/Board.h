#pragma once
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
#include<thread>
#include<mutex>



using namespace std;
class gameToken;
class boardSpace;
class morisGame;

class gameToken
{
public:
	bool isPlaced();
	void setName(int num);
	void setPlayer(bool player);
	void setLocation(boardSpace* place);
	int getName();
	bool getPlayer();
	boardSpace* getLocation();

private:
	int tokenName;
	bool tokenPlayer;
	boardSpace* tokenLocation;
};

class boardSpace {

public:

	gameToken* placedToken;

	bool isEmpty();
	bool isPlayerOne();
	bool isPlayerTwo();
	void setName(int num);
	int getName();
	void placeToken(gameToken* piece);
	gameToken* getToken();
	void addAdjacent(boardSpace* Space);
	void addVerticle(boardSpace* Space);
	void addHorizontal(boardSpace* Space);
	boardSpace* getAdjacent(int i);
	boardSpace* getVerticle(int i);
	boardSpace* getHorizontal(int i);
	void setY(int num);
	void setX(int num);
	int getX();
	int getY();

private:

	int spaceName;
	int xAxis;
	int yAxis;
	vector<boardSpace*> adjacentSpaces; //holds spaces physicly adjacent to this one.
	vector<boardSpace*> verticleMill; //holds spaces needed for a verticle mill with this one. 
	vector<boardSpace*> horizontalMill; // holds spcaes needed for a horizontal mill with this one. 

};

#ifndef MORISGAME
#define MORISGAME

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


	int pos;
	bool updateScene = true;
	bool playing = true;

	int selected;
	int previousSelected;
	int deleted;


	/// This points to the class that encapsulates the state of the game
	shared_ptr<boardSpace> gameState;
	/// This points to the class that manages the A.I. agent that playes against the human player
	/// This mutex is unlocked everytime the human player makes a move
	/// This mutex is unlocked everytime the white player makes a move
	mutex whiteMove;
	/// This mutex is unlocked everytime the black player makes a move
	mutex blackMove;
	/// Mutex to indicated that the object is safe to be deleted


	morisGame();
	int count(bool b);
	int getTurn();
	int isMovingPhase();
	void setBoard();
	void consoleOut();
	void setBoardPiece(int xy);
	void setBoardPieceP2(int xy);
	bool getGameOver();

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

#endif // !1