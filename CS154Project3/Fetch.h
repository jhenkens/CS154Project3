//
//  Fetch.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_fetch_h
#define Project1_fetch_h
#include "Fetched.h"
#include "Decoded.h"

class Fetch{
    int* instructions;
    unsigned int pc;
    unsigned int maxPC;
    unsigned int length;
    
    unsigned int branchPredFailedPC;
    bool prevBranchResults;
    bool branchPredictor;
    unsigned int branchPredDest;
    bool branchValid;
public:
    Fetch(char*);
    int nextInstruction();
    int programLength();
    unsigned int getPC();
    unsigned int getPCPlus4();
    void updatePC(Fetched*);
    void updatePC(Decoded*);
    Fetched* performFetch();
    bool isDone();
    void updateBranchPredictor(Decoded* decoded);
};
#endif
