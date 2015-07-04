//
//  Point2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Drawable.cpp"

class Point2D : public Drawable{
    float x;
    float y;
    float width;
    bool isSmooth;
    Color color;
    
public:
    Point2D(){
        this->x = -1;
        this->y = -1;
        this->width = 4;
        this->isSmooth = false;
        this->color = Color(0.0, 0.0, 0.0, 1.0);
    }
    
    Point2D(float x, float y) : Point2D(){
        Point2D();
        this->x = x;
        this->y = y;
    }
    
    Point2D(float x, float y, float width, Color color) : Point2D(x, y){
        Point2D();
        this->x = x;
        this->y = y;
        this->width = width;
        this->color = color;
    }
    
    float getX(){
        return x;
    }
    
    void setX(float x){
        this->x = x;
    }
    
    float getY(){
        return y;
    }
    
    void setY(float y){
        this->y = y;
    }
    
    float getWidth(){
        return width;
    }
    
    void setWidth(float width){
        this->width = width;
    }
    
    bool getIsSmooth(){
        return isSmooth;
    }
    
    void setIsSmooth(bool isSmooth){
        this->isSmooth = isSmooth;
    }
    
    void draw(){
        
        glColor4f(color.r, color.g, color.b, color.a);
        
        if (this->isSmooth) {
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        }else{
            glDisable(GL_POINT_SMOOTH);
        }
        
        glPointSize(this->width);
        
        glBegin(GL_POINTS);
        glVertex2i(this->x, this->y);
        
        glEnd();
        
    }
    
//    void printCircle(Point2D center, float radius, int num_segments)
//    {
//        glColor4f(0.0, 0.0, 1.0, 1.0);
//        
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity();
//        glTranslatef(center.getX(), center.getY(), 0.0f);
//        static const int circle_points = 100;
//        static const float angle = 2.0f * 3.1416f / circle_points;
//        
//        // this code (mostly) copied from question:
//        glBegin(GL_POLYGON);
//        double angle1=0.0;
//        glVertex2d(radius * cos(0.0) , radius * sin(0.0));
//        int i;
//        for (i=0; i<circle_points; i++)
//        {
//            glVertex2d(radius * cos(angle1), radius *sin(angle1));
//            angle1 += angle;
//        }
//        glEnd();
//        glPopMatrix();
//    }

};