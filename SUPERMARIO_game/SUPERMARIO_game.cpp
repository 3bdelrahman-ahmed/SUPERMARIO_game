// SUPERMARIO_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glut.h>
#include <deque>
#include "../Header files/types.h"
using namespace std;

color createColor(float r, float g , float b) {
    color c;
    c.red = r / 255;
    c.green = g / 255;
    c.blue = b / 255;
    return c;
}

color mainBg = createColor(107.0f, 140.0f, 255.0f);
color floorColorPrimary = createColor(230.0f, 90.0f, 15.0f);
color floorColorSecondary = createColor(255.0f, 165.0f, 66.0f);

deque <block> blocks1;
deque <block> blocks2;

void drawLegLeft() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(50.0, 50.0);
    glVertex2f(60.0, 50.0);
    glVertex2f(60.0f, 100.0);
    glVertex2f(50.0, 100.0);
    glEnd();
}
void drawChracter() {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(50.0,50.0);
    glVertex2f(100.0, 50.0);
    glVertex2f(100.0f, 100.0);
    glVertex2f(50.0, 100.0);
    glEnd();
    drawLegLeft();
}
point createPoint(float x , float y) {
    point newPoint;
    newPoint.x = x;
    newPoint.y = y;
    return newPoint;
}

block createBlock(float x , float y , bool isPrimary) {
    block newBlock;
    newBlock.IsPrimary = isPrimary;
    newBlock.bottomLeft = createPoint(x, y);
    newBlock.bottomRight = createPoint(x + 25, y);
    newBlock.topLeft = createPoint(x, y + 25);
    newBlock.topRight = createPoint(x + 25, y + 25);
    return newBlock;
}

void createFloor() {
    float x = 0;
    bool isPrimary = true;
    if (blocks1.empty() && blocks2.empty())
    while (x <= 775) {
        block newBlock = createBlock(x, 0 , isPrimary);
        blocks1.push_back(newBlock);
        newBlock = createBlock(x, 25, (!isPrimary));
        blocks2.push_back(newBlock);
        x += 25;
        isPrimary = !isPrimary;
    }
}

void displayFloor() {
    for (auto it : blocks1) {
        glBegin(GL_POLYGON);
        if(it.IsPrimary)
            glColor3f(floorColorPrimary.red, floorColorPrimary.green, floorColorPrimary.blue);
        else 
            glColor3f(floorColorSecondary.red, floorColorSecondary.green, floorColorSecondary.blue);
        glVertex2f(it.bottomLeft.x , it.bottomLeft.y);
        glVertex2f(it.bottomRight.x , it.bottomRight.y);
        glVertex2f(it.topRight.x , it.topRight.y);
        glVertex2f(it.topLeft.x , it.topLeft.y);
        
        glEnd();
    }
    for (auto it : blocks2) {
        glBegin(GL_POLYGON);

        if (it.IsPrimary)
            glColor3f(floorColorPrimary.red, floorColorPrimary.green, floorColorPrimary.blue);
        else
            glColor3f(floorColorSecondary.red, floorColorSecondary.green, floorColorSecondary.blue);

        glVertex2f(it.bottomLeft.x, it.bottomLeft.y);
        glVertex2f(it.bottomRight.x, it.bottomRight.y);
        glVertex2f(it.topRight.x, it.topRight.y);
        glVertex2f(it.topLeft.x, it.topLeft.y);

        glEnd();
    }
}

block updateBlock(block oldBlock , int isPlus) {
    block newBlock = oldBlock;
    newBlock.bottomLeft.x += (isPlus * 15);
    newBlock.bottomRight.x += (isPlus * 15);
    newBlock.topLeft.x += (isPlus * 15);
    newBlock.topRight.x += (isPlus * 15);
    return newBlock;

}

void updateBlocks(int isPositive) {
    int i = 0;
    for (auto it : blocks1) {
        blocks1[i] = updateBlock(it, isPositive);
        i++;
    }
    i = 0;
    for (auto it : blocks2) {
        blocks2[i] = updateBlock(it, isPositive);
        i++;
    }
}
void startGame() {
    createFloor();
    displayFloor();
    drawChracter();

}
void update(){}
void moveFunction(){}
void timer(){

   glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    startGame();
    glFlush(); // Force execution of GL commands in finite time
}


void specFunc(int key, int x, int y) {
        switch (key)
        {
        case GLUT_KEY_RIGHT:
            updateBlocks(-1);
            block b1 = blocks1[blocks1.size() - 1];
            block b2 = blocks2[blocks1.size() - 1];
            if (b1.bottomRight.x < 800 && b2.bottomRight.x < 800) {
                block newBlock = createBlock(b1.bottomRight.x, 0, !b1.IsPrimary);
                blocks1.push_back(newBlock);
                newBlock = createBlock(b2.bottomRight.x, 25, !b2.IsPrimary);
                blocks2.push_back(newBlock);
            }
            b1 = blocks1[0];
            b2 = blocks2[0];
            if (b1.bottomRight.x < 0 && b2.bottomRight.x < 0) {
                blocks1.pop_front();
                blocks2.pop_front();
            }
            break;
        case GLUT_KEY_LEFT:
            updateBlocks(1);
            block b3 = blocks1[0];
            block b4 = blocks2[0];
            if (b3.bottomLeft.x > 0 && b4.bottomLeft.x > 0) {
                block newBlock = createBlock(b3.bottomLeft.x - 25, 0, !b3.IsPrimary);
                blocks1.push_front(newBlock);
                newBlock = createBlock(b4.bottomLeft.x - 25, 25, !b4.IsPrimary);
                blocks2.push_front(newBlock);
            }
            b3 = blocks1[blocks1.size() - 1];
            b4 = blocks2[blocks2.size() - 1];
            if (b3.bottomLeft.x > 800  && b4.bottomLeft.x > 800) {
                blocks1.pop_back();
                blocks2.pop_back();
            }
            break;
        default:
            break;
        }
        glutPostRedisplay();
}

int main(int argc, char** argr) {
    glutInit(&argc, argr);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Super_Mario_game");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(mainBg.red, mainBg.green, mainBg.blue, 0);
    glutSpecialFunc(specFunc);
    gluOrtho2D(0.0, 800, 0.0, 600);
    glutDisplayFunc(display);

    glutMainLoop();
}
