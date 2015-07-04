//
//  main.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Square2D.h"
#include "Line2D.h"
#include "Drawer.cpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

using namespace std;

bool environmentInitialized;

GLint mouseX,mouseY;

vector<Point2D> points;

Square2D environmentSquare;
vector<Line2D> environmentLines;

float xMin;
float yMin;
float xMax;
float yMax;

Drawer drawer;

void appendEnvironment(){
    drawer.append(new Square2D(environmentSquare));
    
    for (int i=0; i < environmentLines.size(); i++) {
        drawer.append(new Line2D(environmentLines[i]));
    }
    
}

void appendReadyLine(){
    if (points.size() >1) {
        drawer.append(new Line2D(points[0], points[1]));
    }
}

void appendReadyPoints(){
    for (int i=0; i < points.size(); i++) {
        drawer.append(new Point2D(points[i]));
    }
}


void drawCallback(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    
    appendReadyLine();
    appendReadyPoints();
    appendEnvironment();
    
    drawer.frame();
    
    glSwapAPPLE();
}

void mouseCallback(int button, int state,
                   int x, int y){
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "(" << x << ", " << y << ")\n";
        
        mouseX = x;
        mouseY = y;
        
        if (points.size() < 2) {
            Point2D point = Point2D(x, WINDOW_HEIGHT - y);
            point.setIsSmooth(true);
            point.setWidth(10);
            point.draw();
            
            points.push_back(point);
            
            glutPostRedisplay();
        }
        
    }
    
}

void init(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    int verticalPadding = 150;
    int horizontalPadding = 250;
    
    Line2D left = Line2D(Point2D(horizontalPadding, 0), Point2D(horizontalPadding, WINDOW_HEIGHT));
    left.setIsDashed(true);
    left.setWidth(2.0);
    
    environmentLines.push_back(left);
    
    Line2D right = Line2D(Point2D(WINDOW_WIDTH - horizontalPadding, 0), Point2D(WINDOW_WIDTH - horizontalPadding, WINDOW_HEIGHT));
    right.setIsDashed(true);
    right.setWidth(2.0);
    
    environmentLines.push_back(right);
    
    Line2D top = Line2D(Point2D(0, verticalPadding), Point2D(WINDOW_WIDTH, verticalPadding));
    top.setIsDashed(true);
    top.setWidth(2.0);
    
    environmentLines.push_back(top);
    
    Line2D bottom = Line2D(Point2D(0, WINDOW_HEIGHT - verticalPadding), Point2D(WINDOW_WIDTH, WINDOW_HEIGHT - verticalPadding));
    bottom.setIsDashed(true);
    bottom.setWidth(2.0);
    environmentLines.push_back(bottom);
    
    xMin = 0 + horizontalPadding;
    yMin = 0 + verticalPadding;
    xMax = WINDOW_WIDTH - horizontalPadding;
    yMax = WINDOW_HEIGHT - verticalPadding;
    
    environmentSquare = Square2D(Point2D(xMin, yMin), Point2D(xMax, yMax), Color(1, 0 ,0, 0.5));
}

void keyboardCallback(unsigned char key, int x, int y){
    if (key == 'r'){
        points.clear();
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
    
    gluOrtho2D(0, (GLdouble)w,  0, (GLdouble)h);
}

int main( int argc, char** argv){
    drawer = Drawer();
    
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