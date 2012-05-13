//
//  Executed.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_Executed_h
#define CS154Project3_Executed_h
#include "Decoded.h"

struct Executed{
    int result;
    bool zeroBit;
    char writeReg;
    Decoded* decoded;
    ~Executed();
};

#endif
