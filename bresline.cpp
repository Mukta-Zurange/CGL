#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int wl = 1400;
int wh = 1000;

// Flags for menu options
bool showLine = false;
bool showDottedLine = false;
bool showDashedLine = false;
bool showPattern = false;
bool showSquareWave = false;
bool showTriangularWave = false;

void myInit(void) {
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

// Bresenham's Line Drawing Algorithm
void bresenham(int x1, int y1, int x2, int y2, int LineType) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int interchange;
    int e = 2 * dy - dx;

    if (dy > dx) {
        swap(dx, dy);
        interchange = 1;
    } else {
        interchange = 0;
    }

    glBegin(GL_POINTS);
    glVertex2i(x1, y1);

    for (int i = 1; i <= dx; i++) {
        if (LineType == 1) {
            glVertex2i(x1, y1);
        } else if (LineType == 2) {
            if (i % 20 == 0) glVertex2i(x1, y1);
        } else if (LineType == 3) {
            if (i % 40 < 20) glVertex2i(x1, y1);
        }

        while (e >= 0) {
            if (interchange)
                x1 += sx;
            else
                y1 += sy;
            e -= 2 * dx;
        }

        if (interchange)
            y1 += sy;
        else
            x1 += sx;

        e += 2 * dy;
    }

    glEnd();
    glFlush();
}

// Draw a geometric pattern (diamond inside a rectangle)
void drawPattern() {
    // Outer rectangle
    bresenham(100, -100, 600, -100, 1);
    bresenham(600, -100, 600, -400, 1);
    bresenham(600, -400, 100, -400, 1);
    bresenham(100, -400, 100, -100, 1);

    // Diamond
    bresenham(350, -100, 600, -250, 1);
    bresenham(600, -250, 350, -400, 1);
    bresenham(350, -400, 100, -250, 1);
    bresenham(100, -250, 350, -100, 1);

    // Inner rectangle
    bresenham(225, -175, 475, -175, 1);
    bresenham(475, -175, 475, -325, 1);
    bresenham(475, -325, 225, -325, 1);
    bresenham(225, -325, 225, -175, 1);
}

// Square wave using Bresenham's algorithm
void drawSquareWaveBresenham() {
    int startX = -600;
    int startY = 400;
    int amplitude = 100;
    int wavelength = 100;
    int cycles = 8;

    for (int i = 0; i < cycles; i++) {
        int x1 = startX + i * wavelength;
        int x2 = x1 + wavelength / 2;
        int x3 = x1 + wavelength;

        bresenham(x1, startY, x1, startY + amplitude, 1);         // Rising edge
        bresenham(x1, startY + amplitude, x2, startY + amplitude, 1); // Top
        bresenham(x2, startY + amplitude, x2, startY, 1);         // Falling edge
        bresenham(x2, startY, x3, startY, 1);                     // Bottom
    }
}

// Triangular wave using Bresenham's algorithm
void drawTriangularWaveBresenham() {
    int startX = -600;
    int startY = 200;
    int amplitude = 100;
    int wavelength = 100;
    int cycles = 8;

    for (int i = 0; i < cycles; i++) {
        int x1 = startX + i * wavelength;
        int x2 = x1 + wavelength / 2;
        int x3 = x1 + wavelength;

        bresenham(x1, startY, x2, startY + amplitude, 1); // Upward slope
        bresenham(x2, startY + amplitude, x3, startY, 1); // Downward slope
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Axes
    bresenham(-wl, 0, wl, 0, 1);
    bresenham(0, -wh, 0, wh, 1);

    // Conditional draws
    if (showLine) bresenham(50, 50, 500, 450, 1);
    if (showDottedLine) bresenham(-50, 50, -500, 450, 2);
    if (showDashedLine) bresenham(-50, -50, -500, -450, 3);
    if (showPattern) drawPattern();
    if (showSquareWave) drawSquareWaveBresenham();
    if (showTriangularWave) drawTriangularWaveBresenham();
}

// Menu handler
void menu(int option) {
    switch (option) {
        case 1: showLine = !showLine; break;
        case 2: showDottedLine = !showDottedLine; break;
        case 3: showDashedLine = !showDashedLine; break;
        case 4: showPattern = !showPattern; break;
        case 5: showSquareWave = !showSquareWave; break;
        case 6: showTriangularWave = !showTriangularWave; break;
        case 7: exit(0); break;
    }
    glutPostRedisplay();
}

// Menu setup
void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry(" Simple Line", 1);
    glutAddMenuEntry(" Dotted Line", 2);
    glutAddMenuEntry(" Dashed Line", 3);
    glutAddMenuEntry(" Pattern", 4);
    glutAddMenuEntry(" Square Wave", 5);
    glutAddMenuEntry(" Triangular Wave", 6);
    glutAddMenuEntry(" Exit", 7);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Bresenham Line & Wave Patterns");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    myInit();
    createMenu();
    glutMainLoop();
    return 0;
}
