//
//  fetch.h
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_fetch_h
#define Project1_fetch_h
#include "Decoder.h"
class Fetch{
    int* instructions;
    unsigned int pc;
    unsigned int maxPC;
    unsigned int length;
public:
    Fetch(char*);
    int nextInstruction();
    int programLength();
    unsigned int getPC();
    unsigned int getPCPlus4();
    void updatePC(Decoded* controlBits, bool zeroBit);
    int performFetch();
    bool isDone();
};


#endif
