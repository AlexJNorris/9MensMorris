// 9MensMorris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
 
#include "BoardGUI.h"
#include "Board.h"
#include "Computer.h"
using namespace std;

/// This is the last position that was played by a player
int pos_;
morisGame* Board = new morisGame;
vector<boardSpace*> gameState;
Computer* cmp = new Computer();

// Init_OpenGL() function    
void Init_OpenGL()
{
    // set background color to Black    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // set shade model to Flat    
    glShadeModel(GL_FLAT);
}


void display2(int x) {
    glutPostRedisplay();
    glutTimerFunc(100, display2, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //// << x << ", " << y << endl;
        if (Board->gameMode == 0)
        {
            pos_ = getMenu(x, y);
        }
        else if (Board->gameMode == 1)
        {
            pos_ = get(x, y);
        }
        else
        {
            if (Board->turns % 2 == 0)
            {
                pos_ = get(x, y);
            }
        }
        if ((pos_ < 24 && pos_ > -1)  || pos_ == 25)
        {
            Board->manageGame(pos_);
        }
        if (Board->toBePlacedP2.size() == 0 && ((Board->activePlayer1.size() >= 4) || (Board->activePlayer2.size() >= 4)))
        {
            Board->noValidMoves();
        }
    }

}
// main function    
void display(void)
{
    glClearColor(1, 1, 1, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    drawNMMBoard(Board);

    if (Board->turns % 2 == 1 && Board->gameMode == 2 && !Board->gameOver)
    {
        pos_ = cmp->makeMove(Board);
        if ((pos_ < 24 && pos_ > -1))
        {
            Board->manageGame(pos_);
        }
    }
   

    //manageGame(Board);

}

int main(int argc, char* argv[])
{

    Board->setBoard();
    glutInit(&argc, argv);
    glutInitWindowSize(640, 500);
    glutInitWindowPosition(1, 1);

    glutCreateWindow("Nine Men's Morris");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(100, display2, 0);
    glutMainLoop();

    return EXIT_SUCCESS;
}