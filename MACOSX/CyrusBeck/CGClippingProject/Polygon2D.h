//
//  Polygon.h
//  CGClippingProject
//
//  Created by Luiz Edgar on 8/5/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#ifndef __CGClippingProject__Polygon__
#define __CGClippingProject__Polygon__

#include "Point2D.h"

class Polygon2D : public Drawable {
    
    vector<Point2D> points;
    
public:
    Polygon2D(){
        this->color = Color(0.0, 0.0, 0.0, 1.0);
    }
    
    Polygon2D(vector<Point2D> points, Color color) : Polygon2D(){
        this->points = points;
        this->color = color;
    }
    
    void draw();
    
};

#endif /* defined(__CGClippingProject__Polygon__) */
