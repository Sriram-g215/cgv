//3D-Seirpinski gasket (tetrahedron)
#include <iostream>
#include <GL/glut.h>

void draw_triangle(float* a, float* b, float* c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void draw_tetra(float* a, float* b, float* c, float* d)
{
    //Background triangle
    glColor3f(1, 0, 0);
    draw_triangle(a, b, c);

    //2 triangle
    glColor3f(0, 1, 0);
    draw_triangle(a, b, d);

    //3rd triangle x
    glColor3f(0, 0, 1);
    draw_triangle(d, b, c);


    //4th triangle
    glColor3f(1, 0, 0);
    draw_triangle(a, d, c);

}

void divide_tetrahedran(float* a, float* b, float* c, float* d, int m)
{
    //6 midpoint array to include 3 dimensions(x,y,z)
    float ab[3], ac[3], ad[3], bc[3], bd[3], cd[3];
    int j;
    if (m > 0) //No of divisions >0
    {
        for (j = 0;j < 3;j++)
        {
            //Calculate the midpoints-0,1,2 calculates x,y,z dimensions respectively
            ab[j] = (a[j] + b[j]) / 2;
            ac[j] = (a[j] + c[j]) / 2;
            ad[j] = (a[j] + d[j]) / 2;
            bc[j] = (b[j] + c[j]) / 2;
            bd[j] = (b[j] + d[j]) / 2;
            cd[j] = (c[j] + d[j]) / 2;
        }
        //Call the function recursively 4 times to divide the tetrahedran 
        divide_tetrahedran(a, ab, ac, ad, m - 1);
        divide_tetrahedran(ab, b, bc, bd, m - 1);
        divide_tetrahedran(ac, bc, c, cd, m - 1);
        divide_tetrahedran(ad, bd, cd, d, m - 1);
    }
    else
        draw_tetra(a, b, c, d);
}


void myinit()
{
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    float v[4][3] = { {-0.5,-0.25,0},
                       {0,0.75,0},
                       {0.5,-0.25,0},
                        {0,0,0.25} };
    int n = 2;
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    divide_tetrahedran(v[0], v[1], v[2], v[3], n);
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D-seirpinski-gasket");
    myinit();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glutMainLoop();
    return 0;

}
