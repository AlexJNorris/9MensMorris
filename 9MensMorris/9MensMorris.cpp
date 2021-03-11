// 9MensMorris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<Windows.h>    
// first include Windows.h header file which is required    
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder   
#include "GameManager.cpp"
#include "Board.cpp"
// Init_OpenGL() function    
void Init_OpenGL()
{
    // set background color to Black    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // set shade model to Flat    
    glShadeModel(GL_FLAT);
}


void display() {

    shared_ptr<morisGame> game = nullptr;
    game->display();
}
void display2(int x) {
    glutPostRedisplay();
    glutTimerFunc(100, display2, 0);
}
void mouse(int button, int state, int x, int y) {
  //  nineMen->mouse(button, state, x, y);
}
void keyboard(unsigned char key, int x, int y) {
  //  nineMen->keyboard(key, x, y);
}

// main function    
int main(int argc, char** argv)
{
    //string place;
    //string q;

    // initialize glut    


  //  morisGame* Board = new morisGame;
   // GameManager gameManager;
   // gameManager.manageGame(Board);
    
    // Initialize GLUT
    glutInit(&argc, argv);
    // Create a window with the given title
    glutCreateWindow("Nine Men Morris");
    // Set the window's initial width & height
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
    // Register display callback handler for window re-paint 
    glutDisplayFunc(display);
    glutTimerFunc(100, display2, 2);
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
    
    system("pause");
    return 0;
}