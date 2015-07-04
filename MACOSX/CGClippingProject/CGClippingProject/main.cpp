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

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

// ASSUME THAT xmax, xmin, ymax and ymin are global constants.

OutCode ComputeOutCode(double x, double y)
{
    OutCode code;
    
    code = INSIDE;          // initialised as being inside of clip window
    
    if (x < xMin)           // to the left of clip window
        code |= LEFT;
    else if (x > xMax)      // to the right of clip window
        code |= RIGHT;
    if (y < yMin)           // below the clip window
        code |= BOTTOM;
    else if (y > yMax)      // above the clip window
        code |= TOP;
    
    return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (xmin, ymin) to (xmax, ymax).
void CohenSutherlandLineClipAndDraw(Point2D a, Point2D b)
{
    double x0 = a.getX(), y0 = a.getY(), x1 = b.getX(), y1 = b.getY();
    
    // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
    OutCode outcode0 = ComputeOutCode(x0, y0);
    OutCode outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;
    
    while (true) {
        if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
            accept = true;
            
            //OPENGL
            
            Color green = Color(0, 1 , 0, 1);
            
            for (int i=0; i < points.size(); i++) {
                points[i].setColor(green);
            }
            
            //OPENGL
            
            break;
        } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
            
            //OPENGL
            
            Color red = Color(1, 0 , 0, 1);
            
            for (int i=0; i < points.size(); i++) {
                points[i].setColor(red);
            }
                        
            //OPENGL
            
            break;
        } else {
            // failed both tests, so calculate the line segment to clip
            // from an outside point to an intersection with clip edge
            double x, y;
            
            // At least one endpoint is outside the clip rectangle; pick it.
            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;
            
            // Now find the intersection point;
            // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
            if (outcodeOut & TOP) {           // point is above the clip rectangle
                x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
                y = yMax;
            } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
                x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
                y = yMin;
            } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
                y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
                x = xMax;
            } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
                y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
                x = xMin;
            }
            
            // Now we move outside point to intersection point to clip
            // and get ready for next pass.
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }
    if (accept) {
        // Following functions are left for implementation by user based on
        // their platform (OpenGL/graphics.h etc.)
        //        DrawRectangle(xmin, ymin, xmax, ymax);
        //        LineSegment(x0, y0, x1, y1);
        
    }
}

void keyboardCallback(unsigned char key, int x, int y){
    if (key == 'r'){
        points.clear();
        glutPostRedisplay();
    }
    
    if (key == 'n'){
        if (points.size() > 1) {
            CohenSutherlandLineClipAndDraw(points[0], points[1]);
        }
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