#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define UPPER 0
#define LOWER 1
#define LEFT 1
#define RIGHT 0
                                        //   ^
// imp   -> x cordinates increase  | y cordinates increase
/// The boundary collision detection uses tile logic
/// as I found that its the fastest way to detect collsion
/// and correct it
using namespace std;


int fn_x,i,j,mTile;

// Below are the POINTS in sequence TO DRAW the BOUNDARY polygon

 int mPoints[][2]={ {0,100},{200,100},{200,150},
                  {300,150},{300,200},{400,200},{400,100},{600,100},
                  {600,50},{700,50},{700,150},{800,150},{800,200},{900,200},{900,150},{1000,150},
                  {1000,100},{1200,100},{1200,150},{1300,150},{1300,200},{1100,200},{1100,225},{1200,225},{1200,250},
                 {1300,250},{1300,500},{700,500},{700,525},{800,525},{800,550},{1000,550},
                 {1000,600},{1100,600},{1100,550},{1300,550},{1300,600},{1400,600},{1400,0},
                 {0,0},{0,400}
        };

 int mPoints2[][2]={ {0,400},{100,400},{100,300},{0,300}};//,{200,350},{200,300}};//,{300,350},{300,300},{0,300}};
 int mPoints4[][2]={ {100,350},{300,350},{300,300},{100,300}};
 int mPoints5[][2]={ {300,450},{400,450},{400,300},{300,300}};
 int mPoints6[][2]={ {400,400},{500,400},{500,300},{400,300}};//
 int mPoints7[][2]={ {500,350},{700,350},{700,300},{500,300}};
 int mPoints8[][2]={ {700,325},{900,325},{900,300},{700,300}};

