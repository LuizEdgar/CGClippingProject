//
//  Drawable.h
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/4/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#ifndef CGClippingProject_Drawable_h
#define CGClippingProject_Drawable_h


#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC

#include <GLUT/glut.h>

#else
// Unsupported platform
#endif
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

#include "Color.h"

using namespace std;

class Drawable {
public:
    virtual void draw();
};

#endif
