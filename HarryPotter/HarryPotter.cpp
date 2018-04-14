#include "TextureBuilder.h"
#include <stdio.h>
#include <math.h>
#include <glut.h>
#include <time.h>



#define GLUT_KEY_ESCAPE 27

GLuint texID;
GLuint texID2;

int rep = 1;

bool Victory = false;
bool Defeat = false;

bool newStartingPointEnemy = true;
bool newStartingPointEnemy2 = true;
bool newStartingPointBall = true;
bool newStartingPointPowerUp = true;

int RotationAngle = 0;
bool RotatingUp = false;
bool RotatingDown = false;
bool RotatingToNormal = false;

bool spawnPowerUp = false;
bool randomize = true;
int spawnCounter;
int powerUpCounter = 0;

//enemy path
int p0Enemy[2];
int p1Enemy[2];
int p2Enemy[2];
int p3Enemy[2];
double tEnenmy = 0.0;

//enemy2 path
int p0Enemy2[2];
int p1Enemy2[2];
int p2Enemy2[2];
int p3Enemy2[2];
double tEnenmy2 = 0.0;

//ball path
int p0Ball[2];
int p1Ball[2];
int p2Ball[2];
int p3Ball[2];
double tBall = 0.0;

//power up path
int p0PowerUp[2];
int p1PowerUp[2];
int p2PowerUp[2];
int p3PowerUp[2];
double tPowerUp = 0.0;



int firstBackground = 0;
int secondBackground = 0;
int cloud = 1000;
int cloud2 = 1200;
//main character
int mainXtranslation = 0;
int mainYtranslation = 0;
int mainXposition = 490;
int mainYposition = 320;
int mainHitboxRadius = 60;
//enemy
int enemyHitboxRadius = 10;
int enemyXtranslation = 1000;
int enemyYtranslation = -200;
int enemyXposition = 490;
int enemyYposition = 310;
//enemy2
int enemy2HitboxRadius = 10;
int enemy2Xtranslation = 1000;
int enemy2Ytranslation = -200;
int enemy2Xposition = 490;
int enemy2Yposition = 310;
//power up
int powerUpXposition = 100;
int powerUpYposition = 100;
int powerUpXtranslation = 1000;
int powerUpYtranslation = 400;
int powerUpHitbox = 2;
//ball
int ballXposition = 100;
int ballYposition = 100;
int ballXtranslation = 0;
int ballYtranslation = 0;
int ballHitboxRadius = 5;
int BallRotation = 0;
//snitch
int snitchXposition = 90;
int snitchYposition = 90;
int snitchHitboxRadius = 20;
int snitchXtranslation = 850;
int snitchYtranslation = 200;


int bezierX(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res;
	res = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	return res;
}

int bezierY(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res;
	res = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}

// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and its radius
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

// draws a simple triangle
void drawTriangle(int x, int y, int length) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x+length,y);
	glVertex2f(x + (length)/2, y + (length*(sqrt(3)/2)));
	glEnd();
}

