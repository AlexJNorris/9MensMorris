#pragma once
#include<stdio.h> 

#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h> 
#include<string>
#include "Board.h"

using namespace std;



//function to place tokens based on which player's turn it is
void placeToken(int playerNum, morisGame* Board);
void manageGame(morisGame* Board);