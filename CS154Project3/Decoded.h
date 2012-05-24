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

struct Decoded: public Fetched{
    int readReg1;
    int readReg2;
//    unsigned int calculatedBranchResult;
    bool branchResult;
    bool stall;
    unsigned int getProperBranchPC();
    Decoded(Fetched*);
    ~Decoded();
};

#endif
