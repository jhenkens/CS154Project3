//
//  driver.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 . All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill

/*
 Question for TA:
 JAL: What register is $ra? is it register 31? - it is register 31  
 JAL: ALU OP? does it matter?
 
 BGE: Branch Greater than or Equal? Use ALUop slt?
 
 What do you do for the ALU 'not' operator? - I think it was answeres in piazza - invert first word
 
 
 Is it OK that writeback is in the same class as decoder? It is pretty much just our registry IO class
 Is it OK that branch support is just in our fetch class?
 For decoder, is what we did alright? read two registers in separate instructions, store in ints
 
 For branching/jumping support, do we have to only use the zerobit from the ALUResult? This messing things up with xor and sub, only works with slt
 
 Ask Prof:
 For BNE - should we use sub or xor? if we use XOR, then both BNE and BGE branch of aluresult ==0
 If we use sub or xor, it would change the ALUop value in the printout, even if the result was the same

 
 
 
 */
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include "driver.h"

#define TEST
using namespace std;


int main(int argc, char * argv[])
{
    if(argc!=3 || strncmp(argv[1], "-file",5)!=0) {
        printf("Invalid Arguments!");
        return 1;
    }
    
    Fetch* instMem = new Fetch(argv[2]);
    RegFile* reg = new RegFile;
    Memory* mem = new Memory;
    int i;
    Fetched* prevInstruction=0;
    Decoded* prevDecode=0;
    Executed* prevExecute=0;
    Memoried* prevMem=0;
    for(i = 0; shouldContinue(instMem,prevInstruction, prevDecode, prevExecute, prevMem);i++){
        
        cout<<"Cycle "<<i<<":"<<endl;
        Fetched* instr = instMem->performFetch();
        
        string wbRes = WriteBack::performWriteBack(reg, prevMem);
        
        Decoded* decoded = reg->performDecode(prevInstruction);
        prevInstruction=instr;
        
        Executed* execute = Execute::performExecute(prevDecode);
        prevDecode = decoded;
        
        Memoried* memoried = mem->performMemory(prevExecute);
        prevExecute = execute;
        
        cout<<wbRes<<endl;
        delete prevMem;
        prevMem = memoried;
        
        reg->printRegisters();
        instMem->updatePC(instr, 0);

    }
    
    cout<<"Cycles: "<<i<<endl;
    cout<<"Instructions executed: "<<instMem->programLength()<<endl;
    
    return 0;
}

bool shouldContinue(Fetch* instMem, Fetched* instr,Decoded* dec, Executed* exec, Memoried* mem){
    bool done = instMem->isDone();
    return ((!done)||(instr!=0)||(dec!=0)||(exec!=0)||(mem!=0));
}
