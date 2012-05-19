//
//  Decoded.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_Decoded_h
#define CS154Project3_Decoded_h
#include "Fetched.h"

struct Decoded{
    Fetched* fetched;
    ~Decoded();
    int read1;
    int read2;
    bool stall;
    bool branch;
};

#endif
