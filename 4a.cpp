#include <iostream>
#include <GL/glut.h>

using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void setPixel(int x, int y, float color[]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(int x, int y, float fillColor[]) {
    float interiorColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);
    if (interiorColor[0] == 1.0 && interiorColor[1] == 1.0 && interiorColor[2] == 1.0) {
        setPixel(x, y, fillColor);
        floodFill(x + 1, y, fillColor);
        floodFill(x - 1, y, fillColor);
        floodFill(x, y + 1, fillColor);
        floodFill(x, y - 1, fillColor);
    }
}

void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0);  // Red border color
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 480 - y;
        float fillColor[] = {0.0, 0.0, 1.0};  // Blue fill color
        floodFill(x, y, fillColor);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
