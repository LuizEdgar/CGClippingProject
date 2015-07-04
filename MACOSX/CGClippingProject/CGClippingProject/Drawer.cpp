//
//  Drawer.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/1/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#import "Drawable.h"

class Drawer {
    
    vector<Drawable*> drawables;

public:
    Drawer(){}
    
    void append(Drawable *drawable){
        drawables.push_back(drawable);
    };
    
    void frame(){
        while (!drawables.empty()) {
            Drawable *d = drawables.front();
            d->draw();
            drawables.erase (drawables.begin());
            delete d;
        }
    }
};