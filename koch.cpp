#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int iterations;

void koch(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, int iter) {
    if (iter == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    GLfloat dx = (x2 - x1) / 3;
    GLfloat dy = (y2 - y1) / 3;

    GLfloat x3 = x1 + dx;
    GLfloat y3 = y1 + dy;

    GLfloat x5 = x2 - dx;
    GLfloat y5 = y2 - dy;

    // Coordinates for the peak of the triangle
    GLfloat x4 = 0.5 * (x1 + x2) - sqrt(3.0) * (y1 - y2) / 6;
    GLfloat y4 = 0.5 * (y1 + y2) - sqrt(3.0) * (x2 - x1) / 6;

    koch(x1, y1, x3, y3, iter - 1);
    koch(x3, y3, x4, y4, iter - 1);
    koch(x4, y4, x5, y5, iter - 1);
    koch(x5, y5, x2, y2, iter - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    // Equilateral triangle points
    GLfloat x1 = -0.5f, y1 = -0.3f;
    GLfloat x2 = 0.5f, y2 = -0.3f;
    GLfloat x3 = 0.0f, y3 = 0.5f;

    koch(x1, y1, x2, y2, iterations);
    koch(x2, y2, x3, y3, iterations);
    koch(x3, y3, x1, y1, iterations);

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter number of iterations: ";
    cin >> iterations;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Snowflake");

    glClearColor(1.0, 1.0, 1.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
