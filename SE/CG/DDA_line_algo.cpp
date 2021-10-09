/* 
Name - Pradnya Deshmukh
Probelm Statement - Execute DDA line Algorithm
Subject - Computer Graphics
*/

#include<GL/glut.h>
#include<iostream>
#include<Windows.h>
#include<cmath>
using namespace std;
float x1,x2,Y1,y2;
void myInit(void)
{
                glClearColor(1.0,1.0,.0,0.0);
                glColor3f(1.0,0.0,0.0);
                glPointSize(4.0);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(0.0,100.0,0.0,100.0);

}
void mydisplay(void)
{
                float x,y,length,dx,dy;
                int i;
                if (abs(x2-x1)>abs(y2-Y1))
                {
                                length=abs(x2-x1);
                }
                else
                length=abs(y2-Y1);
                dx=(x2-x1)/length;
                dy=(y2-Y1)/length;
                x=x1;
                y=Y1;
                glClear(GL_COLOR_BUFFER_BIT);
                glBegin(GL_POINTS);
                glVertex2i(x,y);
                glEnd();
                while(i<=length)
                {

                                x=x+dx;
                                y=y+dy;
                                glBegin(GL_POINTS);
                                glVertex2i(x,y);
                                glEnd();
                                i=i+1;
                }
                glFlush();
                return ;
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
cout<<"Enter x1"<<flush;
cin>>x1;
cout<<"Enter x2"<<flush;
cin>>x2;
cout<<"Enter y1"<<flush;
cin>>Y1;
cout<<"Enter y2"<<flush;
cin>>y2;
glutInitWindowSize (500, 500);
glutInitWindowPosition (100,100);
glutCreateWindow ("DDA Line Algo");
myInit();
glutDisplayFunc(mydisplay);
glutMainLoop();
return 0;
}

