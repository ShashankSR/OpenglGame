#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/*
The spheres here are drawn using the correction
discussed in the doc before display funcion in main.cpp
Drawing 3d was done at last so collision and
points adding couldn't be implemented.
The spheres are supposed to be points

For example : required x coordinate = 350
then corrected = 350 - ( origin (which is at 150 ))
and final = corrected/150
*/

void drawSpheres(){
  glColor3f(0.9,0.7,0.0);
  glPushMatrix();

        glTranslatef(-50.0/150.0,0,-50);
        glutSolidSphere(.1,20,20);

  glPopMatrix();

    glPushMatrix();
        glTranslatef(200.0/150.0,100.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glPushMatrix();
        glTranslatef(300.0/150.0,0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

    glPushMatrix();
        glTranslatef(500.0/150.0,100.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glColor3f(0.9,0.0,0.0);
   glPushMatrix();
        glTranslatef(1100.0/150.0,25.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glColor3f(0.9,0.7,0.0);
  glPushMatrix();
        glTranslatef(1000.0/150.0,300.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glPushMatrix();
        glTranslatef(1100.0/150.0,300.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();


  glPushMatrix();
        glTranslatef(0.0/150.0,250.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

   glPushMatrix();
        glTranslatef(50.0/150.0,250.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

   glPushMatrix();
        glTranslatef(100.0/150.0,250.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glPushMatrix();
        glTranslatef(500.0/150.0,500.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

  glColor3f(0.9,0.0,0.0);

  glPushMatrix();
        glTranslatef(900.0/150.0,500.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();

    glPushMatrix();
        glTranslatef(-100.0/150.0,300.0/150.0,-50);
        glutSolidSphere(.1,20,20);
  glPopMatrix();


}
