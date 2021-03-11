#pragma once

#include<iostream>
#include<vector>
#include<Windows.h>   
#include <GL/glut.h>
#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include <string>

using namespace std;

void print(int x, int y, string text, double size);
void printCenter(int x, int y, string text, double size);
double textWidth(string text, double size);

//Declare Global Variables


const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 500;
const double SCREEN_SHRINK_RATIO = 2;

const int BOARD_WIDTH = 500;
const int BOARD_HEIGHT = 500;
const int BOARD_BG = 0xF7E4D2;

const int EMPTY_COLOR = 0x9B9B9B;
const int WHITE_COLOR = 0xFFFFFF;
const int BLACK_COLOR = 0x000000;
const array<int, 4> RING_COLOR = { 0x141414,0xFF0000,0x00FF00,0x0000FF };
const int GRID_COLOR = 0x9B9B9B;

const bool CIRCLE_FILL = true;
const bool CIRCLE_HOLLOW = false;

const int PLACING_PHASE = 0;
const int MOVING_PHASE = 1;

const int EMPTY = 0;
const int WHITE = 1;
const int BLACK = 2;

const int MENU_SCREEN = 0;
const int GAME_SCREEN = 1;
const int SKIP_SCREEN = 2;
