#include<GL/glut.h> 
#include<iostream> 
void init() 
{ 
    glClearColor(0,0,0,0); 
gluOrtho2D(-250,250,-250,250); 
} 

void brese(int x1, int y1, int x2, int y2) 
{ 
int dx = abs(x2 - x1); 
int dy = abs(y2 - y1); 
int sx = (x2 >= x1) ? 1 : -1; 
int sy = (y2 >= y1) ? 1 : -1; 
int count=0; 
int x = x1, y = y1; 
glBegin(GL_POINTS); 
if (dx > dy) { 
        int p = 2 * dy - dx; 
        for (int i = 0; i <= dx; i++) { 
           if((count/5)%2==0) 
           { 
              glVertex2i(x, y); 
           } 
            x += sx; 
            if (p < 0) { 
                p += 2 * dy; 
            } else { 
                y += sy; 
                p += 2 * (dy - dx); 
            } 
            count++; 
        } 
    } else { 
        int p = 2 * dx - dy; 
        for (int i = 0; i <= dy; i++) { 
        if((count/5)%2==0) 
        { 
           glVertex2i(x, y); 
        } 
            y += sy; 
            if (p < 0) { 
                p += 2 * dx; 
            } else { 
                x += sx; 
                p += 2 * (dx - dy); 
            } 
            count++; 
        } 
    } 
 
    glEnd(); 
    glFlush(); 
} 
 
 
void display() 
{ 
  glClear(GL_COLOR_BUFFER_BIT); 
  glColor3f(1,1,1); 
  glBegin(GL_LINES); 
  glVertex2i(-250,0); 
  glVertex2i(250,0); 
  glVertex2i(0,-250); 
  glVertex2i(0,250); 
  glEnd(); 
   
brese(0, 0, 150, 100);     
brese(0, 0, -150, 100);   
brese(0, 0, -150, -100);  
brese(0, 0, 150, -100);    
   
glFlush(); 
} 
int main(int argc,char **argv) 
{ 
    glutInit(&argc,argv); 
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
glutInitWindowSize(500,500); 
glutInitWindowPosition(100,100); 
glutCreateWindow("Dashed Line"); 
init(); 
glutDisplayFunc(display); 
glutMainLoop(); 
return 0; 

} 
