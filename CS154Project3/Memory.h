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
#include "Decoder.h"

class Memory{
    int* ram;
public:
    Memory();
    int getMemory(unsigned short);
    void setMemory(unsigned short,int data);
    int getMemoryOutput(int addr, int input,  Decoded* controlBits);
};


#endif
