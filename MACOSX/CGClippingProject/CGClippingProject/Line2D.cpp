//
//  Line2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/3/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Point2D.cpp"

class Line2D : public Drawable{
    Point2D start;
    Point2D end;
    
    Color color;
    
    float width;
    
    bool isDashed;
    bool isSmooth;
    
public:
    Line2D(){
        this->start = Point2D();
        this->end = Point2D();
        
        this->isDashed = false;
        this->width = 5;
        this->isSmooth = true;
        
        this->color = Color(0.0, 0.0, 0.0, 1.0);
    }
    
    Line2D(Point2D start, Point2D end) : Line2D(){
        this->start = start;
        this->end = end;
    }
    
    Line2D(Point2D start, Point2D end, float width) : Line2D(start, end){
        this->width = width;
    }
    
    Point2D getStartPoint(){
        return start;
    }
    
    Point2D getEndPoint(){
        return end;
    }
    
    void setWidth(float width){
        this->width = width;
    }
    
    void setStartPoint(Point2D startPoint){
        this->start = startPoint;
    }
    
    void setIsDashed(bool isDashed) {
        this->isDashed = isDashed;
    }
    
    void setEndPoint(Point2D endPoint){
        this->end = endPoint;
    }
    
    void setPointBySequencialPosition(int sequence, Point2D point){
        if (sequence == 0) {
            this->start = point;
        }else{
            this->end = point;
        }
    }
    
    void draw(){
        
        if (this->isSmooth) {
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        }else{
            glDisable(GL_LINE_SMOOTH);
        }
        
        if (this->isDashed) {
            glLineStipple(4, 0xAAAA);
            glEnable(GL_LINE_STIPPLE);
        }else{
            glDisable(GL_LINE_STIPPLE);
        }
        
        glLineWidth(this->width);
        glColor4f(color.r, color.g, color.b, color.a);
        
        glBegin(GL_LINES);
        
        glVertex2i(this->start.getX(), this->start.getY());
        glVertex2i(this->end.getX(), this->end.getY());
        
        glEnd();

    }
    
};

