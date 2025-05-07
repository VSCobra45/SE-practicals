#include <GL/glut.h>  
#include <cmath>  
using namespace std; 
float xball=0.0f; 
float yball=-0.0f; 
float r=0.1f; 
float yspeed=0.02f; 
bool goingUp=true; 
void init() 
{  
 
glClearColor(0.9f, 0.9f, 0.9f, 1.0f);  
glMatrixMode(GL_PROJECTION);  
glLoadIdentity();  
gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  
} 

void display() 
{ 
glClear(GL_COLOR_BUFFER_BIT);  
glLoadIdentity(); 
glTranslatef(xball,yball,0.0f); 
glColor3f(1.0,0.0,0.0); 
glBegin(GL_TRIANGLE_FAN); 
glVertex2f(0.0f,0.0f); 
for(int angle=0;angle<=360;angle=angle+10) 
{ 
    float theta=angle*3.14159f/180; 
    glVertex2f(r*cos(theta),r*sin(theta));  
} 
 
glEnd(); 
glutSwapBuffers(); 
} 
void update(int value) 
{ 
if(goingUp) 
{ 
yball=yball+yspeed; 
if(yball>=0.8f) 
{ 
        goingUp=false; 
     } 
   } 
     else 
     { 
        yball=yball-yspeed; 
         
        if(yball<=-0.8f) 
        { 
          goingUp=true; 
           
        } 
     } 
    
   glutPostRedisplay(); 
   glutTimerFunc(16,update,0); 
    
} 
 
 
int main(int argc, char** argv)  
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
  glutInitWindowSize(600, 600);  
  glutCreateWindow("Animation");  
  init();  
glutDisplayFunc(display);  
glutTimerFunc(0, update, 0);  
glutMainLoop();  
return 0;  
}