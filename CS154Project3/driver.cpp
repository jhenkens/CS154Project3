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
        if(instr!=0)instr->setIfStalls(prevInstruction, prevDecode);
        
        string wbRes = WriteBack::performWriteBack(reg, prevMem,iE);
        
        Decoded* decoded = reg->performDecode(prevInstruction, prevDecode, prevExecute);
        if(decoded!=0 && decoded->branch) instMem->updateBranchPredictor(decoded->branchResult);
        
        Executed* execute = Execute::performExecute(prevDecode,prevExecute,prevMem);
        
        Memoried* memoried = mem->performMemory(prevExecute,prevMem);
        
        cout<<wbRes<<endl;
        
        reg->printRegisters();
        
        if(decoded!=0&&decoded->stall){
            //Delete the new stuff
            delete instr;
            instr = 0;
            delete decoded;
            decoded = 0;
            //insert the noop
            delete prevDecode;
            prevDecode = 0;
            //handle as normal, minus the PC updating
            delete prevExecute;
            prevExecute=execute;
            
            delete prevMem;
            prevMem=memoried;
        }else if(decoded!=0 && (decoded->branch) && (decoded->branchPredictorWhenMade!=decoded->branchResult)){
//            cerr<<"I predicted wrong!"<<endl;
            //If we need to squash, delete the fetched instruction
            delete instr;
            instr=0;
            //Then insert the noop
            delete prevInstruction;
            prevInstruction=0;
            //Then handle like normal
            delete prevDecode;
            prevDecode = decoded;
            delete prevExecute;
            prevExecute = execute;
            delete prevMem;
            prevMem = memoried;
            //Update PC to whatever we didn't go to.
            instMem->updatePC(decoded);
        } else if(instr!=0 && instr->stall){
            //Delete the new stuff
            delete instr;
            instr=0;
            //insert the noop
            delete prevInstruction;
            prevInstruction=0;
            //handle as normal, minus the PC updating
            delete prevDecode;
            prevDecode = decoded;
            delete prevExecute;
            prevExecute=execute;
            
            delete prevMem;
            prevMem=memoried;
        }else{
//            //Normal case:
            delete prevInstruction;
            prevInstruction=instr;
            delete prevDecode;
            prevDecode = decoded;
            delete prevExecute;
            prevExecute = execute;
            delete prevMem;
            prevMem = memoried;
            
            //Update PC based on prev instruction
            instMem->updatePC(instr);
        }

    }

    cout<<"Cycles: "<<i<<endl;
    cout<<"Instructions executed: "<<(*iE)<<endl;
    
    return 0;
}

//bool branchALU(Decoded* branch, Executed* p

bool shouldContinue(Fetch* instMem, Fetched* instr,Decoded* dec, Executed* exec, Memoried* mem){
    bool done = instMem->isDone();
    return ((!done)||(instr!=0)||(dec!=0)||(exec!=0)||(mem!=0));
}
