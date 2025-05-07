#include <math.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <stdlib.h> 

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glPointSize(1.0);
    gluOrtho2D(0, 640, 0, 550);
}
// Flood fill algorithm (4-directional)
void floodFill(int x, int y, float* fillColor, float* boundaryColor) {
    float oldColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, oldColor);
    // Stop if pixel is the same as boundary color or already filled
    if ((oldColor[0] == boundaryColor[0] && oldColor[1] == boundaryColor[1] && oldColor[2] == boundaryColor[2]) || 
    (oldColor[0] == fillColor[0] && oldColor[1] == fillColor[1] && oldColor[2] == fillColor[2])) 
    {
        return;
    }
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
    // Recursive flood fill in 4 directions
    floodFill(x + 1, y, fillColor, boundaryColor); // Right
    floodFill(x- 1, y, fillColor, boundaryColor); // Left
    floodFill(x, y + 1, fillColor, boundaryColor); // Up
    floodFill(x, y- 1, fillColor, boundaryColor); // Down
}

void onMouseClick(int button, int state, int x, int y) { 
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        float fillColor[] = {0, 1, 0};  // Green color 
        float boundaryColor[] = {0, 0, 0};  // Green color 
        printf("Clicked at x: %d, y: %d\n", x, y); 
        floodFill(x, 550 - y, fillColor, boundaryColor);  // Convert y coordinate 
    } 
} 
    
void drawTriangle() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0, 1, 0);  // Green color 
    glBegin(GL_LINE_LOOP); 
    glVertex2i(300, 100); 
    glVertex2i(300, 300); 
    glVertex2i(450, 100); 
    glEnd(); 
    glFlush(); 
} 
    
void display(void) { 
    drawTriangle(); 
} 
    
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
    glutInitWindowSize(640, 550);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Flood Fill Triangle"); 
    init(); 
    glutDisplayFunc(display); 
    glutMouseFunc(onMouseClick); 
    glutMainLoop(); 
    return 0; 
} 
