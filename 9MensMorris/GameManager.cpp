#include<stdio.h> 

#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h> 
#include<string>
#include "Board.cpp"
#include "BoardGUI.cpp"

using namespace std;
//function to place tokens based on which player's turn it is

class GameManager {

public:
    GameManager() 
    {
        return;
    }

    GameManager(morisGame* board)
    {
        manageGame(board);
    }

    void placeToken(int playerNum, morisGame Board)
    {
        string place;

        /*cout << endl << "Enter place for player " << playerNum << " # (0-23): ";
        cin >> place;

        if (playerNum == 1)
            Board.setBoardPiece(stoi(place));
        else
            Board.setBoardPieceP2(stoi(place));
            */
        /*
        Board.consoleOut();
        */
    }

    //function to eventually move tokens after all have been placed
    /*void moveToken(int playerNum, morisGame Board)
    {
        //Insert moving token code here
    }*/

    //function that manages the turn taking
    void manageGame(morisGame* Board)
    {
        string place;

        int turnNum = 0;    // variable to track what turn it currently is

        Board->setBoard();

        //while the game isn't over, continue to take turns
        while (!Board->getGameOver())
        {
            if (Board->toBePlacedP1.size() == 0)
            {
                Board->movingPhase = 1;
                //moveToken(1, Board);
                //moveToken(2, Board);
                //checkMills();
                return;
            }
            else
            {
                placeToken(1, *Board);
                Board->turns++;
                placeToken(2, *Board);
                Board->turns++;
            }
            turnNum++;
        }
    }
};