#include <iostream>
#include <GL/glut.h>

using namespace std;

int wxmin = 200, wxmax = 500, wymin = 100, wymax = 350;
int points[10][2];
int edge;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2, 0.2, 1); // Draw polygon in blue
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(points[i][0], points[i][1]);
    }
    glEnd();
    glFlush();

    glColor3f(0, 1, 0); // Draw clipping window in green
    glBegin(GL_LINE_LOOP);
    glVertex2i(wxmin, wymin);
    glVertex2i(wxmax, wymin);
    glVertex2i(wxmax, wymax);
    glVertex2i(wxmin, wymax);
    glEnd();
    glFlush();
}

int BottomClipping(int e) {
    int k = 0;
    int t[10][2]; // Temporary storage for clipped points

    for (int i = 0; i < e; i++) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[(i + 1) % e][0], y2 = points[(i + 1) % e][1];

        if (y1 >= wymin && y2 >= wymin) {
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
        } else if (y1 < wymin && y2 >= wymin) {
            float x_intersect = x1 + (wymin - y1) * (x2 - x1) / (y2 - y1);
            t[k][0] = x_intersect;
            t[k][1] = wymin;
            k++;
            t[k][0] = x2;
            t[k][1] = y2;
            k++;
        } else if (y1 >= wymin && y2 < wymin) {
            float x_intersect = x1 + (wymin - y1) * (x2 - x1) / (y2 - y1);
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
            t[k][0] = x_intersect;
            t[k][1] = wymin;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    edge = k;
    return k;
}

int TopClipping(int e) {
    int k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[(i + 1) % e][0], y2 = points[(i + 1) % e][1];

        if (y1 <= wymax && y2 <= wymax) {
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
        } else if (y1 > wymax && y2 <= wymax) {
            float x_intersect = x1 + (wymax - y1) * (x2 - x1) / (y2 - y1);
            t[k][0] = x_intersect;
            t[k][1] = wymax;
            k++;
            t[k][0] = x2;
            t[k][1] = y2;
            k++;
        } else if (y1 <= wymax && y2 > wymax) {
            float x_intersect = x1 + (wymax - y1) * (x2 - x1) / (y2 - y1);
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
            t[k][0] = x_intersect;
            t[k][1] = wymax;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    edge = k;
    return k;
}

int LeftClipping(int e) {
    int k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[(i + 1) % e][0], y2 = points[(i + 1) % e][1];

        if (x1 >= wxmin && x2 >= wxmin) {
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
        } else if (x1 < wxmin && x2 >= wxmin) {
            float y_intersect = y1 + (wxmin - x1) * (y2 - y1) / (x2 - x1);
            t[k][0] = wxmin;
            t[k][1] = y_intersect;
            k++;
            t[k][0] = x2;
            t[k][1] = y2;
            k++;
        } else if (x1 >= wxmin && x2 < wxmin) {
            float y_intersect = y1 + (wxmin - x1) * (y2 - y1) / (x2 - x1);
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
            t[k][0] = wxmin;
            t[k][1] = y_intersect;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    edge = k;
    return k;
}

int RightClipping(int e) {
    int k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[(i + 1) % e][0], y2 = points[(i + 1) % e][1];

        if (x1 <= wxmax && x2 <= wxmax) {
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
        } else if (x1 > wxmax && x2 <= wxmax) {
            float y_intersect = y1 + (wxmax - x1) * (y2 - y1) / (x2 - x1);
            t[k][0] = wxmax;
            t[k][1] = y_intersect;
            k++;
            t[k][0] = x2;
            t[k][1] = y2;
            k++;
        } else if (x1 <= wxmax && x2 > wxmax) {
            float y_intersect = y1 + (wxmax - x1) * (y2 - y1) / (x2 - x1);
            t[k][0] = x1;
            t[k][1] = y1;
            k++;
            t[k][0] = wxmax;
            t[k][1] = y_intersect;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    edge = k;
    return k;
}

void P_C() {
    Draw();
}

void goMenu(int value) {
    switch (value) {
        case 1:
            edge = LeftClipping(edge);
            Draw();
            break;
        case 2:
            edge = RightClipping(edge);
            Draw();
            break;
        case 3:
            edge = TopClipping(edge);
            Draw();
            break;
        case 4:
            edge = BottomClipping(edge);
            Draw();
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    cout << "Enter No of edges of polygon: ";
    cin >> edge;
    for (int i = 0; i < edge; i++) {
        cout << "Enter point " << i << " (x space y): ";
        cin >> points[i][0] >> points[i][1];
    }
    points[edge][0] = points[0][0];
    points[edge][1] = points[0][1];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Polygon Clipping");

    init();
    glutCreateMenu(goMenu);
    glutAddMenuEntry("Left", 1);
    glutAddMenuEntry("Right", 2);
    glutAddMenuEntry("Top", 3);
    glutAddMenuEntry("Bottom", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(P_C);
    glutMainLoop();
    return 0;
}
