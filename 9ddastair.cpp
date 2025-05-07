#include <GL/glut.h>
#include <cmath>

void init() {
    glClearColor(0, 0, 0, 0);  // Black background
    gluOrtho2D(-250, 250, -250, 250);  // Set the 2D orthographic view
}

void dda(int x1, int y1, int x2, int y2) {
    int steps;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);  // Choose the greater of dx or dy
    } else {
        steps = abs(dy);
    }

    float xin = dx / (float)steps;  // Calculate the increment for x
    float yin = dy / (float)steps;  // Calculate the increment for y

    float x = x1;
    float y = y1;

    glColor3f(0.0, 1.0, 0.0);  // Green color for the steps
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));  // Draw a point at (x, y)

        x += xin;  // Increment x for horizontal movement
        y += yin;  // Increment y for vertical movement
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    glColor3f(1, 1, 1);  // White color for the axes
    glBegin(GL_LINES);  // Draw coordinate axes
    glVertex2i(-250, 0); glVertex2i(250, 0);  // X-axis
    glVertex2i(0, -250); glVertex2i(0, 250);  // Y-axis
    glEnd();

    // Draw stair steps
    dda(0, 0, 50, 0);    // First horizontal step (right)
    dda(50, 0, 50, 50); // First vertical step (up)
    dda(50, 50, 100, 50); // Second horizontal step (right)
    dda(100, 50, 100, 100); // Second vertical step (up)
    dda(100, 100, 150, 100); // Third horizontal step (right)

    glFlush();  // Force OpenGL to render the image immediately
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Drawing");

    init();  // Initialize OpenGL settings
    glutDisplayFunc(display);  // Set the display function
    glutMainLoop();  // Enter the GLUT main loop

    return 0;
}
