/*
  Copyright notice: This program is hearby licensed under GPL
  In short : U can use this program but should keep this copyright
            intact and shouldnt use for commercial purpose
  Authors : Shashank S.R , Pradneysh.j , Shivam Sahu
            12IT58           12IT49         12IT74
*/




#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "boundary.h"
#include "transrotscale.h"
#include "3dpoints.h"

using namespace std ;

GLdouble width=200, height=200;
int wd;
int ox=120,oy=120,r,a,b;
int arrVertex[10][2],nPoints;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

//colors used for hex
const float mColors[][3]={ {1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,1.0,1.0},{0.0,0.0,1.0},{0.5,0.0,1.0} };

//anti clockwise
float
      mHexagon[6][3][2]={
                         {{ox,oy},{ox-22.8,oy}   ,{ox-11.4,oy+20}}
                       , {{ox,oy},{ox-11.4,oy+20},{ox+11.4,oy+20}}
                       , {{ox,oy},{ox+22.8,oy}   ,{ox+11.4,oy+20}}
                       , {{ox,oy},{ox+22.8,oy}   ,{ox+11.4,oy-20}}
                       , {{ox,oy},{ox-11.4,oy-20},{ox+11.4,oy-20}}
                       , {{ox,oy},{ox-22.8,oy}   ,{ox-11.4,oy-20}}
                        };


// ------ main circle function drawing (NOT USED - kept for understanding game logic) ------//
/*
    This function was used in the intial
    coding stage written by us .. This not used
    now .However the whole game logic is based on the
    center of this circle.We just mapped the hexagon
    to this circle's center whose radius is 20
*/

int f(int ox,int oy ,int x,int y,int r){
    return(x*x+y*y - r*r);
}

void drawCircle(int originX,int originY , int radius){
        int dMp;
        int x=0;
        int y=radius;
        int c=originY-originX;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        dMp = f(originX,originY,x+1,y-(1/2),radius);
        glVertex2d(originX,originY);
        while(y>x){
            if(dMp >= 1){
                dMp=dMp+2*x-2*y+5;
                x=x+1;
                y=y-1;

                glVertex2d(x+originX,y+originY);
                glVertex2d(y+originY-c,x+c+originX);
                glVertex2d(-x+originX,-y+originY);
                glVertex2d(-y+originY-c,-x+originX+c);
                glVertex2d(x+originX,-y+originY);
                glVertex2d(-y+originY-c,x+originX+c);
                glVertex2d(-x+originX,y+originY);
                glVertex2d(y+originY-c,-x+originX+c);
                }
            else{
                dMp=dMp + 2*x +3;//lConst;//
                x=x+1;
                glVertex2d(x+originX,y+originY);
                glVertex2d(y+originY-c,x+c+originX);
                glVertex2d(-x+originX,-y+originY);
                glVertex2d(-y+originY-c,-x+originX+c);
                glVertex2d(x+originX,-y+originY);
                glVertex2d(-y+originY-c,x+originX+c);
                glVertex2d(-x+originX,y+originY);
                glVertex2d(y+originY-c,-x+originX+c);
                }
            }
            glEnd();
         glFlush();
}


//------------------------------------------//
void
init(void)
{
}


void drawHexagon(){
        int j,k;
        glBegin(GL_TRIANGLES);
        for(j=0;j<6;j++){
            glColor3f(mColors[j][0],mColors[j][1],mColors[j][2]);
            for(k=0;k<3;k++){
                glVertex2f(mHexagon[j][k][0],mHexagon[j][k][1]);
            }
        }

        glEnd();
        glFlush();
}

//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
float cameraX=0,cameraY=0;

/// ORTHO AND GLUORTHO2D:->
 /* GLUORTHO2D tells how much of the view port should be shown
    (viewport clipping) ... example if we give gluortho(0,300,..,..)
    it shows the world coordinates till 300 in a single window... now glortho
    takes parameters in terms of screen space ... i.e screen ranges
    from -1 to 1 ie 0 to 300 in world coordinates == 2 units for
    gluortho ... hence the correction factor is aop/150 wich is
    exactly equal to 300/2

    This implies changing the gluortho2d will destroy the staticness of
    the spheres .
*/

void
display(void)
{

  // screen background movement
  if(cameraX+150!=ox && ox>100)
        cameraX=ox -150;

 // sky blue color :red 0.196078 green 0.6 blue 0.8
  glClearColor(0.196078,0.6, 0.8, 1.0);

  // setting camera ..  glfrustrum is not used as we dont need depth feel
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1+cameraX/150, 1+cameraX/150, -1.0+cameraY/150, 1.0+cameraY/150, 2.0, 100.0);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH);
  glEnable(GL_CULL_FACE);

  // drawing 3d ...
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1,0,0);
  drawSpheres();                                  // in 3dpoints.h

//------------------------------------------------------------------//
// setting 2d projection matrix

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0+cameraX, 300+cameraX, 10.0+cameraY, 310+cameraY); /// NOTE : THE DIVISION FACTOR FOR ORTHO IS 300/2

//drawing 2d stuff
glDisable(GL_CULL_FACE);
glDisable(GL_LIGHT0);
glDisable(GL_NORMALIZE);
glDisable(GL_COLOR_MATERIAL);
glDisable(GL_LIGHTING);
glClear(GL_DEPTH_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

drawHexagon();              //defined in main.cpp
drawBoundaries();           //defined in boundary.h
drawCircle(ox,oy,r);
// Making sure we can render 3d again
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);

glutSwapBuffers();

}


//----------------------------------------movement functions ----------------------------//
//----------------------------------------movement functions ----------------------------//

