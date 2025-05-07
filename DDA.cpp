#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1400;
int wh = 1000;

// Flags for menu options
bool showLine = false;
bool showDottedLine = false;
bool showDashedLine = false;
bool showBoat = false;
bool showSquareWave = false;
bool showTriangularWave = false;

void myInit(void) {
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

void ddaAlgorithm(int x1, int y1, int x2, int y2, int LineType) {
    int l;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy))
        l = abs(dx);
    else
        l = abs(dy);

    float DX = dx / float(l);
    float DY = dy / float(l);
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= l; i++) {
        glColor3i(0, 0, 0);

        if (LineType == 1) {
            glVertex2i(round(x), round(y));
        } else if (LineType == 2) {
            if (i % 20 == 0) glVertex2i(round(x), round(y));
        } else if (LineType == 3) {
            if (i % 40 < 20) glVertex2i(round(x), round(y));
        }

        x = x + DX;
        y = y + DY;
    }
    glEnd();
    glFlush();
}

void drawBoat() {
    ddaAlgorithm(300, -350, 750, -350, 1);
    ddaAlgorithm(400, -500, 650, -500, 1);
    ddaAlgorithm(400, -500, 300, -350, 1);
    ddaAlgorithm(650, -500, 750, -350, 1);
    ddaAlgorithm(525, -50, 525, -350, 1);
    ddaAlgorithm(525, -275, 625, -275, 1);
    ddaAlgorithm(525, -50, 625, -275, 1);
}

// Draw square wave
void drawSquareWave() {
    int startX = -600;
    int startY = 400;
    int amplitude = 100;
    int wavelength = 100;
    int cycles = 8;

    for (int i = 0; i < cycles; i++) {
        int x1 = startX + i * wavelength;
        int x2 = x1 + wavelength / 2;
        int x3 = x1 + wavelength;

        // Rising edge
        ddaAlgorithm(x1, startY, x1, startY + amplitude, 1);
        // Top horizontal
        ddaAlgorithm(x1, startY + amplitude, x2, startY + amplitude, 1);
        // Falling edge
        ddaAlgorithm(x2, startY + amplitude, x2, startY, 1);
        // Bottom horizontal
        ddaAlgorithm(x2, startY, x3, startY, 1);
    }
}

// Draw triangular wave
void drawTriangularWave() {
    int startX = -600;
    int startY = 200;
    int amplitude = 100;
    int wavelength = 100;
    int cycles = 8;

    for (int i = 0; i < cycles; i++) {
        int x1 = startX + i * wavelength;
        int x2 = x1 + wavelength / 2;
        int x3 = x1 + wavelength;

        // Up slope
        ddaAlgorithm(x1, startY, x2, startY + amplitude, 1);
        // Down slope
        ddaAlgorithm(x2, startY + amplitude, x3, startY, 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // axis plotting
    ddaAlgorithm(-wl, 0, wl, 0, 1);
    ddaAlgorithm(0, -wh, 0, wh, 1);

    if (showLine) ddaAlgorithm(50, 50, 500, 450, 1);
    if (showDottedLine) ddaAlgorithm(-50, 50, -500, 450, 2);
    if (showDashedLine) ddaAlgorithm(-50, -50, -500, -450, 3);
    if (showBoat) drawBoat();
    if (showSquareWave) drawSquareWave();
    if (showTriangularWave) drawTriangularWave();
}

void menu(int option) {
    switch (option) {
        case 1: showLine = !showLine; break;
        case 2: showDottedLine = !showDottedLine; break;
        case 3: showDashedLine = !showDashedLine; break;
        case 4: showBoat = !showBoat; break;
        case 5: showSquareWave = !showSquareWave; break;
        case 6: showTriangularWave = !showTriangularWave; break;
        case 7: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 1);
    glutAddMenuEntry("Dotted Line", 2);
    glutAddMenuEntry("Dashed Line", 3);
    glutAddMenuEntry("Boat", 4);
    glutAddMenuEntry("Square Wave", 5);
    glutAddMenuEntry("Triangular Wave", 6);
    glutAddMenuEntry("Exit", 7);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

int main(int c, char **v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("DDA: LINE DRAWING ALGORITHM");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    myInit();
    createMenu();

    glutMainLoop();
    return 0;
}
