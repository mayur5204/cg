#include <GL/glut.h>
#include <iostream>

using namespace std;

int wxmin = 200, wxmax = 500, wymax = 350, wymin = 100;
int points[10][2];
int edge = 0;

// Define region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute region code for a point (x, y)
int computeCode(int x, int y) {
    int code = INSIDE;

    if (x < wxmin)
        code |= LEFT;
    else if (x > wxmax)
        code |= RIGHT;
    if (y < wymin)
        code |= BOTTOM;
    else if (y > wymax)
        code |= TOP;

    return code;
}

// Clip a line segment from (x1, y1) to (x2, y2) against a rectangle with
// diagonal from (wxmin, wymin) to (wxmax, wymax)
void cohenSutherland(int x1, int y1, int x2, int y2) {
    // Compute region codes for P1 and P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both endpoints are inside
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside, and in the same region
            break;
        } else {
            // Some segment needs clipping
            int codeOut = code1 ? code1 : code2;

            int x, y;

            // Find intersection point
            if (codeOut & TOP) {
                // Point is above the clip rectangle
                x = x1 + (x2 - x1) * (wymax - y1) / (y2 - y1);
                y = wymax;
            } else if (codeOut & BOTTOM) {
                // Point is below the clip rectangle
                x = x1 + (x2 - x1) * (wymin - y1) / (y2 - y1);
                y = wymin;
            } else if (codeOut & RIGHT) {
                // Point is to the right of the clip rectangle
                y = y1 + (y2 - y1) * (wxmax - x1) / (x2 - x1);
                x = wxmax;
            } else if (codeOut & LEFT) {
                // Point is to the left of the clip rectangle
                y = y1 + (y2 - y1) * (wxmin - x1) / (x2 - x1);
                x = wxmin;
            }

            // Replace outside point with intersection point
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.2, 1);

    // Draw clipped parts of the polygon
    for (int i = 0; i < edge; i++) {
        int x1 = points[i][0];
        int y1 = points[i][1];
        int x2 = points[(i + 1) % edge][0];
        int y2 = points[(i + 1) % edge][1];
        cohenSutherland(x1, y1, x2, y2);
    }

    // Draw the remaining part of the polygon (inside the clipping window)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        int x = points[i][0];
        int y = points[i][1];

        if (x >= wxmin && x <= wxmax && y >= wymin && y <= wymax) {
            glVertex2i(x, y);
        }
    }
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(wxmin, wymin);
    glVertex2i(wxmax, wymin);
    glVertex2i(wxmax, wymax);
    glVertex2i(wxmin, wymax);
    glEnd();

    glFlush();
}

void P_C() {
    Draw();
}

int main(int argc, char** argv) {
    cout << "\nEnter No of edges of polygon: ";
    cin >> edge;

    for (int i = 0; i < edge; i++) {
        cout << "\nEnter point " << i << " x y: ";
        cin >> points[i][0] >> points[i][1];
    }

    points[edge][0] = points[0][0];
    points[edge][1] = points[0][1];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Cohen-Sutherland Polygon Clipping");
    init();

    glutDisplayFunc(P_C);
    glutMainLoop();
    return 0;
}