/*
  Doc:All the movements are taken care by timer funciton,
      This function also simulates gravity and jump.Inclusion of
      all the movements in same function is to gain smooth motion
      of the hexagon as directly giving motion in keyboard press
      callback function doesnt respond to keys which are pressed
      before a new key press.

  @Params : Given by glut
  @return : null

  All the variables regarding timer are below and nowhere else defined
*/

int refreshMills = 30,delta2=0;
float u=10.0,t=0.1,g=-3,delta=0;
GLfloat theta = -20.0;
bool rightmov=false,leftmov=false,jump=false,scale =false;
bool lock1=true,lock2=true,scaleLock = false;
wcPt2D pivotPt;
int bgY2lock=0,bgY2lock2=0;

void Timer(int value) {

//needed for movement functions
   matrix3x3SetIdentity(matComposite);

/*
 The center of the first mentioned circle
 is changed using simple addition and
 subtraction . Elementary physics is used
 to simulate jump . However when the change
 in the coordinates is large it avoids collision
 detection. Hence after a certain value change
 is kept constant.
*/
//gravity simulation...
    if(isBoundCollY==false&&jump==false){       //jump value changes when 'w' is pressed
        delta2+=2;
        oy-=delta2;
    }else{
        delta2=0;
    }

//jump simulation ...
    if(jump==true ){
        delta=u*t+.5*g*t*t;
        if(delta>-20){
            oy+=delta;
        }
        else{
            oy+=-20;
        }t+=0.5;
    }

//right and left movement ...
    if(rightmov==true){
            ox+=6;

    }else if (leftmov==true){
            ox-=6;

    }

    //validating center of circle for collission
    oy=check_Y_Collission(ox,oy);   //in boundary.h
    ox=fn_x;


//termination of jump when collided with ground
    if(isBoundCollY==true){         // isBoundCollY in boundary.h
            t=0;
            u=10.0;
            jump=false;
            delta=0;
            delta2=0;
    }

//background movement when jumped
    if(oy>300&&lock1){
        cameraY+=260;
        lock1=false;
        lock2=false;
    }else if(oy<300&&!lock2){
        cameraY-=260;
        lock2=true;
        lock1=true;
    }
    if(oy>500&&bgY2lock==0){
        cameraY+=150;
        bgY2lock=1;
        bgY2lock2=1;
    }else if(oy>300&&oy<500 && bgY2lock2==1){
        cameraY-=150;
        bgY2lock=0;
        bgY2lock2=0;
    }


//hexagon movement functions ....
/*These functions are excecuted after
//getting valid x,y coordinates of
//the circle mentioned in begininig
//The hex is translated such that its center
//coincides with the center of circle.
The rotation translation and scaling functions
Translate2d Rotate2d and scale2d are in transrotscale.h
*/

    if(mHexagon[0][0][1]!= oy){
        translate2D(0,oy-mHexagon[0][0][1]);
    }

    if(mHexagon[0][0][0]!=ox){
        if(rightmov==true){
            pivotPt.x=mHexagon[0][0][0];
            pivotPt.y=mHexagon[0][0][1];
            rotate2D(pivotPt, theta);
            translate2D(ox-mHexagon[0][0][0],0);

        }else if(leftmov==true){
             pivotPt.x=mHexagon[0][0][0];
             pivotPt.y=mHexagon[0][0][1];
            rotate2D(pivotPt, -theta);
            translate2D(ox-mHexagon[0][0][0],0);
        }
    }


// scale function ----------//
    if(scale==true && scaleLock==false){
       scale2D(2,2,pivotPt);
       scaleLock =true;     //for toggling
    }else if(scale==false && scaleLock ==true){
       scale2D(0.5,0.5,pivotPt);
       scaleLock = false;
    }


    transformVerts2D(mHexagon);  //applying transformation for the hexagon
    display();
    glutTimerFunc(refreshMills,Timer,0); // calls the timer after refreshMlls sec
}

void handleMouseKeyPress(unsigned char key,int x, int y){

  switch(key){
      case 'd':
      case  'D':

                rightmov = true;
                break;
      case 'a':
      case 'A':

                leftmov = true;
                break;
      case 'w':
      case 'W':
                jump=true;
                break;
      case 's':
      case 'S':
                if(scale ==false)
                    scale = true;
                else
                    scale=false;
                break;
  }

}

void keyRelease(unsigned char key,int x, int y){

     switch(key){
      case 'd':
      case 'D':
                rightmov = false;
               break;
      case 'a':
      case 'A':
                leftmov = false;
               break;
      case 'w':
      case 'W':
               break;
      case 's':
      case  'S':
               break;
    }
}

//----------------------------------------------------------------//
//----------------------------------------------------------------//

//-----------------Glut functions ----------------------------------//
void
reshape(int w, int h){

  width = (GLdouble) w;
  height = (GLdouble) h;
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}


int
main(int argc, char *argv[]){
    ox=120;         //initializing the circle and hex
    oy=120;
    r=20;
    pivotPt.x=120;
    pivotPt.y=120;

    {
      init();
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
      glutInitWindowSize((int) width, (int) height);

      glutTimerFunc(0,Timer,0);
      wd = glutCreateWindow("I.T 2016 graphics project" /* title */ );
      glutReshapeFunc(reshape);
      matrix3x3SetIdentity(matComposite);
      glutKeyboardFunc(handleMouseKeyPress);
      glutKeyboardUpFunc(keyRelease);
      glutDisplayFunc(display);

      glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


      glutMainLoop();
      return 0;
    }

}
