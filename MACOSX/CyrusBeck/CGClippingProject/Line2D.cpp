//
//  Line2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/3/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Line2D.h"

Point2D Line2D::getStartPoint(){
    return start;
}

Point2D Line2D::getEndPoint(){
    return end;
}

void Line2D::setWidth(float width){
    this->width = width;
}

void Line2D::setStartPoint(Point2D startPoint){
    this->start = startPoint;
}

void Line2D::setIsDashed(bool isDashed) {
    this->isDashed = isDashed;
}

void Line2D::setEndPoint(Point2D endPoint){
    this->end = endPoint;
}

void Line2D::setPointBySequencialPosition(int sequence, Point2D point){
    if (sequence == 0) {
        this->start = point;
    }else{
        this->end = point;
    }
}

void Line2D::draw(){
    
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

