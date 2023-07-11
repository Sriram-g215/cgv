#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void display()
{
    float pos[] = { 0,1,0,1 };
    float col[] = { 1,0,0,1 };
    float m[] = { 0,1,0,1 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, col);

    gluLookAt(0, 1, 3, 0, 0, 0, 0, 1, 0);
    //tabe top
    glPushMatrix();
    glScalef(1, 0.025, 1);
    glutSolidCube(1);
    glPopMatrix();
    // leg 1
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    // leg2
    glPushMatrix();
    glTranslatef(0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    // leg3
    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    // leg4
    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    //tea pot
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m);
    glPushMatrix();
    glTranslatef(0, 0.25, 0);
    glutSolidTeapot(0.25);
    glPopMatrix();
    glPopAttrib();
    glutSwapBuffers();
    glFlush();
   


}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("tea pot");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}
