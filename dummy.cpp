/*
  Copyright notice: This program is hearby licensed under GPL
  In short : U can change this prog but should keep this copyright
            intact and shouldnt use for commercial purpose
  Authors : Shashank S.R , Pradneysh.j , Shivam Sahu
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
using namespace std ;

GLdouble width=200, height=200;   /* window width and height */
int wd;                   /* GLUT window handle */
int ox=120,oy=120,r,a,b;
int arrVertex[10][2],nPoints;

// ------ main circle function drawing ------//

const float mColors[][3]={ {0.5,0.5,0.5},{1.0,3.0,0.0},{3.0,0.0,1.0},{0.2,1.0,0.2},{1.0,1.0,0.0},{1.0,0.0,0.0} };
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

//anti clock
float
      mHexagon[6][3][2]={
                         {{ox,oy},{ox-22.8,oy}   ,{ox-11.4,oy+20}}
                       , {{ox,oy},{ox-11.4,oy+20},{ox+11.4,oy+20}}
                       , {{ox,oy},{ox+22.8,oy}   ,{ox+11.4,oy+20}}
                       , {{ox,oy},{ox+22.8,oy}   ,{ox+11.4,oy-20}}
                       , {{ox,oy},{ox-11.4,oy-20},{ox+11.4,oy-20}}
                       , {{ox,oy},{ox-22.8,oy}   ,{ox-11.4,oy-20}}
                        };

//------------------------------------------//

void
init(void)
{
    translate2D(10.0,0.0);
}

void drawHexagon(){
        int j,k;
        float a=0.0,b=0.0,c=1.0;

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
float aop=0,aopy=0;

void
display(void)
{
     const float ar = (float) width / (float) height;

  /* clear the screen to white */
  glClearColor(0.8,0.8, 0.6, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  //drawCircle(ox,oy,r);

  glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
//   if(aopy+150!=oy)
//        aopy = oy - 150;
  if(aop+150!=ox && ox>100)
        aop=ox -150;

  gluOrtho2D(0.0+aop, 300+aop, 0.0+aopy, 300+aopy);
  //glDisable(GL_DEPTH_TEST);
//  glDisable(GL_CULL_FACE);
//  glDisable(GL_BLENDING);
//  glDisable(GL_TEXTURE_2D);
  //glDisable(GL_LIGHTING);

  drawBoundaries();
  drawHexagon();

  glMatrixMode(GL_PROJECTION);
  //glMatrixMode(GL_PROJECTION);
  glPushMatrix();
        glTranslated(-2.4,1.2,20);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(0.3,5,5);
    glPopMatrix();
   glutSolidCone(1,1,5,5);
//  glFrustum(-ar, ar, -1.0, 1.0, 1.0, 10.0);
//  glScissor(0,0,500,500);
//  glEnable(GL_SCISSOR_TEST);
}

//----------------------------------------movement functions ----------------------------//
//----------------------------------------movement functions ----------------------------//

/*
  Doc:All the movements are taken care by timer funciton,
      This function also simulates gravity and jump.Inclusion of
      all the movements is to gain smooth motion as directly
      giving motion in keyboard press doesnt respond to keys
      which are pressed before a new key press.
  @Params : Given by glut
  @return : null

  All the variables regarding timer are below and nowhere else defined
*/

int refreshMills = 30,delta2=0;
float u=10.0,t=0.1,g=-3,delta=0,mTransHexY=0,mTransHexX=0,transWorlCordX=0;
GLfloat theta = -20.0;
float mMovementArr[2]={0.0,0.0};
bool rightmov=false,leftmov=false,isOnGround=true,jump=false,scale =false,entered = false,lock1=true,lock2=true;
wcPt2D pivotPt;
float temp1,temp2;

void Timer(int value) {

    matrix3x3SetIdentity(matComposite);

    if(isBoundCollY==false&&jump==false){       //jump value changes when 'w' is pressed
        delta2+=2;
        oy-=delta2;
    }else{
        delta2=0;

    }

    if(jump==true ){
        delta=u*t+.5*g*t*t;
        if(delta>-20){
            oy+=delta;
        }
        else{
            oy+=-20;

        }t+=0.5;
    }

    if(rightmov==true){
            ox+=6;
    }else if (leftmov==true){
            ox-=6;
    }


    oy=check_Y_Collission(ox,oy);
    ox=fn_x;


    if(isBoundCollY==true){         // isBoundCollY in boundary.h
            t=0;
            u=10.0;
            jump=false;
            delta=0;
            delta2=0;
    }

    if(oy>300&&lock1){
     //   glTranslatef(0.0,-200.0,0.0);
        aopy+=260;
        lock1=false;
        lock2=false;
    }else if(oy<300&&!lock2){
       // glTranslatef(0.0,200,0.0);
        aopy-=260;
        lock2=true;
        lock1=true;
    }

//    if(ox>=150 && ox<= 1600-width/4&&rightmov){
//      if(isBoundCollX==false){
//        //glTranslatef(-4.0,0.0,0.0);
//        aop+=4;
//        ox=ox-5;
//        check_Y_Collission(ox,oy);
//        ox=fn_x;
//      }
//    }else if(ox>=150&& ox<= 1600-width/4&&leftmov){
//      if(isBoundCollX==false){
//        //glTranslatef(4.0,0.0,0.0);
//        aop-=4;
//        ox=ox+5;
//        check_Y_Collission(ox,oy);
//        ox=fn_x;
//      }
//    }


    if(mHexagon[0][0][1]!= oy){
        mTransHexY=oy-mHexagon[0][0][1];
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


    if(scale==true && entered==false){
       scale2D(2,2,pivotPt);
       entered =true;
    }else if(scale==false && entered ==true){
       scale2D(0.5,0.5,pivotPt);
       entered = false;
    }


    transformVerts2D(mHexagon);
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

  //oy=check_Y_Collission(ox,oy);
  //glMatrixMode(GL_MODELVIEW);
  //glTranslatef(mMovementArr[0],mMovementArr[1],0.0f);

//  display();
}

void keyRelease(unsigned char key,int x, int y){

     switch(key){
      case 'd':
                rightmov = false;
               break;
      case 'a':
                leftmov = false;
               break;
      case 'w':
               break;
      case 's':
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
  //glViewport(0, 0, 500, 500);
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  //glutSolidCone(2,1,5,5);
 //gluOrtho2D(0.0, width, 0.0, height);
 // glEnable(GL_SCISSOR_TEST);
  //glScissor(width/10,height/10,width-2*width/10,height-2*height/10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}

int
main(int argc, char *argv[]){
    ox=120;
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
      glutMainLoop();
      return 0;
    }

}
