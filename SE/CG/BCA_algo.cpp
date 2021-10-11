/*
Name - Pradnya Deshmukh
Problem Statement - Execute Bresenham’s circle drawing algorithm
*/

#include<GL/glut.h>
#include<iostream>
#define WIDTH 200
#define HEIGHT 200
#define r 50
#define r2 100
using namespace std;

void BresenhamCircle(int x, int y);

void Init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1*WIDTH, WIDTH, -1*HEIGHT, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
}
void MyMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		y = HEIGHT - y;
		x = x - WIDTH;
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		glFlush();
		BresenhamCircle(x,y);
	}
}
void CirclePoints(int cx,int cy,int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(cx+x, cy+y); glVertex2i(cx+y, cy+x);
	glVertex2i(cx-x, cy+y); glVertex2i(cx+y, cy-x);
	glVertex2i(cx+x, cy-y); glVertex2i(cx-y, cy+x);
	glVertex2i(cx-x, cy-y); glVertex2i(cx-y, cy-x);
	glEnd();
	glFlush();
}
void setpixel(GLint x,GLint y)
{
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
}
void BresenhamCircle(int x1,int y1)
{
	float d,d2;
	int x0 = abs(x1);
	int y0 = abs(y1);
	if (x0 > y0)
	{
		int xx = x0;
		x0 = y0;
		y0 = xx;
	}
	int x, y;
	x = 0, y =r;
	d = 3 -(2*r) ;
	CirclePoints(x1,y1,x, y);
	while (x <= y)
	{
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
		CirclePoints(x1,y1,x, y);
	}
	int x2, y2;
	x2 = 0, y2 =r2;
	d2 = 3 -(2*r2) ;
	CirclePoints(x1,y1,x2, y2);
	while (x2 <= y2)
	{
		if (d2 < 0)
			d2 += 4 * x2+ 6;
		else
		{
			d2 += 4 * (x2 - y2) + 10;
			y2--;
		}
		x2++;
		CirclePoints(x1,y1,x2, y2);
	}


}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(4.0);
	for(int i=-WIDTH;i<=WIDTH;i+=2)
	{
		setpixel(i,0);
		setpixel(0,i);
	}
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(2*WIDTH, 2*HEIGHT);
	glutCreateWindow("Bresenham's Circle");
	Init();
	glutMouseFunc(&MyMouse);
	glutDisplayFunc(&display);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
	return 0;
}
