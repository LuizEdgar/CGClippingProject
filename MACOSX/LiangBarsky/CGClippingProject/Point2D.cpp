//
//  Point2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Point2D.h"

float Point2D::getX(){
    return x;
}

void Point2D::setX(float x){
    this->x = x;
}

float Point2D::getY(){
    return y;
}

void Point2D::setY(float y){
    this->y = y;
}

float Point2D::getWidth(){
    return width;
}

void Point2D::setWidth(float width){
    this->width = width;
}

bool Point2D::getIsSmooth(){
    return isSmooth;
}

void Point2D::setIsSmooth(bool isSmooth){
    this->isSmooth = isSmooth;
}

void Point2D::draw(){
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
