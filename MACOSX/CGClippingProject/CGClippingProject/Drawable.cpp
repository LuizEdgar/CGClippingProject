//
//  Drawable.cpp
//  CGClippingProject
//
//  Created by Luiz Edgar on 7/2/15.
//  Copyright (c) 2015 Luiz Edgar. All rights reserved.
//

#include <stdio.h>

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

#include "Color.cpp"

class Drawable {
public:
    virtual void draw() = 0;
};