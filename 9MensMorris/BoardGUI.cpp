


#include "BoardGUI.h"

using namespace std;


/// The radius of a cell with a piece
int radius_ = .05;
/// The corners of the board
vector<pair<float, float> > corners_ = {
    {-.7,.7},{0,.7},{.7,.7},
    {-.4,.4},{0,.4},{.4,.4},
    {-.1,.1},{0,.1},{.1,.1},
    {-.7,0},{-.4,0},{-.1,0},{.1,0},{.4,0},{.7,0},
    {-.1,-.1},{0,-.1},{.1,-.1},
    {-.4,-.4},{0,-.4},{.4,-.4},
    {-.7,-.7},{0,-.7},{.7,-.7}
};

vector<pair<int, int> > mouseCoordinates = {
    {89,67},{313,67},{537,67},
    {185,142},{313,142},{441,142},
    {280,217},{313,217},{345,217},
    {89,242},{185,242},{280,242},{345,242},{441,242},{537,242},
    {280,267},{313,267},{345,267},
    {185,341},{313,341},{441,341},
    {89,417},{313,417},{537,417}
};

int sqDistance(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int get(int x, int y) {
    // Get the color at clicked location
    for (int i = 0; i < 24; i++) {
        int cx = 10 + (mouseCoordinates[i].first);
        int cy = 10 + (mouseCoordinates[i].second);
        if (sqDistance(cx, cy, x, y) <= 15 * 15) {
            return i;
        }
    }
    return -1;
}




void drawFilledSun() {
    //static float angle;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -10);
    int i, x, y;
    double radius = 0.30;
    //glColor3ub(253, 184, 19);     
    glColor3ub(255, 0, 0);
    double twicePi = 2.0 * 3.142;
    x = 0, y = 0;
    glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= 20; i++) {
        glVertex2f(
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
        );
    }
    glEnd(); //END
}
void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}
void drawNMMBoard(morisGame* Board) 
{
    boardSpace* state;
    glColor3f(0.7, 0.7, 0.7);
    //outside top
    glVertex2f(.7, .7);
    glVertex2f(-.7, .7);
    //outside bottom
    glVertex2f(.7, -.7);
    glVertex2f(-.7, -.7);
    //outside right
    glVertex2f(.7, .7);
    glVertex2f(.7, -.7);
    //outside left
    glVertex2f(-.7, .7);
    glVertex2f(-.7, -.7);

    //top connector
    glVertex2f(0, .7);
    glVertex2f(0, .1);
    //bottom connector
    glVertex2f(0, -.7);
    glVertex2f(0, -.1);
    //right connector
    glVertex2f(.7, 0);
    glVertex2f(.1, 0);
    //left connector
    glVertex2f(-.7, 0);
    glVertex2f(-.1, 0);

    //middle top
    glVertex2f(.4, .4);
    glVertex2f(-.4, .4);
    //middle bottom
    glVertex2f(-.4, -.4);
    glVertex2f(.4, -.4);
    //middle right
    glVertex2f(.4, -.4);
    glVertex2f(.4, .4);
    //middle left
    glVertex2f(-.4, -.4);
    glVertex2f(-.4, .4);

    //inner top
    glVertex2f(.1, .1);
    glVertex2f(-.1, .1);
    //inner bottom
    glVertex2f(-.1, -.1);
    glVertex2f(.1, -.1);
    //inner right
    glVertex2f(.1, -.1);
    glVertex2f(.1, .1);
    //inner left
    glVertex2f(-.1, -.1);
    glVertex2f(-.1, .1);
    glEnd();

    glFlush();
    //draw placements
    glColor3f(0, 0, 0);
    print(300,20, "Nine Men's Morris", .5);
 
    if (Board->toBePlacedP1.size() != 0 || Board->toBePlacedP2.size() != 0)
    {
        glColor3f(1, 0, 0);
        print(50, 50, "P1's Pieces To Be Placed: " + to_string(Board->toBePlacedP1.size()), .5);
        glColor3f(0, 0, 0);
        print(460, 50, "P2's Pieces To Be Placed: " + to_string(Board->toBePlacedP2.size()), .5);
    } 
    else
    {
        glColor3f(1, 0, 0);
        print(50, 50, "P1's Pieces Left: " + to_string(Board->activePlayer1.size()), .5);
        glColor3f(0, 0, 0);
        print(460, 50, "P2's Pieces Left: " + to_string(Board->activePlayer2.size()), .5);

    }

    if (Board->getTurn() == 0) {
        glColor3f(1, 0, 0);
        print(274, 464, "Player 1's Turn", .8);
    }
    else
    {
        glColor3f(0, 0, 0);
        print(274, 464, "Player 2's Turn", .8);
    }

    //to highlight selected piece in green
    /*glPointSize(20.0);
    glBegin(GL_POINTS);
    glColor3f(0, 0.8, 0);
    for (int i = 0; i < corners_.size(); i++) {
        state = Board->boardSpaces[i];
        glVertex2f(corners_[i].first, corners_[i].second);
    }

    glEnd();
    glFlush();*/

    //to highlight mills in yellow
    glPointSize(25.0);
    glBegin(GL_POINTS);
    glColor3f(.9, .9, 0);
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board->p1MillArr[i][j] == -1) { break; }
            glVertex2f(corners_[Board->p1MillArr[i][j]].first, corners_[Board->p1MillArr[i][j]].second);

        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board->p2MillArr[i][j] == -1) { break; }
            glVertex2f(corners_[Board->p2MillArr[i][j]].first, corners_[Board->p2MillArr[i][j]].second);

        }
    }
    

    glEnd();
    glFlush();

    glPointSize(15.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < corners_.size(); i++) {
        state = Board->boardSpaces[i];
        
        if (state->isEmpty()) 
        {
            glColor3f(0.8, 0.8, 0.8);
        } 
        else if (state->isPlayerOne()) {
            glColor3f(1, 0, 0);
        }
        else
        {
            glColor3f(0, 0, 0);
        }
        glVertex2f(corners_[i].first, corners_[i].second);
    }

    glEnd();

    glFlush();
    
}
