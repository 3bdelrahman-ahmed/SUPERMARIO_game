// SUPERMARIO_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glut.h>
#include <deque>
#include<cmath>
#include <algorithm>

#include "../Header files/types.h"
using namespace std;
float M_PI = 3.14159265358979323846;
int healthBarLevel = 0;
float cloudPos = 590;
int score = 0;

color createColor(float r, float g , float b) {
    color c;
    c.red = r / 255;
    c.green = g / 255;
    c.blue = b / 255;
    return c;
}

coin createCoin(float x, float y) {
    coin newCoin;
    newCoin.x = x;
    newCoin.y = y;
    return newCoin;
}
coin mainCoin = createCoin(1100.0f , 100.0f );

color mainBg = createColor(107.0f, 140.0f, 255.0f);
color floorColorPrimary = createColor(230.0f, 90.0f, 15.0f);
color floorColorSecondary = createColor(255.0f, 165.0f, 66.0f);
color green = createColor(13.0f , 180.0f , 14.0f);
color grey = createColor(54.0f, 54.0f, 54.0f);
color yellow = createColor(219.0f , 216.0f , 14.0f);
color red = createColor(254.0f, 8.0f, 8.0f);
color coinColorPrimary = createColor(255.0f, 200.0f, 60.0f);
color coinColorSecondary = createColor(240.0f, 142.0f, 9.0f);
color obstacleBorderColor = createColor(115.0f , 75.0f , 40.0f);
color obstaclePrimaryColor = createColor(195.0f, 152.0f, 107.0f); 
color obstacleSecondaryColor = createColor(218, 187, 156);
color healthBar[] = {green , yellow , red};

character mainCharacter;
obstacle checkObstcale;
deque <block> blocks1;
deque <block> blocks2;


void drawLegs() {
    // left leg
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(55.0,50.0);//a
    glVertex2f(72.0,50.0);//b
    glVertex2f(72.0,70.0);//c
    glVertex2f(55.0,70.0);//d
    glEnd();
    // right leg
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(80.0, 50.0);//a
    glVertex2f(97.0, 50.0);//b
    glVertex2f(97.0, 70.0);//c
    glVertex2f(80.0, 70.0);//d
    glEnd();
}

