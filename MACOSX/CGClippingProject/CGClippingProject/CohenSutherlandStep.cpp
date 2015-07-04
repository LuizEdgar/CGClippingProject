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

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

// ASSUME THAT xmax, xmin, ymax and ymin are global constants.

class CohenSutherlandStep {
    Drawer *drawer;
    
    vector<Point2D> *points;
    vector<Point2D> *auxPoints;
    
    float xMax, yMax, xMin, yMin;
    float x0, y0, x1, y1;
    double x, y;
    
    OutCode outcode0, outcode1, outcodeOut;
    
    int step = 0;
    
    Point2D newLineStart;
    
    bool finished = false;
    bool rejected = false;
    
    OutCode computeOutCode(double x, double y)
    {
        OutCode code;
        
        code = INSIDE;          // initialised as being inside of clip window
        
        if (x < xMin)           // to the left of clip window
            code |= LEFT;
        else if (x > xMax)      // to the right of clip window
            code |= RIGHT;
        if (y < yMin)           // below the clip window
            code |= BOTTOM;
        else if (y > yMax)      // above the clip window
            code |= TOP;
        
        return code;
    }
    
    //PASSO 0
    void selecionarPonto(){
        bool accept = false;
        
        //    while (true) {
        if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
            accept = true;
            
            //OPENGL
            
            Color transparent = Color(0, 0, 0, 0);
            
            
            printf("Reta aceita.\n");
            
            for (int i=0; i < points->size(); i++) {
                points->at(i).setColor(transparent);
            }
            
            finished = true;
            
            //OPENGL
            
            //            break;
        } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
            
            //OPENGL
            
            Color gray = Color(0.8, 0.8, 0.8, 1);
            
            for (int i=0; i < points->size(); i++) {
                points->at(i).setColor(gray);
            }
            
            printf("Reta rejeitada.\n");
            
            finished = true;
            rejected = true;
            
            //OPENGL
            
            //            break;
        } else {
            
            // At least one endpoint is outside the clip rectangle; pick it.
            outcodeOut = outcode0 ? outcode0 : outcode1;
            
            step++;
            
            if (outcodeOut == outcode0) {
                points->at(0).setColor(Color(1,0,0,1));
            }else{
                points->at(1).setColor(Color(1,0,0,1));
            }
        }
    }
    
    void criarNovoPonto(){
        points->at(0).setColor(Color(0,0,0,1));
        points->at(1).setColor(Color(0,0,0,1));
        
        
        // Now find the intersection point;
        // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
        if (outcodeOut & TOP) {           // point is above the clip rectangle
            x = x0 + (x1 - x0) * (yMax - y0) / (y1 - y0);
            y = yMax;
        } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
            x = x0 + (x1 - x0) * (yMin - y0) / (y1 - y0);
            y = yMin;
        } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
            y = y0 + (y1 - y0) * (xMax - x0) / (x1 - x0);
            x = xMax;
        } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
            y = y0 + (y1 - y0) * (xMin - x0) / (x1 - x0);
            x = xMin;
        }
        
        printf("Novo ponto calculado: (%lf, %lf)\n",x,y);
        
        Point2D point = Point2D(x, y);
        point.setColor(Color(1,0,0,1));
        points->push_back(point);
        
        step++;
    }
    
    void pontilharReta(){
        
        Color gray = Color(0.8, 0.8, 0.8, 1);
        
        if (outcodeOut == outcode0) {
            auxPoints->push_back(Point2D(x0, y0, 10, gray));
            
            points->at(0).setX(x);
            points->at(0).setY(y);
            
            outcode0 = computeOutCode(x0, y0);
        } else {
            auxPoints->push_back(Point2D(x1, y1, 10, gray));
            
            points->at(1).setX(x);
            points->at(1).setY(y);
            
            outcode1 = computeOutCode(x1, y1);
        }
        
        
        points->pop_back();
        
        auxPoints->push_back(Point2D(x, y, 10, Color(0,0,0,0)));
        
        step++;
        finished = true;
    }
    
public:
    
    CohenSutherlandStep(){
        finished = true;
    }
    
    CohenSutherlandStep(Drawer *drawer, vector<Point2D> *points, vector<Point2D> *auxPoints, double xMin, double yMin, double xMax, double yMax){
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
        
        // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
        outcode0 = computeOutCode(x0, y0);
        outcode1 = computeOutCode(x1, y1);
    }
    
    
    // Cohen–Sutherland clipping algorithm clips a line from
    // P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
    // diagonal from (xmin, ymin) to (xmax, ymax).
    void next()
    {
        switch (step) {
            case 0:
                selecionarPonto();
                break;
            case 1:
                criarNovoPonto();
                break;
            case 2:
                pontilharReta();
                break;
                
            default:
                break;
        }
        
    }
    
    bool isFinished(){
        return finished;
    }
    
    bool isRejected(){
        return rejected;
    }
    //    }
    //    if (accept) {
    //        // Following functions are left for implementation by user based on
    //        // their platform (OpenGL/graphics.h etc.)
    //        //        DrawRectangle(xmin, ymin, xmax, ymax);
    //        //        LineSegment(x0, y0, x1, y1);
    //
    //    }
    
    
};
