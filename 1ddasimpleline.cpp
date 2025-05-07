#include <GL/glut.h> 
#include <cmath> 
//void init(); 
//void display(); 
//void dda(int x1,int y1,int x2 ,int y2); 


// Initialization 
void init() 
{ 
glClearColor(0, 0, 0, 0); // black background 
gluOrtho2D(-250, 250, -250, 250); // Cartesian coords 
} 

// DDA Line Drawing 
void dda(int x1,int y1,int x2 ,int y2) 
{ 
    int steps; 
    int dx = x2 - x1; 
    int dy = y2 - y1; 
 
    int m=dy/dx; 
     
    if(abs(dx)>abs(dy)) 
    { 
      steps=abs(dx); 
    } 
    else 
    { 
      steps=abs(dy); 
    } 
     
    
    float xin = dx / (float)steps; 
    float yin = dy / (float)steps; 
 
    float x = x1; 
    float y = y1; 
 
    glColor3f(0.0, 1.0, 0.0); // green line 
    glBegin(GL_POINTS); 
    for (int i = 0; i <= steps; i++) 
    { 
glVertex2i(round(x), round(y)); 
x += xin; 
y += yin; 
} 
glEnd(); 
}

// Display callback 
void display() 
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
// Draw axes 
glColor3f(1, 1, 1); 
glBegin(GL_LINES); 
glVertex2i(-250, 0); glVertex2i(250, 0); // X-axis 
glVertex2i(0, -250); glVertex2i(0, 250); // Y-axis 
glEnd(); 
// Draw DDA Line 
dda(0,0,150,100); 
dda(0,0,-150,100); 
dda(0,0,-150,-100); 
dda(0,0,150,-100); 
glFlush(); 
} 

// OpenGL entry point 
int main(int argc, char **argv) 
{   
    glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
glutInitWindowPosition(100, 100); 
glutInitWindowSize(500, 500); 
glutCreateWindow("DDA Line Drawing"); 
init();    
glutDisplayFunc(display);  // only one display function 
glutMainLoop(); 
return 0;
} 
 