// int mPoints4[][2]={{500,350},{700,350},{700,325},{900,325},{900,300},{0,300} };
int mPoints3[][2]={{1000,300},{1100,300},{1100,325},{1000,325},{1000,300}};


 /*
  Doc:Main Collision Logic:->
      Entire window is divided into tiles.Each tile has bounds in
      Y and X directions . If the character doesnt fall within the
      bounds then we adjust its values.Below are the arrays which
      store the bounds of each tiles. The 1st dimension is the row or
      column . 2nd is the 'Tile' in the row or column . 3rd are the bounds
      of the tile in X or Y direction. Made 2 different arrays for ease
      of maintanace.These bounds can also be stored in file and loaded.

 */

 int mYCollision[][7][2]={{{100,100+20},{NULL,100+20},{300-20,NULL},{NULL,400+20},{NULL,400+20},{NULL,NULL},{700-20,NULL}}
                        , {{100,100+20},{NULL,100+20},{300-20,NULL},{NULL,350+20},{NULL,NULL},{NULL,NULL},{700-20,NULL}}
                        , {{150,150+20},{NULL,150+20},{300-20,NULL},{NULL,350+20},{NULL,350+20},{NULL,NULL},{700-20,NULL}}
                       ,  {{200,200+20},{NULL,200+20},{300-20,200+20},{NULL,450+20},{NULL,450+20},{NULL,NULL},{700-20,NULL}}
                        , {{100,100+20},{NULL,100+20},{300-20,NULL},{NULL,400+20},{NULL,400+20},{NULL,NULL},{700-20,NULL}}
                        , {{100,100+20},{NULL,100+20},{300-20,NULL},{NULL,350+20},{500-20,NULL},{NULL,525+20},{700-20,NULL}}
                        , {{NULL,50+20} ,{NULL,50+20}  ,{300-20,NULL},{NULL,350+20},{NULL,NULL},{NULL,NULL},{700-20,NULL}}
                    ,   {{NULL,150+20},{NULL,150+20},{300-20,NULL},{NULL,325+20},{500-20,NULL},{NULL,525+20},{700-20,NULL}}
                    ,   {{NULL,NULL},{NULL,200+20},{300-20,200+20},{NULL,325+20},{500-20,NULL},{NULL,550+20},{700-20,NULL}}
                    ,   {{NULL,NULL},{NULL,150+20}  ,{NULL,NULL}  ,{NULL,NULL}  ,{500-20,NULL},{NULL,550+20},{700-20,NULL}}
                     ,  {{NULL,100+20},{NULL,100+20}  ,{300-20,NULL}  ,{NULL,325+20}  ,{500-20,NULL},{NULL,600+20},{700-20,600+20}}
                     ,  {{NULL,100+20},{200-20,100+20},{NULL,225+20},{NULL,NULL}  ,{500-20,NULL},{NULL,550+20},{700-20,NULL}}
                    ,   {{NULL,NULL},{200-20,150+20},{NULL,250+20},{NULL,NULL}  ,{500-20,NULL},{NULL,550+20},{700-20,NULL}}
                         };


 int mXCollision[][13][2] ={
                         { {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}}       //1
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{700-20,600+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{700-20,600+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

                        ,{ {NULL,20},{200-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{700-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,1000+20},{1200-20,NULL},{1300-20,NULL}}   //2
                        ,{ {NULL,20},{200-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{700-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,1000+20},{1200-20,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{300-20,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{NULL,NULL},{800-20,NULL},{NULL,NULL},{NULL,900+20},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{300-20,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{NULL,NULL},{800-20,NULL},{NULL,NULL},{NULL,900+20},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1100-20,NULL},{NULL,NULL},{1300-20,NULL}}     //3
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1200-20,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,900+20},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}      //4
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,700+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,100+20},{300-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,500+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,100+20},{300-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,500+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

                        ,{ {NULL,20},{NULL,NULL},{300-20,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}        //5
                        ,{ {NULL,20},{NULL,NULL},{300-20,NULL},{NULL,NULL},{NULL,400+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{500-20,NULL},{NULL,NULL},{700-20,600+20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}      //6
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{800-20,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1000-20,NULL},{NULL,NULL},{NULL,1100+20},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1000-20,NULL},{NULL,NULL},{NULL,1100+20},{1300-20,NULL}}

                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}            //7
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}
                        ,{ {NULL,20},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{1300-20,NULL}}

 };


bool isBoundCollY=false,isBoundCollX=false;


void drawBoundaries(){

        glColor3f(0.9, 0.6, 0.0);
        //glBegin(GL_POLYGON);
        //-------------------------------------------------------------------//

        glBegin(GL_POLYGON);
        glVertex2d(0,0);
        glVertex2d(0,100);
        glVertex2d(200,100);
        glVertex2d(200,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(200,150);
        glVertex2d(300,150);
        glVertex2d(300,0);
        glVertex2d(200,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(300,0);
        glVertex2d(300,200);
        glVertex2d(400,200);
        glVertex2d(400,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(400,0);
        glVertex2d(400,100);
        glVertex2d(600,100);
        glVertex2d(600,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(700,0);
        glVertex2d(700,150);
        glVertex2d(800,150);
        glVertex2d(800,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(800,0);
        glVertex2d(800,200);
        glVertex2d(900,200);
        glVertex2d(900,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(900,0);
        glVertex2d(900,150);
        glVertex2d(1000,150);
        glVertex2d(1000,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1000,0);
        glVertex2d(1000,100);
        glVertex2d(1200,100);
        glVertex2d(1200,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1200,0);
        glVertex2d(1200,150);
        glVertex2d(1300,150);
        glVertex2d(1300,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1300,0);
        glVertex2d(1300,600);
        glVertex2d(1400,600);
        glVertex2d(1400,0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1100,200);
        glVertex2d(1100,225);
        glVertex2d(1300,225);
        glVertex2d(1300,200);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1200,225);
        glVertex2d(1200,250);
        glVertex2d(1300,250);
        glVertex2d(1300,225);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(700,500);
        glVertex2d(700,525);
        glVertex2d(1300,525);
        glVertex2d(1300,500);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(800,525);
        glVertex2d(800,550);
        glVertex2d(1300,550);
        glVertex2d(1300,525);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2d(1000,500);
        glVertex2d(1000,600);
        glVertex2d(1100,600);
        glVertex2d(1100,500);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2d(600,0);
        glVertex2d(600,50);
        glVertex2d(700,50);
        glVertex2d(700,0);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2d(500,500);
        glVertex2d(500,525);
        glVertex2d(600,525);
        glVertex2d(600,500);
        glEnd();

        //--------------------------------------------------------//

      //  glBegin(GL_LINE_STRIP);
         glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints2[i][0] ,mPoints2[i][1]);
           }
        glEnd();
         glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints4[i][0] ,mPoints4[i][1]);
           }
        glEnd();
         glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints5[i][0] ,mPoints5[i][1]);
           }
        glEnd();
         glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints6[i][0] ,mPoints6[i][1]);
           }
        glEnd();
          glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints7[i][0] ,mPoints7[i][1]);
           }
        glEnd();
          glBegin(GL_POLYGON);
           for(i=0;i<4;i++){
            glVertex2d(mPoints8[i][0] ,mPoints8[i][1]);
           }
        glEnd();
        // glBegin(GL_LINE_STRIP);
         glBegin(GL_POLYGON);
           for(i=0;i<5;i++){
            glVertex2d(mPoints3[i][0] ,mPoints3[i][1]);
           }
        glEnd();
        glColor3f(1.0,0.7,0.0);
         glBegin(GL_LINE_STRIP);
           for(i=0;i<41;i++){
             glVertex2d(mPoints[i][0] ,mPoints[i][1]);
           }
        glEnd();
        glFlush();

}


/*
    Doc:
        The below function sees if the given coordinates are
    within the collision bounds and if not return correct the
    value . We check both the collisions in same function as
    one value depends on other .. i.e collision value of
    y depends both on y as well as x and same with y.If two seperate
    functions.. each are called at different time period leading
    to collision mismatch

    @Params : x , y coordinates of the character
    @Return : valid  y Coordinates and we use fin_x to validate x(bounds)

*/

// Collsion functions start

 float check_Y_Collission(int x,int y){

    //check collsion with y

    i= x/100;
    mTile = y/100  ;

    if(y>mYCollision[i][mTile][UPPER] && mYCollision[i][mTile][UPPER]!= NULL){
        y=mYCollision[i][mTile][UPPER];
        //isBoundCollY=true;
    }else if(y<mYCollision[i][mTile][LOWER] && mYCollision[i][mTile][LOWER]!= NULL){
        y=mYCollision[i][mTile][LOWER];
        isBoundCollY=true;
    }else{
        isBoundCollY=false;
    }

    // check collision with x

    i= y/25;
    mTile = x/100;


    if(x>mXCollision[i][mTile][RIGHT] && mXCollision[i][mTile][RIGHT]!= NULL){
        x=mXCollision[i][mTile][RIGHT];
          isBoundCollX=true;
    }else if(x<mXCollision[i][mTile][LEFT] && mXCollision[i][mTile][LEFT]!= NULL){
        x=mXCollision[i][mTile][LEFT];
          isBoundCollX=true;
    }else{
          isBoundCollX=false;
    }

    fn_x=x; // we equate ox with this as we need change two values and can return only one

    return y;
 }




