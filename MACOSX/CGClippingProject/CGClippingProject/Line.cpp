//
//  Line.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Point2D.cpp"

class Line {
    Point2D start;
    Point2D end;
    
public:
    Line(){
        this->start = Point2D();
        this->end = Point2D();
    }
    
    Line(Point2D start, Point2D end){
        this->start = start;
        this->end = end;
    }
    
    Point2D getStartPoint(){
        return start;
    }
    
    Point2D getEndPoint(){
        return end;
    }
    
    void setStartPoint(Point2D startPoint){
        this->start = startPoint;
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
    
};
