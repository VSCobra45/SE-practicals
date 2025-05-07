#include<GL/glut.h> 
#include<iostream> 
using namespace std; 
void init() 
{ 
    glClearColor(0,0,0,0); 
    gluOrtho2D(250,-250,250,-250);
} 
 
void plot(int xc,int yc,int x,int y) 
{ 
glBegin(GL_POINTS); 
glVertex2i(xc+x,yc+y); 
glVertex2i(xc-x,yc+y); 
glVertex2i(xc+x,yc-y); 
glVertex2i(xc-x,yc-y); 
glVertex2i(yc+y,xc+x); 
glVertex2i(yc-y,xc+x); 
glVertex2i(yc+y,xc-x); 
glVertex2i(yc-y,xc-x); 
glEnd(); 
} 
 
void drawCircle(int xc,int yc,int r) 
{ 
  int x=0; 
  int y=r; 
  int p=3-2*r; 
   
  glBegin(GL_POINTS); 
   
  while(x<=y) 
  { 
    plot(xc,yc,x,y); 
     
    if(p<0) 
    { 
       p=p+4*x+6; 
    } 
    else 
    { 
      p=p+4*(x-y)+10; 
      y--; 
    } 
    x++; 
  } 
   
  glEnd(); 
   
} 
void display() 
{ 
    glColor3f(1,0,1); 
    glBegin(GL_LINES); 
    glVertex2i(250,0); 
    glVertex2i(-250,0); 
    glVertex2i(0,250); 
    glVertex2i(0,-250); 
    drawCircle(0,0,50); 
    glEnd(); 
    glFlush();
} 
 
int main(int argc,char **argv) 
{ 
glutInit(&argc,argv); 
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
glutInitWindowSize(500,500); 
glutInitWindowPosition(100,100); 
glutCreateWindow("Circle"); 
init(); 
glutDisplayFunc(display); 
glutMainLoop(); 
return 0; 
} 
