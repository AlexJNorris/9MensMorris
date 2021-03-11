#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>   
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder   
#include <memory>
#include <array>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mutex>
#include "GameManager.h"

using namespace std;



int sqDistance(int x1, int y1, int x2, int y2);

int get(int x, int y);

void mouse(int button, int state, int x, int y);

void drawFilledSun();

void DrawCircle(float cx, float cy, float r, int num_segments);

void drawNMMBoard(morisGame* Board);