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

void myInit(void) {
   
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

void ddaAlgorithm(int x1, int y1, int x2, int y2, int LineType) {
    int l;
    int dx = x2 - x1;
    int dy = y2 - y1;

    // to find out the length
    if (abs(dx) > abs(dy)) {
        l = abs(dx);
    } else {
        l = abs(dy);
    }

    float DX = dx / float(l);
    float DY = dy / float(l);

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= l; i++) {
        glColor3i(0, 0, 0);

        if (LineType == 1) {
            glVertex2i(round(x), round(y));
        }
        else if (LineType == 2) {
            if (i % 20 == 0) {
                glVertex2i(round(x), round(y));
            }
        }
        else if (LineType == 3) {
            if (i % 40 < 20) {
                glVertex2i(round(x), round(y));
            }
        }
        x = x + DX;
        y = y + DY;
    }

    glEnd();
    glFlush();
}

// Function to draw the boat
void drawBoat() {
   
    ddaAlgorithm(300, -350, 750, -350, 1); // horizontal big 2
    ddaAlgorithm(400, -500, 650, -500, 1); // horizontal short
   
 
   
    ddaAlgorithm(400, -500, 300, -350, 1); // left connecting sides
    ddaAlgorithm(650, -500, 750, -350, 1); // right connecting sides

 
    ddaAlgorithm(525, -50, 525, -350, 1); // right part of the stick
     // Flag
 
    ddaAlgorithm(525, -275, 625, -275, 1); // bottom to top line
    ddaAlgorithm(525, -50, 625, -275, 1); // top to bottom line
}

// Function to display the content
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // axis plotting
    ddaAlgorithm(-wl, 0, wl, 0, 1);
    ddaAlgorithm(0, -wh, 0, wh, 1);

    // Conditionally draw the elements based on menu flags
    if (showLine) {
        ddaAlgorithm(50, 50, 500, 450, 1); // simple line
    }
    if (showDottedLine) {
        ddaAlgorithm(-50,50,-500,450, 2); // dotted line
    }
    if (showDashedLine) {
        ddaAlgorithm(-50,-50,-500,-450, 3); // center line
    }
    if (showBoat) {
        drawBoat(); // draw boat by default or when selected
    }
}

// Menu handling functions
void menu(int option) {
    switch (option) {
        case 1:
            showLine = !showLine; // simple line
            break;
        case 2:
            showDottedLine = !showDottedLine; //  dotted line
            break;
        case 3:
            showDashedLine = !showDashedLine; //  center line
            break;
        case 4:
            showBoat = !showBoat; //  boat drawing
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
    glutAddMenuEntry(" Boat", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_LEFT_BUTTON); // Attach to left-click button
}

int main(int c, char **v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("DDA:LINE DRAWING ALGORITHM");
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);  // Black color for the line

    glutDisplayFunc(display);
    myInit();
    createMenu(); // Create menu

    glutMainLoop();
    return 0;
}