#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

void drawKochCurve(float x1, float y1, float x2, float y2, int iterations) {
    if (iterations == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
        float deltaX = (x2 - x1) / 3;
        float deltaY = (y2 - y1) / 3;

        float xA = x1 + deltaX;
        float yA = y1 + deltaY;

        float xC = x2 - deltaX;
        float yC = y2 - deltaY;

        float xB = xA + (deltaX - deltaY * sqrt(3)) / 2;
        float yB = yA + (deltaX * sqrt(3) + deltaY) / 2;

        drawKochCurve(x1, y1, xA, yA, iterations - 1);
        drawKochCurve(xA, yA, xB, yB, iterations - 1);
        drawKochCurve(xB, yB, xC, yC, iterations - 1);
        drawKochCurve(xC, yC, x2, y2, iterations - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    float x1 = 100.0, y1 = 200.0;
    float x2 = 500.0, y2 = 200.0;

    int iterations = 4;

    drawKochCurve(x1, y1, x2, y2, iterations);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve Fractal");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