void drawCircle(float radius, int segments, float x,float y,float xColor,float yColor,float zColor) {
    glPushMatrix();
    glTranslated(x, y, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(xColor, yColor, zColor);
    for (int i = 0; i < segments; ++i) {
        float theta = static_cast<float>(i) / segments * (2.0 * M_PI);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();
    glPopMatrix();
}
void drawCloud(float x) {
    glPushMatrix();
    glTranslated(x, -30, 0);
    drawCircle(30.0,100.0,250.0,500.0,1.0,1.0,1.0);
    drawCircle(30.0, 100.0, 240.0, 510.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 265.0, 510.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 265.0, 525.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 300.0, 525.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 300.0, 500.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 330.0, 525.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 345.0, 500.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 355.0, 500.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 360.0, 520.0, 1.0, 1.0, 1.0);
    drawCircle(30.0, 100.0, 380.0, 510.0, 1.0, 1.0, 1.0);
    glPopMatrix();
}
void drawBody() {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(50.0f,70.0f);//a
    glVertex2f(100.0f,70.0f);//b
    glVertex2f(115.0f, 85.0f);//c
    glVertex2f(115.0f,115.0f);//d
    glVertex2f(100.0f,130.0f);//e
    glVertex2f(50.0f,130.0f);//f
    glVertex2f(35.0f,115.0f);//g
    glVertex2f(35.0f,85.0f);//h
    glEnd();
    drawCircle(15.0, 100.0, 49.5f, 115.5f, 1.0, 0.0, 0.0); // top left
    drawCircle(15.0,100.0,100.5f,115.5f, 1.0, 0.0, 0.0);// top right
    drawCircle(15.0,100.0,50.5,85.5, 1.0, 0.0, 0.0);// bottom left
    drawCircle(15.0, 100.0, 100, 84.5,1.0,0.0,0.0);// bottom right

}

void handleCollectCoin() {
    if (mainCoin.x < 160 && mainCoin.x > 20 && mainCharacter.y <= 130 && !mainCoin.isCollected) {
        score += 10;
        mainCoin.isCollected = true;
    }
}

void drawEyes() {
    drawCircle(11.65, 100.0, 75.0, 108.0, 1.0, 1.0, 1.0);
    drawCircle(11.65, 100.0, 97.0, 108.0, 1.0, 1.0, 1.0);
    drawCircle(5.5,100.0,75.0,108.0,0.0,0.0,0.0);
    drawCircle(5.5, 100.0, 97.0, 108.0, 0.0, 0.0, 0.0);
}

void drawBlindfold() {
    glPushMatrix();
    glTranslated(5,5,0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(28.0,105.0);//a
    glVertex2f(112.0,105.0);//b
    glVertex2f(108.5,120.0);//c
    glVertex2f(30.0,120.0);//d
    glEnd();
    glPopMatrix();
}

void drawHealthBar() {
    glBegin(GL_POLYGON);
    glColor3f(grey.red, grey.green, grey.blue);
    glVertex2f(580.0f, 550.0f);//a
    glVertex2f(780.0f, 550.0f);//b
    glVertex2f(780.0f, 570.0f);//c
    glVertex2f(580.0f, 570.0f);//d
    glEnd();
    // character health
    glBegin(GL_POLYGON);
    glColor3f(healthBar[healthBarLevel].red, healthBar[healthBarLevel].green, healthBar[healthBarLevel].blue);
    glVertex2f(580.0f, 550.0f);//a
    glVertex2f(580.0f + mainCharacter.helath, 550.0f);//b
    glVertex2f(580.0f + mainCharacter.helath, 570.0f);//c
    glVertex2f(580.0f, 570.0f);//d
    glEnd();
}

void drawChracter() {
    glPushMatrix();
    glTranslated(35, mainCharacter.y , 0);
    glPushMatrix();
    glTranslated(-35, -50, 0);
    drawBody();
    drawEyes();
    drawBlindfold();
    drawLegs();
    glPopMatrix();
    glPopMatrix();
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

obstacle createObstacle(float x , float y) {
    obstacle newObstacle;
    newObstacle.x = x;
    newObstacle.y = y;
    return newObstacle;
}

void drawObstacle() {

    glPushMatrix();
    glTranslated(checkObstcale.x , 50 , 0.0);
    if (checkObstcale.isShape1) {
        glBegin(GL_POLYGON);
        glColor3f(obstacleBorderColor.red, obstacleBorderColor.green, obstacleBorderColor.blue);
        glVertex2f(0.0, 0.0);//a
        glVertex2f(40.0, 0.0);//b
        glVertex2f(40.0, 75.0);//c
        glVertex2f(0.0, 75.0);//d
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(obstacleBorderColor.red, obstacleBorderColor.green, obstacleBorderColor.blue);
        glVertex2f(0.0, 75.0);//a
        glVertex2f(40.0, 75.0);//b
        glVertex2f(40.0, 110.0);//c
        glVertex2f(0.0,110.0);//d
        glEnd();
        

        glBegin(GL_POLYGON);
        glColor3f(obstacleSecondaryColor.red, obstacleSecondaryColor.green, obstacleSecondaryColor.blue);
        glVertex2f(4, 4);//a
        glVertex2f(36, 4);//b
        glVertex2f(36, 75.0);//c
        glVertex2f(4, 75.0);//d
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(obstaclePrimaryColor.red, obstaclePrimaryColor.green, obstaclePrimaryColor.blue);
        glVertex2f(4, 75);//a
        glVertex2f(36, 75);//b
        glVertex2f(36, 106);//c
        glVertex2f(4,106.0);//d
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(obstaclePrimaryColor.red, obstaclePrimaryColor.green, obstaclePrimaryColor.blue);
        glVertex2f(10.0, 75);//a
        glVertex2f(15, 75);//b
        glVertex2f(12.5, 65);//c
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(obstaclePrimaryColor.red, obstaclePrimaryColor.green, obstaclePrimaryColor.blue);
        glVertex2f(25.0, 75);//a
        glVertex2f(35.0, 75);//b
        glVertex2f(30.0, 60);//c
        glEnd();
    }
    else {
        glBegin(GL_POLYGON);
        glColor3f(obstacleBorderColor.red, obstacleBorderColor.green, obstacleBorderColor.blue);
        glVertex2f(0.0, 0.0);//a
        glVertex2f(55.0, 0.0);//b
        glVertex2f(55.0, 55.0);//c
        glVertex2f(0.0, 55.0);//d
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(obstaclePrimaryColor.red, obstaclePrimaryColor.green, obstaclePrimaryColor.blue);
        glVertex2f(5, 5);//a
        glVertex2f(50.0, 5);//b
        glVertex2f(50.0, 50.0);//c
        glVertex2f(5, 50.0);//d
        glEnd();
        drawCircle(10, 100, 27.5, 27.5, obstacleBorderColor.red, obstacleBorderColor.green, obstacleBorderColor.blue);
    }
    glPopMatrix();

}

void showCoin(float x, float y) {
    glPushMatrix();
    glTranslated(x, y, 0.0);
    drawCircle(32.0f, 100, 0, 0, coinColorPrimary.red, coinColorPrimary.green, coinColorPrimary.blue);
    drawCircle(25.0f, 100, 0, 0, coinColorSecondary.red, coinColorSecondary.green, coinColorSecondary.blue);
    drawCircle(15.0f, 100, 0, 0, coinColorPrimary.red, coinColorPrimary.green, coinColorPrimary.blue);
    glPopMatrix();
}

void startGame() {
    createFloor();
    displayFloor();

    drawChracter();
    drawHealthBar();
    drawCloud(cloudPos);
    drawObstacle();
    if(!mainCoin.isCollected)
        showCoin(mainCoin.x, mainCoin.y);
}

void handleCrash() {
    if (!mainCharacter.isCrashed && checkObstcale.isShape1 && mainCharacter.y < 160 && mainCharacter.y > 140 && checkObstcale.x < 97 && checkObstcale.x > 15) {
        mainCharacter.helath -= 20;
        mainCharacter.isCrashed = true;
    }
    else if (!mainCharacter.isCrashed && checkObstcale.isShape1 && mainCharacter.y <= 140 && checkObstcale.x < 115 && checkObstcale.x > -5) {
        mainCharacter.helath -= 20;
        mainCharacter.isCrashed = true;
    }
    else if (!mainCharacter.isCrashed && !checkObstcale.isShape1 && mainCharacter.y < 105 && mainCharacter.y > 85 && checkObstcale.x < 97 && checkObstcale.x > 0) {
        mainCharacter.helath -= 20;
        mainCharacter.isCrashed = true;
    }
    else if (!mainCharacter.isCrashed && !checkObstcale.isShape1 && mainCharacter.y <= 85 && checkObstcale.x < 115 && checkObstcale.x > -20) {
        mainCharacter.helath -= 20;
        mainCharacter.isCrashed = true;
    }
    if (mainCharacter.helath <= 100 && mainCharacter.helath > 50) healthBarLevel = 1;
    else if (mainCharacter.helath <= 50) healthBarLevel = 2;
}

void update(){}
void moveFunction(){}
void timer(int value){
    cloudPos -= 10;
    if (cloudPos <= -450) cloudPos = 590;
    if (mainCharacter.isJumping) {
        mainCharacter.y += 10;
        if (mainCharacter.y > 250) mainCharacter.isJumping = false;
    }
    else if(mainCharacter.y > 50) {
        mainCharacter.y -= 15;
        mainCharacter.y = max(50.0f, mainCharacter.y);
    }
    handleCollectCoin();
    handleCrash();
    glutPostRedisplay();
    glutTimerFunc(75, timer, 0);		//75 milliseconds
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
            checkObstcale.x -= 15;
            cout << checkObstcale.x << endl;
            mainCoin.x -= 15;
            cloudPos -= 3;
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

            handleCrash();
            handleCollectCoin();
            if (mainCoin.x < -40) {
                mainCoin.x = checkObstcale.x + 250;
                mainCoin.isCollected = false;
            }

            if (checkObstcale.isShape1 && checkObstcale.x < -40) {
                mainCharacter.isCrashed = false;
                checkObstcale.x = 800;
                checkObstcale.isShape1 = rand() % 2;
            }
            else if (!checkObstcale.isShape1 && checkObstcale.x < -55) {
                mainCharacter.isCrashed = false;
                checkObstcale.x = 800;
                checkObstcale.isShape1 = rand() % 2;
            }
            break;
        case GLUT_KEY_UP :
            mainCharacter.isJumping = true;
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
    glutTimerFunc(0, timer, 0);
    gluOrtho2D(0.0, 800, 0.0, 600);
    glutDisplayFunc(display);

    glutMainLoop();
}
