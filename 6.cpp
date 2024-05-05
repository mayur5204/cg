#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int ch = 0;
vector<int> arr;
int ct = 0;
float colorarr[] = {1.0, 0.0, 0.0};
float flc[] = {1.0, 0.0, 0.0};
float neg[] = {0.0, 1.0, 1.0};

void copyarr(float* arr1) {
    for (int i = 0; i < 3; i++) {
        flc[i] = arr1[i];
        if (arr1[i] == 0.0f) {
            neg[i] = 1.0f;
        }
        if (arr1[i] == 1.0f) {
            neg[i] = 0.0f;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float* flc) {
    glColor3f(flc[0], flc[1], flc[2]);
    glBegin(GL_LINE_LOOP);
    glLineWidth(3);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glEnd();
    glLineWidth(1);
    glFlush();
}

void TrnsScaling(vector<int> arr) {
    vector<int> sarr;
    int sz = arr.size();
    float Sx, Sy;
    cout << "Enter Sx scaling factor: ";
    cin >> Sx;
    cout << "Enter Sy scaling factor: ";
    cin >> Sy;
    for (int i = 0; i < sz; i++) {
        if (i % 2 == 0) {
            sarr.push_back(arr.at(i) * Sx);
        }
        if (i % 2 == 1) {
            sarr.push_back(arr.at(i) * Sy);
        }
    }
    drawTriangle(sarr.at(0), sarr.at(1), sarr.at(2), sarr.at(3), sarr.at(4), sarr.at(5), neg);
    sarr.clear();
}

void RotationAboutPt(vector<int> arr, int x, int y) {
    int xr = x;
    int yr = y;
    int angle;
    cout << "Enter angle in degrees to rotate: ";
    cin >> angle;
    float theta = angle * M_PI / 180;
    vector<int> sarr;
    int sz = arr.size();
    for (int i = 0; i < sz; i++) {
        if (i % 2 == 0) {
            int nx = xr + ((arr.at(i) - xr) * cos(theta)) - ((arr.at(i + 1) - yr) * sin(theta));
            sarr.push_back(nx);
        }
        if (i % 2 == 1) {
            int ny = yr + ((arr.at(i - 1) - xr) * sin(theta)) + ((arr.at(i) - yr) * cos(theta));
            sarr.push_back(ny);
        }
    }
    drawTriangle(sarr.at(0), sarr.at(1), sarr.at(2), sarr.at(3), sarr.at(4), sarr.at(5), neg);
    sarr.clear();
}

void Reflection(vector<int> arr) {
    vector<int> rarr;
    int sz = arr.size();
    for (int i = 0; i < sz; i++) {
        if (i % 2 == 0) {
            rarr.push_back(arr.at(i));
        }
        if (i % 2 == 1) {
            rarr.push_back(-1 * arr.at(i));
        }
    }
    drawTriangle(rarr.at(0), rarr.at(1), rarr.at(2), rarr.at(3), rarr.at(4), rarr.at(5), neg);
    rarr.clear();
}

void mouse(int button, int state, int x, int y) {
    static int xx, yy;
    xx = x - 300;
    yy = 300 - y;
    int sz = arr.size();
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (ch == 1) {
            if (sz < 6) {
                arr.push_back(xx);
                arr.push_back(yy);
            }
            sz = arr.size();
            if (sz == 6) {
                drawTriangle(arr.at(0), arr.at(1), arr.at(2), arr.at(3), arr.at(4), arr.at(5), flc);
            }
        }
        if (ch == 2) {
            RotationAboutPt(arr, xx, yy);
        }
        if (ch == 3) {
            Reflection(arr);
        }
        if (ch == 4) {
            TrnsScaling(arr);
        }
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't': {
            ch = 1;
            copyarr(colorarr);
            cout << "Triangle is opted" << endl;
            glutMouseFunc(mouse);
            break;
        }
        case 'R': {
            ch = 2;
            copyarr(colorarr);
            cout << "Rotation about any arbitrary point is opted" << endl;
            glutMouseFunc(mouse);
            cout << "Click on the arbitrary point" << endl;
            break;
        }
        case 'r': {
            ch = 3;
            copyarr(colorarr);
            cout << "Reflection is opted" << endl;
            glutMouseFunc(mouse);
            break;
        }
        case 's': {
            ch = 4;
            copyarr(colorarr);
            cout << "Scaling Transformation is opted" << endl;
            glutMouseFunc(mouse);
            break;
        }
    }
    glutPostRedisplay();
}

void initialize() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-300, 300, -300, 300);
}

void initialaxis() {
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(-300, 0);
    glVertex2i(300, 0);
    glVertex2i(0, -300);
    glVertex2i(0, 300);
    glEnd();
    glFlush();
    glutKeyboardFunc(keyboard);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Geometric Transformations");
    initialize();
    cout << "Choose your transformation type: " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "t => Triangle" << endl;
    cout << "R => Rotation about point" << endl;
    cout << "r => Reflection" << endl;
    cout << "s => Scaling" << endl;
    cout << "--------------------------------------------" << endl;
    glutDisplayFunc(initialaxis);
    glutMainLoop();
    return 0;
}
