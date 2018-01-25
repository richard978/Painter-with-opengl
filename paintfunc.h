#ifndef PAINTFUNC_H
#define PAINTFUNC_H
void glRoundRec(float centerX,float centerY,float width,float height,float cirR,int MODE)
{
    float Pi=3.1415926536f;
    float PI_HALF = Pi/2;
    float divide=20.0;
    float tx,ty;
    glBegin(MODE);
    int opX[4]={1,-1,-1,1};
    int opY[4]={1,1,-1,-1};
    float x=0;
    float part=1/divide;
    float w=width/2-cirR;
    float h=height/2-cirR;
    for(x=0;x<4;x+=part){
        float rad = PI_HALF*x;
        tx=cirR*cos(rad)+opX[(int)x]*w+centerX;
        ty=cirR*sin(rad)+opY[(int)x]*h+centerY;
        glVertex2f(tx,ty);
    }
   glEnd();
}

void glEmptyRect(float leftX, float leftY, float rightX, float rightY)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(leftX,leftY);
    glVertex2d(rightX,leftY);
    glVertex2d(rightX,rightY);
    glVertex2d(leftX,rightY);
    glEnd();
}

void Bezier(int n, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float f1, f2, f3, f4;
    float deltaT = 1.0 / n;
    float T;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= n; i++){
        T = i * deltaT;
        f1 = (1-T) *(1-T) * (1-T);
        f2 = 3 * T * (1-T) * (1-T);
        f3 = 3 * T * T * (1-T);
        f4 = T * T * T;
        glVertex2f(f1*x1+f2*x2+f3*x3+f4*x4, f1*y1+f2*y2+f3*y3+f4*y4);
    }
    glEnd();
}
#endif // PAINTFUNC_H
