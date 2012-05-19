//
//  Memory.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_memory_h
#define Project1_memory_h
#include "Execute.h"
#include "Memoried.h"


class Memory{
    int ram [256];
public:
    Memory();
    int getMemory(unsigned short);
    void setMemory(unsigned short,int data);
    int getMemoryOutput(Executed* exec);
    Memoried* performMemory(Executed* exec,Memoried*);
};


#endif
