//
//  driver.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 . All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include "driver.h"
#include "Decoder.h"
#include "Memory.h"
#include "WriteBack.h"

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
    int* iE = new int;
    (*iE)=0;
    Fetched* prevInstruction=0;
    Decoded* prevDecode=0;
    Executed* prevExecute=0;
    Memoried* prevMem=0;
    for(i = 0; shouldContinue(instMem,prevInstruction, prevDecode, prevExecute, prevMem);i++){
        
        cout<<"Cycle "<<i<<":"<<endl;
        Fetched* instr = instMem->performFetch();
        
        string wbRes = WriteBack::performWriteBack(reg, prevMem,iE);
        
        Decoded* decoded = reg->performDecode(prevInstruction, prevDecode);
        
        Executed* execute = Execute::performExecute(prevDecode,prevExecute,prevMem);
        
        Memoried* memoried = mem->performMemory(prevExecute,prevMem);
        
        cout<<wbRes<<endl;
        
        reg->printRegisters();
        
        if(decoded!=0&&decoded->stall){
            delete instr;
            delete decoded;
            prevDecode = 0;
            prevExecute=execute;
            delete prevMem;
            prevMem=memoried;
        } if(decoded!=0 && (decoded->branch!=decoded->branchPredictorWhenMade)){
            delete instr;
            prevInstruction=0;
            prevDecode = decoded;
            prevExecute = execute;
            
            instMem->updatePC(true,false,(decoded->immi)<<2,0);
            delete prevMem;
            prevMem = memoried;
        } else{
            delete prevInstruction;
            prevInstruction=instr;
            delete prevDecode;
            prevDecode = decoded;
            delete prevExecute;
            prevExecute = execute;
            
            instMem->updatePC(false,(instr!=0&&instr->bType==1),0,(instr!=0)?(instr->jumpAddr)<<2:0);
            delete prevMem;
            prevMem = memoried;
        }

    }
    
    cout<<"Cycles: "<<i<<endl;
    cout<<"Instructions executed: "<<(*iE)<<endl;
    
    return 0;
}



bool shouldContinue(Fetch* instMem, Fetched* instr,Decoded* dec, Executed* exec, Memoried* mem){
    bool done = instMem->isDone();
    return ((!done)||(instr!=0)||(dec!=0)||(exec!=0)||(mem!=0));
}
