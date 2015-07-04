//
//  Point2D.h
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#ifndef CGClippingProject_Point2D_h
#define CGClippingProject_Point2D_h

#include "Drawable.h"

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
    
    float getX();
    
    void setX(float x);
    
    float getY();
    
    void setY(float y);
    
    float getWidth();
    
    void setWidth(float width);
    
    bool getIsSmooth();
    
    void setIsSmooth(bool isSmooth);
    
    void draw();
    
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

#endif
