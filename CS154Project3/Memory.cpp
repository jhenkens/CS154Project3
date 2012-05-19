//
//  Memory.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Memory.h"
#include <assert.h>

Memory::Memory(){
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

int Memory::getMemoryOutput(Executed* exec){
    int addr = exec->result;
    int input = exec->decoded->read2;
    Fetched* controlBits = exec->decoded->fetched;
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

Memoried* Memory::performMemory(Executed* exec,Memoried* prevMem){
    if(exec==0){
        std::cout<<"Memory instruction: "<<std::endl;
        return 0;
    }
    Memoried* mem = new Memoried;
    std::cout<<"Memory instruction: "<<exec->decoded->fetched->printString<<std::endl;
    
    Fetched* ftchd = exec->decoded->fetched;
    if(ftchd->memWr && (ftchd->rt==prevMem->executed->writeReg) && (prevMem->executed->decoded->fetched->memRd)){
        exec->decoded->read2=prevMem->read;
    }
    
    mem->executed=exec;
    mem->read=getMemoryOutput(exec);
    return mem;
}