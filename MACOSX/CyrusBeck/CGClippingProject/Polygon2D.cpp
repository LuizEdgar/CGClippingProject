//
//  Polygon.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 8/5/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Polygon2D.h"

void Polygon2D::draw(){
    glColor4f(color.r, color.g, color.b, color.a);
    
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < this->points.size(); i++) {
        glVertex2f(points[i].getX(), points[i].getY());
    }
    glEnd();
    
}
