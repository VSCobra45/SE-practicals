#include <GL/glut.h>
#include <iostream>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // White background
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

bool colorMatch(float* color1, float* color2, float tolerance) {
    for (int i = 0; i < 3; i++) {
        if (abs(color1[i] - color2[i]) > tolerance)
            return false;
    }
    return true;
}

void floodFill(int x, int y, float* newColor, float* boundaryColor) {
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
    float tolerance = 0.1f;

    if (!colorMatch(color, boundaryColor, tolerance) &&
        !colorMatch(color, newColor, tolerance)) {
        
        glColor3f(newColor[0], newColor[1], newColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y, newColor, boundaryColor);
        floodFill(x - 1, y, newColor, boundaryColor);
        floodFill(x, y + 1, newColor, boundaryColor);
        floodFill(x, y - 1, newColor, boundaryColor);
    }
}

void onMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
        y = 480 - y;

        float boundaryColor[] = {0, 0, 1};  // Blue
        float newColor[] = {0, 1, 0};       // Green

        floodFill(x, y, newColor, boundaryColor);
    }
}

void draw_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);  // Blue
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();

    glFlush();
}

void display() {
    draw_triangle();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill Algorithm in OpenGL");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();

	return 0;
}