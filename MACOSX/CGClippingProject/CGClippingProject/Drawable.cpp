//
//  Drawable.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/2/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Drawable.h"

void Drawable::draw(){}

void Drawable::setColor(Color color){
    this->color = color;
};

Color Drawable::getColor(){
    return color;
}
