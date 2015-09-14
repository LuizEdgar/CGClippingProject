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
    vector<Line2D> *environmentLines;

    
    float xMax, yMax, xMin, yMin;
    float x0, y0, x1, y1;
    double x, y;
    
    double t0, t1;
    double p,q,r;
    double xDelta, yDelta;
    
    bool finished, rejected, initialized;
    
    int edge;
    int currentStep;
    
public:
    
    LiangBarksy(Drawer *drawer, vector<Line2D> *environmentLines, vector<Point2D> *points, vector<Point2D> *auxPoints, double xMin, double yMin, double xMax, double yMax){
        this->drawer = drawer;
        this->points = points;
        this->auxPoints = auxPoints;
        this->environmentLines = environmentLines;
        
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
        
        finished = false;
        rejected = false;
        initialized = true;
        
        edge = 0;
        currentStep = 0;
    }
    
    LiangBarksy(){
        finished = false;
        rejected = false;
        initialized = false;
    }
    
    void next(){
        switch (currentStep) {
            case 0:
                if (edge < 4 && !rejected) {
                    stepEdge();
                }else{
                    finished = true;
                    markEnd();
                }
                break;
            case 1:
                
                break;
            case 2:
                
                break;
            default:
                break;
        }
    }
    
    void markEnd(){
        Color lineColor = Color(0.05, 0.55, 0.85, 1);

        for (int i = 0; i < environmentLines->size(); i++) {
            environmentLines->at(i).setColor(lineColor);
            environmentLines->at(i).setIsDashed(true);
        }

        if (!rejected) {
            printf("Fim, temos nova reta.\n");

            points->at(0).setX(x0 + t0*xDelta);
            points->at(0).setY(y0 + t0*yDelta);
            points->at(1).setX(x0 + t1*xDelta);
            points->at(1).setY(y0 + t1*yDelta);
        }else{
            printf("Fim, tudo rejeitado.\n");
        }
        
        currentStep++;
    }
    
    void stepEdge(){
        
        Color blue = Color(0.5, 0.4, 0.9, 1);
        Color gray = Color(0.8, 0.8, 0.8, 1);
        Color red = Color(1.0, 0.4, 0.4, 1);
        Color lineColor = Color(0.05, 0.55, 0.85, 1);

        
        for (int i = 0; i < environmentLines->size(); i++) {
            environmentLines->at(i).setColor(lineColor);
            environmentLines->at(i).setIsDashed(true);
        }
        
        environmentLines->at(edge).setColor(red);
        environmentLines->at(edge).setIsDashed(false);
        
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
            return;
        }
        
        

        if (p < 0){
            if(r > t1){
                rejected = true;
                return;
                
            }else if (r > t0){
                printf("p < 0 -> Atualizando t0 = %lf para %lf pelo edge = %d.\n", t0, r, edge);
                auxPoints->push_back(Point2D(x0 + r*xDelta, y0 + r*yDelta, 10, blue));
                t0 = r;
            }else{
                auxPoints->push_back(Point2D(x0 + r*xDelta, y0 + r*yDelta, 10, gray));
            }
        }else if (p > 0){
            if (r < t0) {
                rejected = true;
                return;
                
            }else if (r < t1){
                printf("p > 0 -> Atualizando t1 = %lf para %lf pelo edge = %d.\n", t1, r, edge);
                auxPoints->push_back(Point2D(x0 + r*xDelta, y0 + r*yDelta, 10, blue));
                t1 = r;
            }else{
                auxPoints->push_back(Point2D(x0 + r*xDelta, y0 + r*yDelta, 10, gray));
            }
        }
        
        edge++;
    }
    
    bool isFinished(){
        return finished;
    }
    
    bool isRejected(){
        return rejected;
    }
    
    bool isInitialized(){
        return initialized;
    }

    
};
