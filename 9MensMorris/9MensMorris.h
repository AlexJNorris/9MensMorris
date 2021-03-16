#pragma once

#include "BoardGUI.h"
using namespace std;

/// This is the last position that was played by a player
int pos_;
morisGame* Board = new morisGame;
vector<boardSpace*> gameState;

// Init_OpenGL() function    
void Init_OpenGL();


void display2(int x);

void mouse(int button, int state, int x, int y);
// main function    
void display(void);

int main(int argc, char* argv[]);