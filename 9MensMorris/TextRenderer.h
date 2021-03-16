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

const int EMPTY = 0;
const int BLACK = 2;
