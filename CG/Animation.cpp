#include <GL/glut.h>
#include <cmath>

float ballX = 0.0f;
float ballY = 0.0f;
float radius = 0.1f;
float ySpeed = 0.02f;
bool goingUp = true;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the ball
    glTranslatef(ballX, ballY, 0.0f);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for(int angle = 0; angle <= 360; angle += 10) {
        float theta = angle * 3.14159f / 180;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // Simple up and down bouncing logic
    if (goingUp) {
        ballY += ySpeed;
        if (ballY >= 0.8f) goingUp = false;
    } else {
        ballY -= ySpeed;
        if (ballY <= -0.8f) goingUp = true;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

void init() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Light background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bouncing Ball Animation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

