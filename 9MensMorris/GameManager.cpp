
#include "GameManager.h"

    void placeToken(int playerNum, morisGame* Board)
    {
        int changeChk = Board->turns;
        string place;
        
        cout << endl << "Enter place for player " << playerNum << " # (0-23): ";
        cin >> place;

        while (changeChk == Board->turns) {

            if (stoi(place) > -1 && stoi(place) < 24) {
                if (Board->boardSpaces[stoi(place)]->isEmpty()) {
                    if (playerNum == 0)
                    {
                        Board->setBoardPiece(stoi(place));
                        break;
                    }
                    else
                    {
                        Board->setBoardPieceP2(stoi(place));
                        break;
                    }
                }
                cout << endl << "Spot is taken - Enter different number " << " # (0-23): ";
                cin >> place;
            }
            else
            {
                cout << endl << "Out of range - Enter different number " << " # (0-23): ";
                cin >> place;
            }
            
        }
        
        Board->consoleOut();
        
    }

    //function to eventually move tokens after all have been placed
    /*void moveToken(int playerNum, morisGame Board)
    {
        //Insert moving token code here
    }*/

    //function that manages the turn taking
    void manageGame(morisGame* Board)
    {
        string place;   // variable to track what turn it currently is
       

        //while the game isn't over, continue to take turns
            if (Board->toBePlacedP2.size() == 0)
            {
                Board->movingPhase = 1;
                //moveToken(1, Board);
                //moveToken(2, Board);
                //checkMills();
                return;
            }
            else
            {
                
                    placeToken(Board->getTurn(), Board);
                    Board->turns++;

            }
    }
    
