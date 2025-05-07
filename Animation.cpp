#include <GL/glut.h>
#include <math.h>

float flagY = -200.0; // Initial position of the flag

void init()
{
    glClearColor(0.6, 0.8, 1.0, 1.0); // Blue background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void drawPole()
{
    glColor3f(0.5, 0.35, 0.05); // Brown color for pole
    glBegin(GL_QUADS);
    glVertex2f(240.0, 50.0);
    glVertex2f(260.0, 50.0);
    glVertex2f(260.0, 370.0);
    glVertex2f(240.0, 370.0);
    glEnd();
}

void drawFlag()
{
    glColor3f(0.0, 1.0, 0.0); // Green stripe
    glBegin(GL_QUADS);
    glVertex2f(260.0, flagY);
    glVertex2f(360.0, flagY);
    glVertex2f(360.0, flagY + 20.0);
    glVertex2f(260.0, flagY + 20.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // White stripe
    glBegin(GL_QUADS);
    glVertex2f(260.0, flagY + 20.0);
    glVertex2f(360.0, flagY + 20.0);
    glVertex2f(360.0, flagY + 40.0);
    glVertex2f(260.0, flagY + 40.0);
    glEnd();

    glColor3f(1.0, 0.5, 0.0); // Orange stripe
    glBegin(GL_QUADS);
    glVertex2f(260.0, flagY + 40.0);
    glVertex2f(360.0, flagY + 40.0);
    glVertex2f(360.0, flagY + 60.0);
    glVertex2f(260.0, flagY + 60.0);
    glEnd();

    // Draw Ashoka Chakra
    glColor3f(0.0, 0.0, 1.0);
    float cx = 310.0, cy = flagY + 30.0, r = 8.0;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159 / 180;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();

    // Draw spokes of Ashoka Chakra
    for (int i = 0; i < 24; i++)
    {
        float theta = i * 3.14159 / 12;
        glBegin(GL_LINES);
        glVertex2f(cx, cy);
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPole();
    drawFlag();
    glFlush();
}

void update(int value)
{
    if (flagY < 300.0) // Move the flag up to a certain height
    {
        flagY += 2.0;
        glutPostRedisplay();
        glutTimerFunc(30, update, 0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flag Hoisting Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);
    glutMainLoop();
    return 0;
}