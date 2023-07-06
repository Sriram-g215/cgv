#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int xx, yy, xend, yend;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}
void Bresenhamline()
{
    int p, x, y;
    if (xx > xend)
    {
        x = xend;
        y = yend;
        xend = xx;
        yend = yy;
    }
    else {
        x = xx;
        y = yy;
    }
    int dx = abs(xend - x), dy = abs(yend - y);
    int twody = 2 * dy, twodyMinustwodx = 2 * (dy - dx);
    int twodx = 2 * dx, twodxMinustwody = 2 * (dx - dy);
    glColor3f(1, 0, 0); 
    glPointSize(2); 
    if (dx > dy)
    {
        
        p = 2 * dy - dx;
        setPixel(x, y);
        while (x < xend)
        {
            x = x + 1;
            if (p < 0)
                p = p + twody;
            else
            {
                y = y + 1;
                p = p + twodyMinustwodx;
            }
            setPixel(x, y);
        }
    }
    else
    {
        //For slope m>1
        p = 2 * dx - dy;
        setPixel(x, y);
        while (y < yend)
        {
            y = y + 1;
            if (p < 0)
                p = p + twodx;
            else
            {
                x = x + 1;
                p = p + twodxMinustwody;
            }
            setPixel(x, y);
        }
    }
}
void display()
{
    glClearColor(1, 1, 1, 1); 
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(300, 300, 100, 100);
    Bresenhamline();
    glFlush(); 
}
int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100); 
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham's Line Drawing  Algorthm");
     myinit();
    
    printf("Enter co-ordinates of first point: ");
    xx = 20; yy = 30;
    printf("Enter co-ordinates of second point: ");
    xend = 80; yend = 90;
    glutDisplayFunc(display);
    glutMainLoop();
   
}
