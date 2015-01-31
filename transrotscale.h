
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265

GLsizei winWidth = 600, winHeight=600;

GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt2D{
public :
        GLfloat x, y;
};

typedef GLfloat Matrix3x3 [3][3];

Matrix3x3 matComposite;

const GLdouble pi = 3.14159;

float hex_temp[6][3][2];


void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
        GLint row, col;
        for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
        {
                matIdent3x3[row][col] = (row == col);
        }
}

void matrix3x3PreMultiply(Matrix3x3 m1,Matrix3x3 matComposite)
{
        GLint row, col;
        Matrix3x3 matTemp;

            for (row = 0; row < 3; row++){
                for (col = 0; col < 3; col++){
                    matTemp[row][col] =   m1[row][0] * matComposite[0][col]
                                        + m1[row][1] * matComposite[1][col]
                                        + m1[row][2] * matComposite[2][col];
                }
            }
            for (row = 0; row < 3; row++){
                for (col = 0; col < 3; col++){
                   matComposite[row][col] = matTemp[row][col];
                }
            }

}


void translate2D(GLfloat tx, GLfloat ty)
{
        Matrix3x3 matTransl;
        matrix3x3SetIdentity(matTransl);

        matTransl[0][2] = tx;
        matTransl[1][2] = ty;

        matrix3x3PreMultiply(matTransl, matComposite);
}

void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
        Matrix3x3 matRot;
        matrix3x3SetIdentity(matRot);


        matRot[0][0] = cosf(theta*PI/180);
        matRot[0][1] = -sinf(theta*PI/180);
        matRot[0][2] = pivotPt.x *(1-cosf(theta*PI/180)) + pivotPt.y * sinf(theta*PI/180);
        matRot[1][0] = sinf(theta*PI/180);
        matRot[1][1] = cosf(theta*PI/180);
        matRot[1][2] = pivotPt.y *(1 - cosf(theta*PI/180)) - pivotPt.x * sinf(theta*PI/180);

        matrix3x3PreMultiply(matRot,matComposite);
}

void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
        Matrix3x3 matScale;
        matrix3x3SetIdentity(matScale);

        matScale[0][0] = sx;
        matScale[0][2] = (1 - sx)*fixedPt.x;
        matScale[1][1] = sy;
        matScale[1][2] = (1 - sy)*fixedPt.y;

        matrix3x3PreMultiply(matScale, matComposite);
}


void transformVerts2D(float hex[][3][2]){

  GLfloat temp;
  int j=0,k;
      for(j=0;j<6;j++)
        for (k = 0; k < 3; k++){

                        temp = matComposite[0][0] *hex[j][k][0] +
                               matComposite[0][1] *hex[j][k][1] +
                               matComposite[0][2];
                hex[j][k][1] = matComposite[1][0] *hex[j][k][0] +
                               matComposite[1][1] *hex[j][k][1] +
                               matComposite[1][2];
                hex[j][k][0] = temp;
        }
}
