//
//  Square2D.h
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#ifndef CGClippingProject_Square2D_h
#define CGClippingProject_Square2D_h

#include "Point2D.h"

class Square2D : public Drawable{
    Point2D start;
    Point2D end;
    
public:
    Square2D(){
        this->start = Point2D();
        this->end = Point2D();
        
        this->color = Color(0.0, 0.0, 0.0, 1.0);
    }
    
    Square2D(Point2D start, Point2D end, Color color) : Square2D(){
        this->start = start;
        this->end = end;
        
        this->color = color;
    }
    
    Point2D getStartPoint();
    
    Point2D getEndPoint();
    
    void setStartPoint(Point2D startPoint);
    
    void setEndPoint(Point2D endPoint);
    
    void setPointBySequencialPosition(int sequence, Point2D point);
    
    void draw();
};

#endif
