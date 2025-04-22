#include <iostream>
#include <GL/glut.h>

using namespace std;

void init(){
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set the background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);  // Set up orthographic projection
}

// The recursive boundary fill algorithm
void bound_it(int x, int y, float* fillColor, float* bc){
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);  // Get the color at the current point

    // Check if the color is different from the boundary color and the fill color
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {

        // Set the fill color and draw the point
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x, y);  // Draw a single pixel
        glEnd();
        glFlush();  // Flush the buffer to ensure the drawing is updated

        // Recursively call the function to fill neighboring pixels
        bound_it(x + 1, y, fillColor, bc);  // Right
        bound_it(x - 1, y, fillColor, bc);  // Left
        bound_it(x, y + 1, fillColor, bc);  // Up
        bound_it(x, y - 1, fillColor, bc);  // Down
    }
}

void mouse(int btn, int state, int x, int y){
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Boundary color (blue) and fill color (red)
        float bCol[] = {0, 0, 1};  // Blue boundary
        float color[] = {1, 0, 0}; // Red fill color

        // Adjust the y-coordinate because OpenGL's origin is at the bottom-left
        y = 480 - y;
        
        bound_it(x, y, color, bCol);  // Start the boundary fill at the clicked point
    }
}

void world(){
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    glLineWidth(3);
    glPointSize(2);

    // Draw a blue triangle (boundary)
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2i(150, 100);
        glVertex2i(300, 300);
        glVertex2i(450, 100);
    glEnd();

    glFlush();  // Ensure all the drawing is done
}

int main(int argc, char** argv){
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);  // Set the window size
    glutInitWindowPosition(200, 200);  // Set the window position
    glutCreateWindow("Flood Fill Algorithm in OpenGL");

    init();  // Initialize OpenGL settings
    glutDisplayFunc(world);  // Set the display function
    glutMouseFunc(mouse);  // Set the mouse function
    glutMainLoop();  // Start the main event loop

    return 0;
}
