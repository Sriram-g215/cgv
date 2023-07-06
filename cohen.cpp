
#include<stdio.h>
#include<GL/glut.h>
#define opcode int 
enum { top = 0x8, bottom = 0x4, left = 0x1, right = 0x2 };
float xmin, xmax, ymin, ymax, umin, umax, vmin, vmax;
float x1, yone, x2, y2;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
opcode compopcode(float x, float y)
{
    int p = 0;
    if (x < xmin) p = p | left;
    if (x > xmax) p = p | right;
    if (y < ymin) p = p | bottom;
    if (y > ymax) p = p | top;
    return p;
}
void cohensutherland()
{
    bool accept = false, done = false;
    int x = 0, y = 0;
    opcode p1, p2, p;
    p1 = compopcode(x1, yone);
    p2 = compopcode(x2, y2); 
    float m = (y2 - yone) / (x2 - x1);
    do {
        if (!(p1 | p2))
        {
            accept = true;
            done = true;
        }
        else if (p1 & p2)
            done = true;
        else
        {
            p = p1 ? p1 : p2;
            if (p & bottom)
            {
                y = ymin;
                x = x1 + (ymin - yone) / m;
            }
            if (p & top)
            {
                y = ymax;
                x = x1 + (ymax - yone) / m;
            }
            if (p & right)
            {
                x = xmax;
                y = yone + (xmax - x1) * m;
            }
            if (p & left)
            {
                x = xmin;
                y = yone + (xmin - x1) * m;
            }
            if (p == p2)
            {
                x2 = x;
                y2 = y;
                p2 = compopcode(x2, y2);
            }
            if (p == p1)
            {
                x1 = x;
                yone = y;
                p1 = compopcode(x1, yone);
            }
        }
    } while (!done);
    if (accept)
    {
        float sx = (umax - umin) / (xmax - xmin);
        float sy = (vmax - vmin) / (ymax - ymin);
        x1 = sx * x1 + umin - sx * xmin;
        yone = sy * yone + vmin - sy * ymin;
        x2 = sx * x2 + umin - sx * xmin;
        y2 = sy * y2 + vmin - sy * ymin;
    }
    glBegin(GL_LINES);
    glVertex2f(x1, yone);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}
void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(x1, yone);
    glVertex2f(x2, y2);
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(umin, vmin);
    glVertex2f(umin, vmax);
    glVertex2f(umax, vmax);
    glVertex2f(umax, vmin);
    glEnd();
    cohensutherland();
    glFlush();
}
int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CLIPPING ALGORITHM");
    myinit();
    printf("Enter the clipping window points xmin, xmax, ymin, ymax");
    xmin = 200;
    xmax = 300;
    ymin = 200;
    ymax=300;
    printf("Enter the display window points umin, umax, vmin, vmax");
    umin = 350;
    umax = 400;
    vmin = 350;
    vmax = 400;;
    printf("\nEnter the first point x1,y1\n");
    x1 = 250;
    yone=250;
    printf("\nEnter the second point x2,y2\n");
    x2 = 100;
    y2=100;
    glutDisplayFunc(display);
    glutMainLoop();
}
