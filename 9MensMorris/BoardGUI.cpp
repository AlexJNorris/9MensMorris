#include<iostream>
#include<vector>

#include<Windows.h>    
#include <iostream>
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder   
#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include "TextRenderer.cpp"
#include "board.cpp"

using namespace std;

class BoardGUI {
	TextRenderer tr;

	BoardGUI() :width_(50), height_(50) {
	}

	BoardGUI(int width, int height) :
		width_(width* content_),
		outerWidth_(width),
		height_(height* content_),
		outerHeight_(height) {
		// Update the corner with the actual x and y coordinate
		for (int i = 0; i < corners_.size(); i++) {
			int x = width_ / 7.0 / 2.0 + corners_[i].first * width_ / 7.0;
			int y = height_ / 7.0 / 2.0 + corners_[i].second * height_ / 7.0;
			corners_[i] = { x,y };
		}
		widthOffset_ = (outerWidth_ - width_) / 2;
		heightOffset_ = (outerHeight_ - height_) / 2;

	}

	void drawCircle(GLfloat x, GLfloat y, GLfloat radius, bool filled) {
		// Draw a circle
		double PI = acos(0) * 2;
		int i;
		int lineAmount = 100; //# of triangles used to draw circle

		GLfloat twicePi = 2.0f * PI;
		if (filled) {
			glBegin(GL_TRIANGLE_FAN);
		}
		else {
			glBegin(GL_LINE_LOOP);
		}
		for (i = 0; i <= lineAmount; i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / lineAmount)),
				y + (radius * sin(i * twicePi / lineAmount))
			);
		}
		glEnd();
	}
	void makePoint(pair<int, int> p) {
		glVertex2f(p.first, p.second);
	}
	int sqDistance(int x1, int y1, int x2, int y2) {
		return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	}

	int get(int x, int y) {
		// Get the color at clicked location
		for (int i = 0; i < corners_.size(); i++) {
			int cx = widthOffset_ + corners_[i].first;
			int cy = heightOffset_ + corners_[i].second;
			if (sqDistance(cx, cy, x, y) <= radius_ * radius_) {
				return i;
			}
		}
		return -1;
	}
	void changeColor(int color) {
		// Change color to "color"
		int b = color & 0xFF;
		color = color >> 8;
		int g = color & 0xFF;
		color = color >> 8;
		int r = color & 0xFF;
		glColor3f(r / 255.0, g / 255.0, b / 255.0);
	}

	void drawBoard() {
		// Draws the whole board
		changeColor(BOARD_BG);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(width_, 0);
		glVertex2f(width_, height_);
		glVertex2f(0, height_);
		glEnd();

		changeColor(GRID_COLOR);
		glLineWidth(4);
		// BIG square
		glBegin(GL_LINE_LOOP);
		makePoint(corners_[0]);
		makePoint(corners_[2]);
		makePoint(corners_[23]);
		makePoint(corners_[21]);
		glEnd();
		// Medium square
		glBegin(GL_LINE_LOOP);
		makePoint(corners_[3]);
		makePoint(corners_[5]);
		makePoint(corners_[20]);
		makePoint(corners_[18]);
		glEnd();
		// Small square
		glBegin(GL_LINE_LOOP);
		makePoint(corners_[6]);
		makePoint(corners_[8]);
		makePoint(corners_[17]);
		makePoint(corners_[15]);
		glEnd();
		// Lines
		glBegin(GL_LINE_STRIP);
		makePoint(corners_[1]);
		makePoint(corners_[7]);
		glEnd();
		glBegin(GL_LINE_STRIP);
		makePoint(corners_[16]);
		makePoint(corners_[22]);
		glEnd();
		glBegin(GL_LINE_STRIP);
		makePoint(corners_[9]);
		makePoint(corners_[11]);
		glEnd();
		glBegin(GL_LINE_STRIP);
		makePoint(corners_[12]);
		makePoint(corners_[14]);
		glEnd();
	}

	void draw(morisGame* gameState, array<int, 24>& extraColors) {
		// Draw the whole board and then all the pieces
		auto boardState = gameState->boardSpaces;
		glTranslatef(widthOffset_, heightOffset_, 0.0);

		drawBoard();

		for (int i = 0; i < boardState.size(); i++) {
			int x = corners_[i].first;
			int y = corners_[i].second;
			// Check the color of the current piece
			if (boardState[i]->isEmpty()) {
				changeColor(EMPTY_COLOR);
				drawCircle(x, y, smallRadius_, CIRCLE_FILL);
			}
			else if (boardState[i]->isPlayerOne()) {
				changeColor(WHITE_COLOR);
				drawCircle(x, y, radius_, CIRCLE_FILL);
			}
			else {
				changeColor(BLACK_COLOR);
				drawCircle(x, y, radius_, CIRCLE_FILL);
			}
			glLineWidth(0.1);
			// Add the extra ring colors if needed
			if (extraColors[i] >= 1 || !boardState[i]->isEmpty()) {
				changeColor(RING_COLOR[extraColors[i]]);
				drawCircle(x, y, radius_, CIRCLE_HOLLOW);
			}
		}

		// Display the information of the game
		vector<string> colorTurns = { "White","Black" };
		vector<string> phasesText = { "Placing Phase","Moving Phase" };
		vector<string> colorRings = { "Last played to","Last played from", "Last removed piece" };
		string turn = colorTurns[gameState->getTurn()] + "'s turn";
		string phaseText = phasesText[gameState->isMovingPhase()];
		string whiteCount = "White: ";
		string blackCount = "Black: ";
		whiteCount.push_back(gameState->count(false) + '0');
		blackCount.push_back(gameState->count(true) + '0');
		// Game title
		tr.print(outerWidth_ + 15, 50, "Nine Men's", 1);
		tr.print(outerWidth_ + 50, 80, "Morris", 1);
		// The current player's turn
		tr.print(outerWidth_ + 15, 150, turn, 1);

		// The current phase
		tr.print(outerWidth_ + 15, 200, phaseText, 1);
		// The number of white pieces left
		tr.print(outerWidth_ + 15, 230, whiteCount, 1);
		// The number of black pieces left
		tr.print(outerWidth_ + 15, 260, blackCount, 1);

		// Draw the colored rings and their meanings:
		int x = outerWidth_ + 15;
		int y = 310;
		for (int i = 0; i < colorRings.size(); i++) {
			changeColor(RING_COLOR[i + 1]);
			drawCircle(x - 20, y - 30, radius_, CIRCLE_HOLLOW);
			tr.print(x + 20, y, colorRings[i], 0.6);
			y += 30;
		}

		// The option to go to the main menu 
		tr.print(outerWidth_ + 15, y + 20, "M: Main Menu", 0.8);
		// The option to restart the game with same parameters 
		tr.print(outerWidth_ + 15, y + 50, "R: Restart", 0.8);

		glTranslatef(-widthOffset_, -heightOffset_, 0.0);
	}

	private:
		

		/// Percentage of the content of the board
		double content_ = 0.9;
		/// The radius of an empty cell
		int smallRadius_ = 6;
		/// The radius of a cell with a piece
		int radius_ = 12;
		/// The x offset of the outer board to the inner board
		int widthOffset_;
		/// The y offset of the outer board to the inner board
		int heightOffset_;
		/// The corners of the board
		vector<pair<int, int> > corners_ = {
			{0,0},{3,0},{6,0},
			{1,1},{3,1},{5,1},
			{2,2},{3,2},{4,2},
			{0,3},{1,3},{2,3},{4,3},{5,3},{6,3},
			{2,4},{3,4},{4,4},
			{1,5},{3,5},{5,5},
			{0,6},{3,6},{6,6}
		};
		/// The width of the board
		int width_;
		/// The outer width of the board
		int outerWidth_;
		/// The height of the board
		int height_;
		/// The outer height of the board
		int outerHeight_;
};