//
//  Square2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Square2D.h"

Point2D Square2D::getStartPoint(){
    return start;
}

Point2D Square2D::getEndPoint(){
    return end;
}

void Square2D::setStartPoint(Point2D startPoint){
    this->start = startPoint;
}

void Square2D::setEndPoint(Point2D endPoint){
    this->end = endPoint;
}

void Square2D::setPointBySequencialPosition(int sequence, Point2D point){
    if (sequence == 0) {
        this->start = point;
    }else{
        this->end = point;
    }
}

void Square2D::draw(){
    glColor4f(color.r, color.g, color.b, color.a);
    
    
    glBegin(GL_QUADS);
    glVertex2i(this->start.getX(), this->start.getY());
    glVertex2i(this->start.getX(), this->end.getY());
    glVertex2i(this->end.getX(), this->end.getY());
    glVertex2i(this->end.getX(), this->start.getY());
    glEnd();
    
}
