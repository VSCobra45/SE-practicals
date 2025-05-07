#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define MAX_POINTS 100
#define FACTORIAL_CACHE_SIZE 21
typedef struct {
    float x, y;
} Point;
Point controlPoints[MAX_POINTS];
int numPoints = 0;
double factorialCache[FACTORIAL_CACHE_SIZE]; // Cache for factorial values
int factorialCacheInitialized = 0;
void initFactorialCache() {
    if (factorialCacheInitialized) return;   
    factorialCache[0] = 1.0;
    for (int i = 1; i < FACTORIAL_CACHE_SIZE; i++) {
        factorialCache[i] = factorialCache[i-1] * i;
    }
    factorialCacheInitialized = 1;
}
double factorial(int n) {
    if (n < 0) return 0;
    if (n >= FACTORIAL_CACHE_SIZE) {
        printf("Factorial too large: %d\n", n);
        return 0;
    }
    return factorialCache[n];
}
double binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    return factorial(n) / (factorial(k) * factorial(n - k));
}
void drawPoint(float x, float y) {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
void drawBezierCurve() {
    if (numPoints < 2) return;
    glColor3f(1.0, 1.0, 1.0);  // White color
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.0; t += 0.01) {
        float x = 0, y = 0;
        int n = numPoints - 1;
        for (int i = 0; i <= n; i++) {
            // Calculate the Bernstein polynomial value
            float blend = pow(t, i) * pow(1 - t, n - i) * binomialCoefficient(n, i);           
            // Apply the blend to the control point
            x += controlPoints[i].x * blend;
            y += controlPoints[i].y * blend;
        }
        glVertex2f(x, y);
    }
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw control points
    glColor3f(1.0, 0.0, 0.0);  // Red color
    for (int i = 0; i < numPoints; i++) {
        drawPoint(controlPoints[i].x, controlPoints[i].y);
    }
    // Draw control polygon
    glColor3f(0.0, 1.0, 0.0);  // Green color
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numPoints; i++) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();
    // Draw Bezier curve
    drawBezierCurve();   
    glFlush();
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (numPoints >= MAX_POINTS) {
            printf("Maximum number of control points reached\n");
            return;
        }
        // Convert screen coordinates to GL coordinates
        float xf = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0 - 1.0;
        float yf = 1.0 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0;
        controlPoints[numPoints].x = xf;
        controlPoints[numPoints].y = yf;
        numPoints++;       
        printf("Added control point (%f, %f), total points: %d\n", xf, yf, numPoints);
        glutPostRedisplay();
    }
}
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        // Clear all control points
        numPoints = 0;
        printf("Cleared all control points\n");
        glutPostRedisplay();
    }
    else if (key == 'q' || key == 'Q' || key == 27) {
        // Exit on 'q', 'Q' or ESC
        exit(0);
    }
}
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);   
    initFactorialCache();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve Drawing");
    printf("Bezier Curve Drawing Application\n");
    printf("--------------------------------\n");
    printf("Click with left mouse button to add control points\n");
    printf("Press 'c' to clear all control points\n");
    printf("Press 'q' or ESC to quit\n");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
} 