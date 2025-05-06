#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
int points[4][2];
int clicks = 0;
bool curveDrawn = false;
void drawPoint(GLfloat x, GLfloat y)
{
    glColor3f(0.0,1.0,0.0);
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    glVertex2f((GLfloat)x,(GLfloat)y);
    glEnd();
    glFlush();
}
void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    glFlush();
}
void midPointSubDivision(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    GLfloat xAB = (x2 + x1)/2;
    GLfloat yAB = (y2 + y1)/2;
    GLfloat xBC = (x3 + x2)/2;
    GLfloat yBC = (y3 + y2)/2;
    GLfloat xCD = (x4 + x3)/2;
    GLfloat yCD = (y4 + y3)/2;
    GLfloat xABC = (xAB + xBC)/2;
    GLfloat yABC = (yAB + yBC)/2;
    GLfloat xBCD = (xBC + xCD)/2;
    GLfloat yBCD = (yBC + yCD)/2;
    GLfloat xABCD = (xABC + xBCD)/2;
    GLfloat yABCD = (yABC + yBCD)/2;

    if(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) > 4 ||
       ((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2)) > 4 ||
       ((x4 - x3)*(x4 - x3) + (y4 - y3)*(y4 - y3)) > 4)
    {
        midPointSubDivision(x1,y1,xAB,yAB,xABC,yABC,xABCD,yABCD);
        midPointSubDivision(xABCD,yABCD,xBCD,yBCD,xCD,yCD,x4,y4);
    }
    else
    {
        drawLine(x1,y1,xABCD,yABCD);
        drawLine(xABCD,yABCD,x4,y4);
    }
}
void init()
{
 glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,0,600);
}
void display()
{
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.0,1.0,0.0);
     if(curveDrawn)
     {
         for(int i = 0; i < 4; ++i)
         {
             drawPoint(points[i][0],points[i][1]);
         }
     }
     glFlush();
}
void mouse(int btn, int state, int x, int y)
{
        if(state == GLUT_DOWN && btn == GLUT_LEFT_BUTTON)
        {
            points[clicks][0] = (GLfloat)x;
            points[clicks][1] = (GLfloat)(600 - y);
            clicks++;

            drawPoint((GLfloat)x,(GLfloat)(600-y));
            if(clicks == 4)
            {
                drawLine(points[0][0],points[0][1],points[1][0],points[1][1]);
                drawLine(points[1][0],points[1][1],points[2][0],points[2][1]);
                drawLine(points[2][0],points[2][1],points[3][0],points[3][1]);

                midPointSubDivision(points[0][0],points[0][1],points[1][0],points[1][1],points[2][0],points[2][1],points[3][0],points[3][1]);
            }
        }
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("BEZIER");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}