//
//  main.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "CyrusBeck.cpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

using namespace std;

bool environmentInitialized;

Drawer drawer;
vector<Line2D> environmentLines;

vector<Point2D> points;

GLint mouseX,mouseY;

Line2D getInfiniteLine(Point2D start, Point2D end){
    
    float m = (end.getY() - start.getY()) / (end.getX() - start.getX());
    float b = start.getY() - m * start.getX();
    
    if (start.getX() == end.getX()) {
        start.setY(0);
        end.setY(WINDOW_HEIGHT);
    }else if (start.getY() == end.getY()){
        start.setX(0);
        end.setX(WINDOW_WIDTH);
    }else if (start.getX() < end.getX()){
        if (start.getY() < end.getY()) {
            start.setX(0);
            start.setY(b);
            
            end.setX((WINDOW_HEIGHT - b)/m);
            end.setY(WINDOW_HEIGHT);
        }else{
            start.setX(0);
            start.setY(b);
            
            end.setX(-b/m);
            end.setY(0);
        }
    }else{
        if (start.getY() < end.getY()) {
            start.setX(0);
            start.setY(b);
            
            end.setX(WINDOW_WIDTH);
            end.setY(m * WINDOW_WIDTH + b);
        }else{
            start.setX(-b/m);
            start.setY(0);
            
            end.setX(WINDOW_WIDTH);
            end.setY(m * WINDOW_WIDTH + b);
        }
    }
    
    return Line2D(start, end);
}

void calcularNormal (Point2D i, Point2D j)
{
//
//    Point2D v;
//    
//        n[i].x = -(p.pt[j].y - p.pt[i].y)/(p.pt[j].x - p.pt[i].x);
//        
//        n[i].y = 1.0;
//        v.x = p.pt[k].x - p.pt[i].x;
//        
//        v.y = p.pt[k].y - p.pt[i].y;
//        
//        if (DotProduct (n[i],v) > 0)    //
//            
//        { n[i].x *= -1;
//            n[i].y  = -1;
//        }
}

void appendEnvironment(){
    
    for (int i=0; i < environmentLines.size(); i++) {
        drawer.append(new Line2D(environmentLines[i]));
    }
    
}

void appendReadyPoints(){
    for (int i=0; i < points.size(); i++) {
        drawer.append(new Point2D(points[i]));
    }
}


void appendReadyLine(){
    if (points.size() >1) {
        Line2D *l = new Line2D(points[0], points[1]);
        drawer.append(l);
    }
    
}

void drawCallback(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    appendEnvironment();
    appendReadyPoints();
    appendReadyLine();
    
    drawer.frame();
    
    glSwapAPPLE();
}

void mouseCallback(int button, int state,
                   int x, int y){
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
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
    printf("Cyrus-Beck Clipping\n");
    printf("1. Crie dois pontos na tela com o mouse.\n");
    printf("2. Aperte 'n' para executar uma iteração do algoritmo.\n");
    printf("Aperte 'r' para recomeçar.\n");
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Color gray = Color(0.05, 0.55, 0.85, 0.2);
    
    Point2D a = Point2D((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - 100);
    Point2D b = Point2D((WINDOW_WIDTH / 2) + 100, (WINDOW_HEIGHT / 2) - 50);
    Point2D c = Point2D((WINDOW_WIDTH / 2) + 100, (WINDOW_HEIGHT / 2) + 50);
    Point2D d = Point2D((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) + 100);
    Point2D e = Point2D((WINDOW_WIDTH / 2) - 100, (WINDOW_HEIGHT / 2) + 50);
    Point2D f = Point2D((WINDOW_WIDTH / 2) - 100, (WINDOW_HEIGHT / 2) - 50);
    
    Line2D ab = getInfiniteLine(a, b);
    ab.setIsDashed(true);
    ab.setColor(gray);
    ab.setWidth(2.0);
    
    Line2D bc = getInfiniteLine(b, c);
    bc.setIsDashed(true);
    bc.setColor(gray);
    bc.setWidth(2.0);
    
    Line2D cd = getInfiniteLine(c, d);
    cd.setIsDashed(true);
    cd.setColor(gray);
    cd.setWidth(2.0);
    
    Line2D de = getInfiniteLine(d, e);
    de.setIsDashed(true);
    de.setColor(gray);
    de.setWidth(2.0);
    
    Line2D ef = getInfiniteLine(e, f);
    ef.setIsDashed(true);
    ef.setColor(gray);
    ef.setWidth(2.0);
    
    Line2D fa = getInfiniteLine(f, a);
    fa.setIsDashed(true);
    fa.setColor(gray);
    fa.setWidth(2.0);
    
    Line2D abFill = Line2D(a, b);
    Line2D bcFill = Line2D(b, c);
    Line2D cdFill = Line2D(c, d);
    Line2D deFill = Line2D(d, e);
    Line2D efFill = Line2D(e, f);
    Line2D faFill = Line2D(f, a);
    
    environmentLines.push_back(ab);
    environmentLines.push_back(bc);
    environmentLines.push_back(cd);
    environmentLines.push_back(de);
    environmentLines.push_back(ef);
    environmentLines.push_back(fa);
    
    environmentLines.push_back(abFill);
    environmentLines.push_back(bcFill);
    environmentLines.push_back(cdFill);
    environmentLines.push_back(deFill);
    environmentLines.push_back(efFill);
    environmentLines.push_back(faFill);
    
}


void keyboardCallback(unsigned char key, int x, int y){
    if (key == 'r'){
        printf("Resetando algoritmo...\n");
        
        points.clear();
        glutPostRedisplay();
    }
    
    if (key == 'n'){
          
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
    glutCreateWindow("Cyrus–Beck");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(drawCallback);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);
    glutReshapeFunc(resizeWindowCallback);
    init();
    glutMainLoop();
}