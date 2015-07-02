//
//  Point2D.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

class Point2D {
    int x;
    int y;
    
public:
    Point2D(){
        this->x = -1;
        this->y = -1;
    }
    
    Point2D(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }
};