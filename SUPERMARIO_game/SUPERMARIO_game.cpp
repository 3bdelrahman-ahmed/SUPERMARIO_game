// SUPERMARIO_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glFlush(); // Force execution of GL commands in finite time
}

int main(int argc, char** argr) {
    glutInit(&argc, argr);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Super_Mario_game");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.2f, 0.2f, 0.2f, 0.9f);
    gluOrtho2D(0.0, 800, 0.0, 600);
    glutDisplayFunc(display);

    glutMainLoop();
}
