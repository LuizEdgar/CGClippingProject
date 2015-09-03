//
//  CohenShuterland.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include "Drawer.cpp"
#include "Square2D.h"
#include "Line2D.h"

class LiangBarksy {
    Drawer *drawer;
    
    vector<Point2D> *points;
    vector<Point2D> *auxPoints;
    
    float xMax, yMax, xMin, yMin;
    float x0, y0, x1, y1;
    double x, y;
    
    double t0, t1;
    double p,q,r;
    double xDelta, yDelta;
    
    bool finished, rejected;
    
public:
    
    LiangBarksy(Drawer *drawer, vector<Point2D> *points, vector<Point2D> *auxPoints, double xMin, double yMin, double xMax, double yMax){
        this->drawer = drawer;
        this->points = points;
        this->auxPoints = auxPoints;
        
        this->xMin = xMin;
        this->yMin = yMin;
        this->xMax = xMax;
        this->yMax = yMax;
        
        Point2D a = points->at(0);
        Point2D b = points->at(1);
        
        x0 = a.getX();
        y0 = a.getY();
        x1 = b.getX();
        y1 = b.getY();
        
        t0 = 0.0;
        t1 = 1.0;
        
        xDelta = x1 - x0;
        yDelta = y1 - y0;
        
        finished = true;
        rejected = false;
    }
    
    LiangBarksy(){
        finished = true;
        rejected = false;
    }
    
    void next(){
        int edge;
        
        for (edge = 0; edge<4 ; edge++){
           
            if(edge == 0){ //LEFT
                p = -xDelta;
                q = -(xMin - x0);
            }
            if(edge == 1){ //RIGHT
                p = xDelta;
                q = (xMax - x0);
            }
            if(edge == 2){ //BOTTOM
                p = -yDelta;
                q = -(yMin - y0);
            }
            if(edge == 3){ //TOP
                p = yDelta;
                q = (yMax - y0);
            }
            r = q/p;
            
            if (p == 0 && q < 0) {
                printf("Linha paralela.\n");

                rejected = true;
                finished = true;
                return;
            }
            
            if (p < 0){
                if(r > t1){
                    rejected = true;
                    finished = true;
                    return;

                }else if (r > t0){
                    printf("p < 0 -> Atualizando t0 = %lf para %lf pelo edge = %d.\n", t0, r, edge);
                    t0 = r;
                }
            }else if (p > 0){
                if (r < t0) {
                    rejected = true;
                    finished = true;
                    return;

                }else if (r < t1){
                    printf("p > 0 -> Atualizando t1 = %lf para %lf pelo edge = %d.\n", t1, r, edge);
                    t1 = r;
                }
            }
            
        }
        
        finished = true;
        
        if (!rejected) {
            points->at(0).setX(x0 + t0*xDelta);
            points->at(0).setY(y0 + t0*yDelta);
            points->at(1).setX(x0 + t1*xDelta);
            points->at(1).setY(y0 + t1*yDelta);
        }
        
    }
    
    bool isFinished(){
        return finished;
    }
    
    bool isRejected(){
        return rejected;
    }
    
};
