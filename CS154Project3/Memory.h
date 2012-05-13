//
//  memory.h
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_memory_h
#define Project1_memory_h
#include "Execute.h"

struct Memoried{
    Executed* executed;
    ~Memoried();
    int read;
};

class Memory{
    int* ram;
public:
    Memory();
    int getMemory(unsigned short);
    void setMemory(unsigned short,int data);
    int getMemoryOutput(Executed* exec);
    Memoried* performMemory(Executed* exec);
};


#endif
