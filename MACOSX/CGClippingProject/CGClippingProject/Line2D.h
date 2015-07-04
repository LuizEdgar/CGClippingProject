//
//  Line2D.h
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#ifndef CGClippingProject_Line2D_h
#define CGClippingProject_Line2D_h

#include "Point2D.h"

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
        this->width = 2.5;
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
    
    Point2D getStartPoint();
    
    Point2D getEndPoint();
    
    void setWidth(float width);
    
    void setStartPoint(Point2D startPoint);
    
    void setIsDashed(bool isDashed);
    
    void setEndPoint(Point2D endPoint);
    
    void setPointBySequencialPosition(int sequence, Point2D point);
    
    void draw();
    
};

#endif
