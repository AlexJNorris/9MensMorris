// 9MensMorris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
 

#include "BoardGUI.h"
using namespace std;

/// This is the last position that was played by the human player
int pos_;
morisGame* Board = new morisGame;
vector<boardSpace*> gameState;

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
        pos_ = get(x, y);
        cout << pos_;
        //Board->setBoardPiece(pos_);
    }
}
// main function    
void display(void)
{
    glClearColor(1, 1, 1, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);


   
    drawNMMBoard(Board);

    manageGame(Board);

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