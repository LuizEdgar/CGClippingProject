//
//  Color.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/2/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include <stdio.h>

class Color {
    
public:
    
    float r;
    float g;
    float b;
    float a;
    
    Color(){
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
    }
    
    Color(float r, float g, float b, float a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

};