// draws the main character in the middle of the screen
void drawMainCharacter() {
	// yellow triangle
	glPushMatrix();
	glTranslated(137, -85, 0);
	glTranslated(300, 400, 0);
	glRotated(-90, 0, 0, 1);
	glTranslated(-300, -400, 0);
	glColor3f(1, 1, 0);
	drawTriangle(300, 400, 25);
	glPopMatrix();

	//left upper leg
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left lower leg
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-165, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left upper arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left lower arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(40, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left hand
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(59, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 5, 10);
	glPopMatrix();

	//left upper finger
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(61, 40, 0);
	glTranslated(470, 305, 0);
	glRotated(-20, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 3, 10);
	glPopMatrix();

	//left lower finger
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(61, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 7, 3);
	glPopMatrix();

	// wooden stick
	glPushMatrix();
	glColor3f(0.55, 0.41, 0.29);
	drawRect(450, 300, 100, 5);
	glPopMatrix();

	// body
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(470, 305, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 55, 20);
	glPopMatrix();

	// right upper leg
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(-14, 14, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 50, 10);
	glPopMatrix();

	//right lower leg
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-135, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left foot
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(-21, -24, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right foot
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(-10, -38, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right upper arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//right lower arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(27, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 21, 10);
	glPopMatrix();

	//right hand
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	glTranslated(42, 0, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 10, 10);
	glPopMatrix();

	// back hair
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-2, 7, 0);
	drawCircle(510, 360, 13);
	glPopMatrix();

	// head
	glPushMatrix();
	glColor3f(0.9, 0.72, 0.63);
	drawCircle(510, 360, 13);
	glPopMatrix();

	// eye
	glPushMatrix();
	glTranslated(3, 3, 0);
	glColor3f(1, 1, 1);
	drawCircle(510, 360, 3);
	glPopMatrix();

	// eye color
	glPushMatrix();
	glTranslated(4, 3, 0);
	glColor3f(0, 0, 1);
	drawCircle(510, 360, 2);
	glPopMatrix();

	//mouth
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(7, 0, 0);
	glTranslated(512, 350, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-512, -350, 0);
	drawTriangle(512, 350, 7);
	glPopMatrix();

	//front hair
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-1, -5, 0);
	glTranslated(498, 367, 0);
	glRotated(20, 0, 0, 1);
	glTranslated(-498, -367, 0);
	drawRect(498, 367, 25, 7);
	glPopMatrix();

	//cape
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(-33, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 70, 21);
	glPopMatrix();

	//cape end
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(-45, 12, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();

	//cape front
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslated(16, 29, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();
}

void drawEnemy() {
	// yellow triangle
	glPushMatrix();
	glTranslated(137, -85, 0);
	glTranslated(300, 400, 0);
	glRotated(-90, 0, 0, 1);
	glTranslated(-300, -400, 0);
	glColor3f(1, 1, 0);
	drawTriangle(300, 400, 25);
	glPopMatrix();

	//left upper leg
	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left lower leg
	glPushMatrix();
	glColor3f(0.8, 0, 0);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-165, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left upper arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left lower arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(40, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left hand
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(59, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 5, 10);
	glPopMatrix();

	//left upper finger
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(61, 40, 0);
	glTranslated(470, 305, 0);
	glRotated(-20, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 3, 10);
	glPopMatrix();

	//left lower finger
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(61, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 7, 3);
	glPopMatrix();

	// wooden stick
	glPushMatrix();
	glColor3f(0.55, 0.41, 0.29);
	drawRect(450, 300, 100, 5);
	glPopMatrix();

	// body
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(470, 305, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 55, 20);
	glPopMatrix();

	// right upper leg
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-14, 14, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 50, 10);
	glPopMatrix();

	//right lower leg
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-135, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left foot
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(-21, -24, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right foot
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(-10, -38, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right upper arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//right lower arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(27, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 21, 10);
	glPopMatrix();

	//right hand
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	glTranslated(42, 0, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 10, 10);
	glPopMatrix();

	// back hair
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2, 7, 0);
	drawCircle(510, 360, 13);
	glPopMatrix();

	// head
	glPushMatrix();
	glColor3f(1, 0.82, 0.73);
	drawCircle(510, 360, 13);
	glPopMatrix();

	// eye
	glPushMatrix();
	glTranslated(3, 3, 0);
	glColor3f(1, 1, 1);
	drawCircle(510, 360, 3);
	glPopMatrix();

	// eye color
	glPushMatrix();
	glTranslated(4, 3, 0);
	glColor3f(0, 1, 0);
	drawCircle(510, 360, 2);
	glPopMatrix();

	//mouth
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(7, 0, 0);
	glTranslated(512, 350, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-512, -350, 0);
	drawTriangle(512, 350, 7);
	glPopMatrix();

	//front hair
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-1, -5, 0);
	glTranslated(498, 367, 0);
	glRotated(20, 0, 0, 1);
	glTranslated(-498, -367, 0);
	drawRect(498, 367, 25, 7);
	glPopMatrix();

	//cape
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-33, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 70, 21);
	glPopMatrix();

	//cape end
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-45, 12, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();

	//cape front
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(16, 29, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();
}

void drawEnemy2() {
	// yellow triangle
	glPushMatrix();
	glTranslated(137, -85, 0);
	glTranslated(300, 400, 0);
	glRotated(-90, 0, 0, 1);
	glTranslated(-300, -400, 0);
	glColor3f(1, 1, 0);
	drawTriangle(300, 400, 25);
	glPopMatrix();

	//left upper leg
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left lower leg
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-165, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left upper arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left lower arm
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslated(40, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//left hand
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(59, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(0, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 5, 10);
	glPopMatrix();

	//left upper finger
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(61, 40, 0);
	glTranslated(470, 305, 0);
	glRotated(-20, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 3, 10);
	glPopMatrix();

	//left lower finger
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(61, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 7, 3);
	glPopMatrix();

	// wooden stick
	glPushMatrix();
	glColor3f(0.55, 0.41, 0.29);
	drawRect(450, 300, 100, 5);
	glPopMatrix();

	// body
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(470, 305, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 55, 20);
	glPopMatrix();

	// right upper leg
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(-14, 14, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 50, 10);
	glPopMatrix();

	//right lower leg
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(14, -14, 0);
	glTranslated(470, 305, 0);
	glRotated(-135, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 30, 10);
	glPopMatrix();

	//left foot
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(-21, -24, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right foot
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(-10, -38, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 15, 7);
	glPopMatrix();

	//right upper arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(20, 30, 0);
	glTranslated(470, 305, 0);
	glRotated(-65, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 20, 10);
	glPopMatrix();

	//right lower arm
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(27, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 21, 10);
	glPopMatrix();

	//right hand
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	glTranslated(42, 0, 0);
	glTranslated(470, 305, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 10, 10);
	glPopMatrix();

	// back hair
	//glPushMatrix();
	//glColor3f(0.1, 0.1, 0.1);
	//glTranslated(-2, 7, 0);
	//drawCircle(510, 360, 13);
	//glPopMatrix();

	// head
	glPushMatrix();
	glColor3f(0.47, 0.36, 0.31);
	drawCircle(510, 360, 13);
	glPopMatrix();

	// eye
	glPushMatrix();
	glTranslated(3, 3, 0);
	glColor3f(1, 1, 1);
	drawCircle(510, 360, 3);
	glPopMatrix();

	// eye color
	glPushMatrix();
	glTranslated(4, 3, 0);
	glColor3f(0, 0, 0);
	drawCircle(510, 360, 2);
	glPopMatrix();

	//mouth
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(7, 0, 0);
	glTranslated(512, 350, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-512, -350, 0);
	drawTriangle(512, 350, 7);
	glPopMatrix();

	//front hair
	//glPushMatrix();
	//glColor3f(0.1, 0.1, 0.1);
	//glTranslated(-1, -5, 0);
	//glTranslated(498, 367, 0);
	//glRotated(20, 0, 0, 1);
	//glTranslated(-498, -367, 0);
	//drawRect(498, 367, 25, 7);
	//glPopMatrix();

	//cape
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(-33, 15, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawRect(470, 305, 70, 21);
	glPopMatrix();

	//cape end
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(-45, 12, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();

	//cape front
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(16, 29, 0);
	glTranslated(470, 305, 0);
	glRotated(15, 0, 0, 1);
	glTranslated(-470, -305, 0);
	drawTriangle(470, 305, 24);
	glPopMatrix();
}

void drawSnitch() {
	//draw left wing
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(-25, -5, 0);
	glTranslated(100, 100, 0);
	glRotated(20, 0, 0, 1);
	glTranslated(-100, -100, 0);
	drawRect(100, 100, 25, 3);

	glPushMatrix();
	glTranslated(91, -55, 0);
	glRotated(45, 0, 0, 1);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glPopMatrix();
	glPopMatrix();

	//draw golden ball
	glPushMatrix();
	glColor3f(1,1,0);
	drawCircle(100, 100, 10);
	glPopMatrix();

	//draw right wing
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-20, -10, 0);
	glTranslated(100, 100, 0);
	glRotated(20, 0, 0, 1);
	glTranslated(-100, -100, 0);
	drawRect(100, 100, 25, 3);

	glPushMatrix();
	glTranslated(91, -55, 0);
	glRotated(45, 0, 0, 1);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glTranslated(5, -5, 0);
	drawRect(100, 100, 20, 5);
	glPopMatrix();
	glPopMatrix();
}

void drawPowerUp() { // x = 100 , y = 100
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawCircle(100, 100, 30);
	glColor3f(1, 0, 0);
	drawRect(74, 90, 40, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(25, 25.5, 0);
	glTranslated(80, 90, 0);
	glRotated(-90, 0, 0, 1);
	glTranslated(-80, -90, 0);
	drawTriangle(80,90,30);
	glPopMatrix();
}

void drawCloud() {
	glPushMatrix();
	glColor3f(1, 1, 1);

	drawCircle(150, 120, 50);
	drawCircle(100, 100, 50);
	drawCircle(200, 100, 50);
	drawCircle(150, 80, 50);

	glPopMatrix();
}

void drawball() {
	//ball
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	drawCircle(100, 100, 25);
	glPopMatrix();
	//yellow square
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(100, 100, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(-100, -100, 0);
	drawRect(95, 95, 10, 10);
	glPopMatrix();
	//yellow triangle
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(0,-3,0);
	glTranslated(100, 100, 0);
	glRotated(60, 0, 0, 1);
	glTranslated(-100, -100, 0);
	drawTriangle(100, 100, 11);
	glPopMatrix();
}

void Key(unsigned char key, int x, int y) {
	
	if ((key == GLUT_KEY_UP|| key == 'w') && !(mainYtranslation >= 300)) {
		mainYtranslation += 20;
		RotatingUp = true;
	}
	else if ((key == GLUT_KEY_DOWN || key == 's') && !(mainYtranslation <= -300)) {
		mainYtranslation -= 20;
		RotatingDown = true;
	}
	if (key == GLUT_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y) {

	if (key == 'w' || key == 's' || key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) {
		RotatingDown = false;
		RotatingUp = false;
		RotatingToNormal = true;
	}
	glutPostRedisplay();
}

void Timer(int value) {

	//some variables
	int currentMainXposition = mainXposition + mainXtranslation;
	int currentMainYposition = mainYposition + mainYtranslation;
	int currentEnenmyXposition = enemyXposition + enemyXtranslation;
	int currentEnenmyYposition = enemyYposition + enemyYtranslation;
	int currentEnenmy2Xposition = enemy2Xposition + enemy2Xtranslation;
	int currentEnenmy2Yposition = enemy2Yposition + enemy2Ytranslation;
	int currentPowerUpXposition = powerUpXposition + powerUpXtranslation;
	int currentPowerUpYposition = powerUpYposition + powerUpYtranslation;
	int currentBallXposition = ballXposition + ballXtranslation;
	int currentBallYposition = ballYposition + ballYtranslation;
	int currentSnitchXposition = snitchXposition + snitchXtranslation;
	int currentSnitchYposition = snitchYposition + snitchYtranslation;
	// code
	firstBackground--;
	if (firstBackground == -1000)
		firstBackground = 1000;

	secondBackground--;
	if (secondBackground == -2000)
		secondBackground = 0;

	cloud -= 2;
	if (cloud == -1200)
		cloud = 1000;

	cloud2 -= 2;
	if (cloud2 == -1500)
		cloud2 = 1000;

	if (RotatingUp) {
		RotationAngle++;
		if (RotationAngle >= 15)
			RotatingUp = false;
	}

	if (RotatingDown) {
		RotationAngle--;
		if (RotationAngle <= -15)
			RotatingDown = false;
	}

	if (RotatingToNormal) {
		if (RotationAngle > 0)
			RotationAngle--;
		if (RotationAngle < 0)
			RotationAngle++;
		if (RotationAngle == 0)
			RotatingToNormal = false;
	}

	if (spawnCounter == 0 || spawnCounter == 3 || spawnCounter == 5 || spawnCounter == 6) {
		if (tEnenmy < 1) {
			if (newStartingPointEnemy) {
				if (rand() % 2 == 0) {
					p0Enemy[1] = rand() % 201;
					p3Enemy[1] = rand() % 201;
				}
				else
				{
					p0Enemy[1] = -1 * (rand() % 201);
					p3Enemy[1] = -1 * (rand() % 201);
				}
			}
			newStartingPointEnemy = false;
			tEnenmy += 0.001;
			enemyXtranslation = bezierX(tEnenmy, p0Enemy, p1Enemy, p2Enemy, p3Enemy);
			enemyYtranslation = bezierY(tEnenmy, p0Enemy, p1Enemy, p2Enemy, p3Enemy);
		}
		else
		{
			randomize = true;
			tEnenmy = 0.0;
		}
	}

	if (spawnCounter == 1 || spawnCounter == 4 || spawnCounter == 3 || spawnCounter == 6) {
		if (tEnenmy2 < 1) {
			if (newStartingPointEnemy2) {
				if (rand() % 2 == 0) {
					p0Enemy2[1] = rand() % 201;
					p3Enemy2[1] = rand() % 201;
				}
				else
				{
					p0Enemy2[1] = -1 * (rand() % 201);
					p3Enemy2[1] = -1 * (rand() % 101);
				}
			}
			newStartingPointEnemy2 = false;
			tEnenmy2 += 0.001;
			enemy2Xtranslation = bezierX(tEnenmy2, p0Enemy2, p1Enemy2, p2Enemy2, p3Enemy2);
			enemy2Ytranslation = bezierY(tEnenmy2, p0Enemy2, p1Enemy2, p2Enemy2, p3Enemy2);
		}
		else
		{
			randomize = true;
			tEnenmy2 = 0.0;
		}
	}

	if(spawnPowerUp){

		if (tPowerUp < 1) {
			if (newStartingPointPowerUp) {
				if (rand() % 2 == 0) {
					p0PowerUp[1] = rand() % 201;
					p3PowerUp[1] = rand() % 201;
					}
				else
				{
					p0PowerUp[1] = -1 * (rand() % 201);
					p3PowerUp[1] = -1 * (rand() % 101);
				}
			}
			newStartingPointPowerUp = false;
			tPowerUp += 0.001;
			powerUpXtranslation = bezierX(tPowerUp, p0PowerUp, p1PowerUp, p2PowerUp, p3PowerUp);
			powerUpYtranslation = bezierY(tPowerUp, p0PowerUp, p1PowerUp, p2PowerUp, p3PowerUp);
		}
		else
		{
			spawnPowerUp = false;
			tPowerUp = 0.0;
		}
	}

	
	if (spawnCounter == 2 || spawnCounter == 5 || spawnCounter == 4 || spawnCounter == 6) {
		if (tBall < 1) {
			if (newStartingPointBall) {
				if (rand() % 2 == 0) {
					p0Ball[1] = rand() % 201;
					p3Ball[1] = rand() % 201;
				}
				else
				{
					p0Ball[1] = -1 * (rand() % 201);
					p3Ball[1] = -1 * (rand() % 101);
				}
			}
			newStartingPointBall = false;
			tBall += 0.001;
			BallRotation += 10;
			ballXtranslation = bezierX(tBall, p0Ball, p1Ball, p2Ball, p3Ball);
			ballYtranslation = bezierY(tBall, p0Ball, p1Ball, p2Ball, p3Ball);
		}
		else
		{
			randomize = true;
			tBall = 0.0;
		}
	}

	if (spawnCounter == 0 || spawnCounter == 3 || spawnCounter == 5 || spawnCounter == 6) {
		double distanceToEnemy = sqrt((pow(currentEnenmyXposition - currentMainXposition, 2.0)) + (pow(currentEnenmyYposition - currentMainYposition, 2.0)));
		if (distanceToEnemy < (mainHitboxRadius + enemyHitboxRadius)) {
			mainXtranslation -= 200;
		}
	}

	if (spawnPowerUp) {
		double distanceToPowerUp = sqrt((pow(currentPowerUpXposition - currentMainXposition, 2.0)) + (pow(currentPowerUpYposition - currentMainYposition, 2.0)));
		if (distanceToPowerUp < (mainHitboxRadius + powerUpHitbox)) {
			mainXtranslation += 200;
			spawnPowerUp = false;
			tPowerUp = 0.0;
			powerUpXposition = 100;
			powerUpXtranslation = 1000;
		}
	}

	if (spawnCounter == 2 || spawnCounter == 5 || spawnCounter == 4 || spawnCounter == 6) {
		double distanceToBall = sqrt((pow(currentBallXposition - currentMainXposition, 2.0)) + (pow(currentBallYposition - currentMainYposition, 2.0)));
		if (distanceToBall < (mainHitboxRadius + ballHitboxRadius)) {
			mainXtranslation -= 200;
		}
	}

	if (spawnCounter == 1 || spawnCounter == 4 || spawnCounter == 3 || spawnCounter == 6) {
		double distanceToEnemy2 = sqrt((pow(currentEnenmy2Xposition - currentMainXposition, 2.0)) + (pow(currentEnenmy2Yposition - currentMainYposition, 2.0)));
		if (distanceToEnemy2 < (mainHitboxRadius + enemy2HitboxRadius)) {
			mainXtranslation -= 200;
		}
	}

	double distanceToSnitch = sqrt((pow(currentSnitchXposition - currentMainXposition, 2.0)) + (pow(currentSnitchYposition - currentMainYposition, 2.0)));
	if (distanceToSnitch < (mainHitboxRadius + snitchHitboxRadius)) {
		Victory = true;
	}

	if (currentMainXposition < 0)
		Defeat = true;

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 1 millisecond 
	glutTimerFunc(1 * 1, Timer, 0);
}

void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	srand(time(NULL));
	if (randomize) {
		newStartingPointBall = true;
		newStartingPointEnemy = true;
		newStartingPointEnemy2 = true;
		newStartingPointPowerUp = true;

		spawnCounter = rand() % 7;

		randomize = false;

		if (spawnCounter < 3) {
			powerUpCounter += 1;
		} 
		else if (spawnCounter < 6 && spawnCounter >= 3) {
			powerUpCounter += 2;
		} 
		else {
			powerUpCounter += 3;
		}
		if (powerUpCounter >= 6) {
			spawnPowerUp = true;
			powerUpCounter = 0;
		}
	}

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(0+firstBackground, 0, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(1000+firstBackground, 0, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(1000+firstBackground, 600, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(0+firstBackground, 600, 0);
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, texID2);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(1000+secondBackground, 0, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(2000+secondBackground, 0, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(2000+secondBackground, 600, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(1000+secondBackground, 600, 0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	////////////////////drawing the objects////////////////////

	glPushMatrix();
	glTranslated(mainXtranslation, mainYtranslation, 0);
	glColor4f(0, 0, 1, 0);
	glTranslated(mainXposition, mainYposition, 0);
	glRotated(RotationAngle, 0, 0, 1);
	glTranslated(-mainXposition, -mainYposition, 0);
	drawCircle(mainXposition, mainYposition, mainHitboxRadius);
	drawMainCharacter();
	glPopMatrix();

	if (spawnPowerUp) {
		randomize = false;
		glPushMatrix();
		glTranslated(powerUpXtranslation, powerUpYtranslation, 0);
		drawPowerUp();
		glColor4f(0, 0, 0, 0);
		drawCircle(powerUpXposition, powerUpYposition, powerUpHitbox);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslated(cloud,300,0);
	drawCloud();
	glPopMatrix();

	glPushMatrix();
	glTranslated(cloud2, 150, 0);
	drawCloud();
	glPopMatrix();

	glPushMatrix();
	glTranslated(snitchXtranslation, snitchYtranslation, 0);
	drawSnitch();
	glColor4f(0, 0, 0, 0);
	drawCircle(snitchXposition, snitchYposition, snitchHitboxRadius);
	glPopMatrix();

	if (spawnCounter == 0 || spawnCounter == 3 || spawnCounter == 5 || spawnCounter == 6) {
		randomize = false;
		glPushMatrix();
		glTranslated(enemyXtranslation, enemyYtranslation, 0);
		drawEnemy();
		glColor4f(0, 0, 0, 0);
		drawCircle(enemyXposition, enemyYposition, enemyHitboxRadius);
		glPopMatrix();
	}

	if (spawnCounter == 2 || spawnCounter == 5 || spawnCounter == 4 || spawnCounter == 6) {
		randomize = false;
		glPushMatrix();
		glTranslated(ballXtranslation, ballYtranslation, 0);
		glTranslated(ballXposition, ballYposition, 0);
		glRotated(BallRotation, 0, 0, 1);
		glTranslated(-ballXposition, -ballYposition, 0);
		drawball();
		glColor4f(0, 0, 0, 0);
		drawCircle(ballXposition, ballYposition, ballHitboxRadius);
		glPopMatrix();
	}

	if (spawnCounter == 1 || spawnCounter == 4 || spawnCounter == 3 || spawnCounter == 6) {
		randomize = false;
		glPushMatrix();
		glTranslated(enemy2Xtranslation, enemy2Ytranslation, 0);
		drawEnemy2();
		glColor4f(0, 0, 0, 0);
		drawCircle(enemy2Xposition, enemy2Yposition, enemy2HitboxRadius);
		glPopMatrix();
	}

	if (Victory) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		print(200, 300, "CONGRATULATIONS , YOU'VE GOT THE SNITCH :D");
	}

	if (Defeat) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		print(300, 300, "YOU LOSE , PRESS ESC TO EXIT :(");
	}

	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);


	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);

	// enemy path 
	p0Enemy[0] = 700;
	p0Enemy[1] = -200;

	p1Enemy[0] = 300;
	p1Enemy[1] = 300;

	p2Enemy[0] = 100;
	p2Enemy[1] = -300;

	p3Enemy[0] = -500;
	p3Enemy[1] = 300;


	// enemy2 path 
	p0Enemy2[0] = 700;
	p0Enemy2[1] = 200;

	p1Enemy2[0] = 100;
	p1Enemy2[1] = -500;

	p2Enemy2[0] = 300;
	p2Enemy2[1] = 300;

	p3Enemy2[0] = -500;
	p3Enemy2[1] = -200;

	//ball path
	p0Ball[0] = 1000;
	p0Ball[1] = 100;

	p1Ball[0] = 0;
	p1Ball[1] = 600;

	p2Ball[0] = 800;
	p2Ball[1] = 600;

	p3Ball[0] = -200;
	p3Ball[1] = 100;

	//power up path
	p0PowerUp[0] = 1000;
	p0PowerUp[1] = 100;

	p1PowerUp[0] = 800;
	p1PowerUp[1] = 600;

	p2PowerUp[0] = 500;
	p2PowerUp[1] = 300;

	p3PowerUp[0] = -200;
	p3PowerUp[1] = 100;

	glutCreateWindow("Harry Potter");
	glutDisplayFunc(Display);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
	glutKeyboardUpFunc(KeyUp);  // sets the KeyboardUp handler function; called when a key is released
	glutTimerFunc(0, Timer, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	gluOrtho2D(0,1000,0,600);

	loadBMP(&texID, "textures/background1.bmp", true);
	loadBMP(&texID2, "textures/background2.bmp", true);

	glutMainLoop();
}