//
//  Memoried.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_Memoried_h
#define CS154Project3_Memoried_h
#include "Executed.h"

struct Memoried{
    Executed* executed;
    ~Memoried();
    int read;
};

#endif
