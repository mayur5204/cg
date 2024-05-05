#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <unistd.h>

using namespace std;

float angle = 45.0; 
float velocity = 50.0; 
float gravity = 9.81; 
float timeStep = 0.05; 
float elapsedTime = 0.0; 
float posX = -100.0, posY = 0.0; 

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -10.0, 100.0);
}

void drawBall() {
    
    glPointSize(10.0); 

    
    glColor3f(1.0, 0.0, 0.0); 

   
    glBegin(GL_POINTS);
    glVertex2f(posX, posY);
    glEnd();
}

void update(int value) {
    
    float radians = angle * M_PI / 180.0;
    float velX = velocity * cos(radians);
    float velY = velocity * sin(radians) - gravity * elapsedTime;
    posX += velX * timeStep;
    posY += velY * timeStep;
    elapsedTime += timeStep;

    glutPostRedisplay();
    glutTimerFunc(10, update, 0); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Projectile Motion");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
