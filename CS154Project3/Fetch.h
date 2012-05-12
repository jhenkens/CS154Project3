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
class fetch{
    int* instructions;
    unsigned int pc;
    unsigned int length;
public:
    fetch(char*);
    int nextInstruction();
    int programLength();
    unsigned int getPC();
    void setPCWithInfo(unsigned short controlBits, bool zeroBit, short offset, int jumpAddress);

};


#endif
