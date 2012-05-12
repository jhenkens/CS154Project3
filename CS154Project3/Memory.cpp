//
//  memory.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Memory.h"
#include <assert.h>

Memory::Memory(){
    ram = new int[256];
    for(int i = 0; i<256;i++)ram[i]=0;
}

int Memory::getMemory(unsigned short addr){
    assert(addr>=0 && addr<1024);
    return ram[addr>>2];
}

void Memory::setMemory(unsigned short addr, int data){
    assert(addr>=0 && addr<1024);
    ram[addr>>2] = data;
}

int Memory::getMemoryOutput(int addr, int input,  Decoded* controlBits){
    assert(!(controlBits->memWr&&controlBits->memRd));
    if(controlBits->memWr){
        setMemory((unsigned short) addr,input);
        return 0;
    } else if(controlBits->memRd){
        return getMemory((unsigned short) addr);
    } else{
        return 0;
    }
}
