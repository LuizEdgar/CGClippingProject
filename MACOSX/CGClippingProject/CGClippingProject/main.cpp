//
//  main.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "CohenSutherlandStep.cpp"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

using namespace std;

bool environmentInitialized;

GLint mouseX,mouseY;

vector<Point2D> points;

vector<Point2D> auxPoints;

Square2D environmentSquare;
vector<Line2D> environmentLines;

float xMin;
float yMin;
float xMax;
float yMax;

Drawer drawer;

CohenSutherlandStep currentStep;

void appendEnvironment(){
    drawer.append(new Square2D(environmentSquare));
    
    for (int i=0; i < environmentLines.size(); i++) {
        drawer.append(new Line2D(environmentLines[i]));
    }
    
}

void appendReadyLine(){
    if (points.size() >1) {
        Line2D *l = new Line2D(points[0], points[1]);
        
        if (currentStep.isFinished() && currentStep.isRejected()){
            l->setIsDashed(true);
            l->setWidth(1);
        }
        
        drawer.append(l);
    }
    
    for (int i=0; i < auxPoints.size(); i = i+2) {
        Line2D *l = new Line2D(auxPoints[i], auxPoints[i+1]);
        l->setIsDashed(true);
        l->setWidth(1);
        drawer.append(l);
    }
}

void appendReadyPoints(){
    for (int i=0; i < auxPoints.size(); i++) {
        drawer.append(new Point2D(auxPoints[i]));
    }
    
    for (int i=0; i < points.size(); i++) {
        drawer.append(new Point2D(points[i]));
    }
}


void drawCallback(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    appendEnvironment();
    appendReadyLine();
    appendReadyPoints();
    
    drawer.frame();
    
    glSwapAPPLE();
}

void mouseCallback(int button, int state,
                   int x, int y){
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {        
        mouseX = x;
        mouseY = y;
        
        if (points.size() < 2) {
            printf("Ponto setado: (%d,%d)\n", x, y);

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
    printf("Cohen Sutherland Clipping\n");
    printf("1. Crie dois pontos na tela com o mouse.\n");
    printf("2. Aperte 'n' para executar uma iteração do algoritmo.\n");
    printf("Aperte 'r' para recomeçar.\n");
    
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    int verticalPadding = 150;
    int horizontalPadding = 250;
    
    Color gray = Color(0.05, 0.55, 0.85, 1);
    
    Line2D left = Line2D(Point2D(horizontalPadding, 0), Point2D(horizontalPadding, WINDOW_HEIGHT));
    left.setIsDashed(true);
    left.setColor(gray);
    left.setWidth(2.0);
    
    environmentLines.push_back(left);
    
    Line2D right = Line2D(Point2D(WINDOW_WIDTH - horizontalPadding, 0), Point2D(WINDOW_WIDTH - horizontalPadding, WINDOW_HEIGHT));
    right.setIsDashed(true);
    right.setColor(gray);
    right.setWidth(2.0);
    
    environmentLines.push_back(right);
    
    Line2D top = Line2D(Point2D(0, verticalPadding), Point2D(WINDOW_WIDTH, verticalPadding));
    top.setIsDashed(true);
    top.setColor(gray);
    top.setWidth(2.0);
    
    environmentLines.push_back(top);
    
    Line2D bottom = Line2D(Point2D(0, WINDOW_HEIGHT - verticalPadding), Point2D(WINDOW_WIDTH, WINDOW_HEIGHT - verticalPadding));
    bottom.setIsDashed(true);
    bottom.setColor(gray);
    bottom.setWidth(2.0);
    environmentLines.push_back(bottom);
    
    xMin = 0 + horizontalPadding;
    yMin = 0 + verticalPadding;
    xMax = WINDOW_WIDTH - horizontalPadding;
    yMax = WINDOW_HEIGHT - verticalPadding;
    
    environmentSquare = Square2D(Point2D(xMin, yMin), Point2D(xMax, yMax), Color(0.92, 0.37 , 0.37, 0.4));
}


void keyboardCallback(unsigned char key, int x, int y){
    if (key == 'r'){
        printf("Resetando algoritmo...\n");
        
        points.clear();
        auxPoints.clear();
        currentStep = CohenSutherlandStep();
        glutPostRedisplay();
    }
    
    if (key == 'n'){
        if (points.size() > 1) {
            if (currentStep.isFinished()) {
                currentStep = CohenSutherlandStep(&drawer, &points, &auxPoints, xMin, yMin, xMax, yMax);
            }
            currentStep.next();
            
            glutPostRedisplay();
        }else{
            printf("Selecione mais um ponto para iniciar o algoritmo.\n");
        }
        
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