#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int wl = 1400;
int wh = 1000;

bool showCircle = false;
bool showOlympicRing = false;
bool showConcentricCircles = false;
bool showSpiral = false;

// Function to plot a point in all 8 octants of the circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

// Bresenham Circle Algorithm
void bresenhamCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    glBegin(GL_POINTS);

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            p = p + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    glEnd();
    glFlush();
}

// Function to draw Olympic Rings at a specified position
void drawOlympicRing(int xc, int yc) {
    int r = 50;
    int spacing = 120; // Adjusted spacing for quadrant fit

    bresenhamCircle(xc - spacing, yc, r);      
    bresenhamCircle(xc, yc, r);                
    bresenhamCircle(xc + spacing, yc, r);      
    bresenhamCircle(xc - spacing / 2, yc - 70, r);
    bresenhamCircle(xc + spacing / 2, yc - 70, r);
}

// Function to draw Concentric Circles at a specified position
void drawConcentricCircles(int xc, int yc) {
    for (int r = 50; r <= 150; r += 50) {
        bresenhamCircle(xc, yc, r);
    }
}

// Function to draw a continuous Spiral at a specified position
void drawSpiral(int xc, int yc) {
    double angle = 0.0;
    double radius = 1.0;

    glBegin(GL_LINE_STRIP);

    while (radius < 150) { // Limited size to fit quadrant
        int x = xc + radius * cos(angle);
        int y = yc + radius * sin(angle);
        glVertex2i(x, y);
       
        angle += 0.1;
        radius += 0.5;
    }

    glEnd();
    glFlush();
}

// Function to display the content
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    glBegin(GL_LINES);
    glVertex2i(-wl, 0); glVertex2i(wl, 0); // X-axis
    glVertex2i(0, -wh); glVertex2i(0, wh); // Y-axis
    glEnd();

    // Draw small center marker
    bresenhamCircle(0, 0, 5);

    // Draw each shape in its respective quadrant
    if (showCircle) {
        bresenhamCircle(wl / 2, wh / 2, 100); // Q1: Top-right
    }
    if (showOlympicRing) {
        drawOlympicRing(-wl / 2, wh / 2); // Q2: Top-left
    }
    if (showConcentricCircles) {
        drawConcentricCircles(-wl / 2, -wh / 2); // Q3: Bottom-left
    }
    if (showSpiral) {
        drawSpiral(wl / 2, -wh / 2); // Q4: Bottom-right
    }

    glFlush();
}

// Menu handling functions
void menu(int option) {
    switch (option) {
        case 1:
            showCircle = !showCircle;
            break;
        case 2:
            showOlympicRing = !showOlympicRing;
            break;
        case 3:
            showConcentricCircles = !showConcentricCircles;
            break;
        case 4:
            showSpiral = !showSpiral;
            break;
        case 5:
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Create menu for drawing options
void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry(" Simple Circle", 1);
    glutAddMenuEntry(" Olympic Rings", 2);
    glutAddMenuEntry(" Concentric Circles", 3);
    glutAddMenuEntry(" Spiral", 4);
    glutAddMenuEntry(" Exit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right-click
}

void myInit(void) {
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Bresenham Circle Algorithm - Quadrants");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    myInit();
    createMenu();

    glutMainLoop();
    return 0;
}