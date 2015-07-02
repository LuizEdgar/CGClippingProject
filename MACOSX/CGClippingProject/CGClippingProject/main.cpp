//
//  main.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Line.cpp"

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC

#include <GLUT/glut.h>

#else
// Unsupported platform
#endif
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

using namespace std;

bool environmentInitialized;

GLint mouseX,mouseY;

Point2D points[2];
int counter;

int spin;

void drawEnvironment(){
    glColor4f(1.0, 0, 0, 0.5);
    
    int verticalPadding = 150;
    int horizontalPadding = 250;
    
    glBegin(GL_QUADS);
    glVertex3f(0 + horizontalPadding, 0 + verticalPadding, 0.0); // top left
    glVertex3f(0 + horizontalPadding, WINDOW_HEIGHT - verticalPadding, 0.0); // bottom left
    glVertex3f(WINDOW_WIDTH - horizontalPadding, WINDOW_HEIGHT - verticalPadding, 0.0); // bottom right
    glVertex3f(WINDOW_WIDTH - horizontalPadding, 0 + verticalPadding, 0.0); // top right
    glEnd();
}

void printLine(Line line){
    glLineWidth(3);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    
    glBegin(GL_LINES);
    
    glVertex2i(line.getStartPoint().getX(), line.getStartPoint().getY());
    glVertex2i(line.getEndPoint().getX(), line.getEndPoint().getY());
    
    glEnd();
}

void printPoint(Point2D point){
    glPointSize(10.0);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    
    glBegin(GL_POINTS);
    
    glVertex2i(point.getX(), point.getY());
    
    glEnd();
}

void printCircle(Point2D center, float radius, int num_segments)
{
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    
    glPointSize(100);
    glBegin(GL_POINTS);
    glVertex2i(center.getX(), center.getY());
    
    glEnd();

    /// other
    
//    
//    glColor4f(0.0, 0.0, 1.0, 1.0);
//    
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    glTranslatef(center.getX(), center.getY(), 0.0f);
//    static const int circle_points = 100;
//    static const float angle = 2.0f * 3.1416f / circle_points;
//    
//    // this code (mostly) copied from question:
//    glBegin(GL_POLYGON);
//    double angle1=0.0;
//    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
//    int i;
//    for (i=0; i<circle_points; i++)
//    {
//        glVertex2d(radius * cos(angle1), radius *sin(angle1));
//        angle1 += angle;
//    }
//    glEnd();
//    glPopMatrix();

///other
    
//    //filled circle
//    float x1,y1,x2,y2;
//    float angle;
//    
//    x1 = center.getY(),y1=center.getY();
//    glColor3f(0.0,0.0,0.6);
//    
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(x1,y1);
//    
//    for(angle=0.0f ; angle<=2*3.14159 ; angle+=0.2)
//    {
//        x2 = x1+sin(angle)*radius;
//        y2 = y1+cos(angle)*radius;
//        glVertex2f(x2,y2);
//    }
//    
//    glEnd();

}

void testSpin(){
    glPushMatrix();
    
    //update spin
    spin += 1;
    if (spin > 100)
        spin = 0;
    // rotate
    
    int verticalPadding = 150;
    int horizontalPadding = 250;
    
    glBegin(GL_QUADS);
    glVertex3f(0 + horizontalPadding, 0 + verticalPadding, 0.0); // top left
    glVertex3f(0 + horizontalPadding, WINDOW_HEIGHT - verticalPadding, 0.0); // bottom left
    glVertex3f(WINDOW_WIDTH - horizontalPadding, WINDOW_HEIGHT - verticalPadding, 0.0); // bottom right
    glVertex3f(WINDOW_WIDTH - horizontalPadding, 0 + verticalPadding, 0.0); // top right
    
    glEnd();
    glPopMatrix();
    
}

void drawReadyPoints(){
    if (counter >= 0) {
        cout << "p0(" << points[0].getX() << ", " << points[0].getY() << ")\n";
//        printPoint(points[0]);
        printCircle(points[0], 10, 20);
    }

    if (counter > 0) {
        cout << "p1(" << points[1].getX() << ", " << points[1].getY() << ")\n";
//        printPoint(points[1]);
        printCircle(points[1], 10, 20);
    }
}

void drawReadyLine(){
    if (counter > 0) {
        printLine(Line(points[0], points[1]));
    }
}

void drawCallback(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawReadyLine();
    drawReadyPoints();
    drawEnvironment();
    
//    testSpin();
    
    glSwapAPPLE();
}

void mouseCallback(int button, int state,
                   int x, int y){

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "(" << x << ", " << y << ")\n";
        
        mouseX = x;
        mouseY = y;
        
        if (counter < 2) {
            points[++counter] = Point2D(x, y);
            
            if (counter == 1) {
                counter++;
            }
            
            glutPostRedisplay();
        }
        
    }
    
}

void init(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    counter = -1;
}

void keyboardCallback(unsigned char key, int x, int y){
    if (key == 'r'){
        counter = -1;
        glutPostRedisplay();
    }
    
    if (key == 'n'){
        glutPostRedisplay();
    }
    
    if (key == 'q'){
        exit(0);
    }
}

void resizeWindowCallback(GLsizei w, GLsizei h){
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    
    gluOrtho2D(0, (GLdouble)w,  (GLdouble)h, 0);
    
    
    //    if (h == 0) h = 1;
    
    //    if (w <= h)
    //        gluOrtho2D (0.0f, 250.0, 0.0f, 250.0f*h/w);
    //    else
    //        gluOrtho2D (0.0f, 250.0f*h/w, 0.0f, 250.0f);
    
    ////    gluOrtho2D(-1, 1, -1, 1);
    
}

int main( int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen–Sutherland");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(drawCallback);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);
    glutReshapeFunc(resizeWindowCallback);
    init();
    glutMainLoop();
}
//
//
//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}
