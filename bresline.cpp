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

void myInit(void) {
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

// Corrected Bresenham's Line Algorithm
void bresenham(int x1, int y1, int x2, int y2, int LineType) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int e = 2 * dy - dx;
    int interchange;

    // If the line has a steep slope, swap the roles of x and y
    if (dy > dx) {
        // Swap dx and dy
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    } else {
        interchange = 0;
    }

    glBegin(GL_POINTS);

    // Plot the first point
    glVertex2i(x1, y1);

    // Main loop to plot points
    for (int i = 1; i <= dx; i++) {
        // Plot the current point
        if (LineType == 1) {
            glVertex2i(x1, y1);
        } else if (LineType == 2) {
            if (i % 20 == 0) {  // Plot every 20th point for dotted line
                glVertex2i(x1, y1);
            }
        } else if (LineType == 3) {
            if (i % 40 < 20) {  // Plot first 20 points of every 40 for dashed line
                glVertex2i(x1, y1);
            }
        }

        // If error term is larger than or equal to 0, adjust
        while (e >= 0) {
            if (interchange == 1) {
                x1 += sx;  // Move in the x direction
            } else {
                y1 += sy;  // Move in the y direction
            }
            e -= 2 * dx;  // Adjust the error term
        }

        // Move to the next point
        if (interchange == 1) {
            y1 += sy;  // Move in the y direction
        } else {
            x1 += sx;  // Move in the x direction
        }

        // Adjust the error term based on the slope
        e += 2 * dy;
    }

    glEnd();
    glFlush();
}

// Function to draw the pattern
void drawPattern() {
 
    //outer rectangle
    bresenham(100, -100, 600, -100, 1);
    bresenham(600, -100, 600, -400, 1);
    bresenham(600, -400, 100, -400, 1);
    bresenham(100, -400, 100, -100, 1);
   
    //diamond
    bresenham(350, -100, 600, -250, 1);
    bresenham(600, -250, 350, -400, 1);
    bresenham(350, -400, 100, -250, 1);
    bresenham(100, -250, 350, -100, 1);
   
    //inner rectangle
    bresenham(225, -175, 475, -175, 1);
    bresenham(475, -175, 475, -325, 1);
    bresenham(475, -325, 225, -325, 1);
    bresenham(225, -325, 225, -175, 1);
   
 
   
}

// Function to display the content
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // axis plotting
    bresenham(-wl, 0, wl, 0, 1);
    bresenham(0, -wh, 0, wh, 1);

    // Conditionally draw the elements based on menu flags
    if (showLine) {
        bresenham(50, 50, 500, 450, 1); // simple line
    }
    if (showDottedLine) {
        bresenham(-50, 50, -500, 450, 2); // dotted line
    }
    if (showDashedLine) {
        bresenham(-50, -50, -500, -450, 3); // dashed line
    }
    if (showPattern) {
        drawPattern(); // draw pattern by default or when selected
    }
}

// Menu handling functions
void menu(int option) {
    switch (option) {
        case 1:
            showLine = !showLine; // simple line
            break;
        case 2:
            showDottedLine = !showDottedLine; // dotted line
            break;
        case 3:
            showDashedLine = !showDashedLine; // center line
            break;
        case 4:
            showPattern = !showPattern; // pattern drawing
            break;
        case 5:
            exit(0); // Exit the program
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redraw the window after menu option
}

// Create menu for drawing options
void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry(" Simple Line", 1);
    glutAddMenuEntry(" Dotted Line", 2);
    glutAddMenuEntry(" Dashed Line", 3);
    glutAddMenuEntry(" Pattern", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_LEFT_BUTTON); // Attach to left-click button
}

int main(int c, char **v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Bresenham: LINE DRAWING ALGORITHM");
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);  // Black color for the line

    glutDisplayFunc(display);
    myInit();
    createMenu(); // Create menu

    glutMainLoop();
    return 0;
}