//
//  Execute.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Execute.h"
#include "Memoried.h"

int Execute::aluOp(Decoded* decoded){
    Fetched* controlBits= decoded->fetched;
    int reg1 = decoded->read1;
    int reg2 = decoded->read2;
    int a1=reg1;
    int a2=(controlBits->aluSrc)?controlBits->immi:reg2;
    int result;
    switch (controlBits->aluOp) {
        case 0:
            //And
            result = a1&a2;
            break;
        case 1:
            result = a1|a2;
            break;
        case 2:
            result = a1+a2;
            break;
        case 3:
            result = a1-a2;
            break;
        case 4:
            result = !a1;
            break;
        case 5:
            result = a1^a2;
            break;
        case 6:
            result = a1<a2;
            break;
        default:
            break;
    }
    return result;
}

Executed* Execute::performExecute(Decoded* decoded, Executed* prevExec, Memoried* prevMem){
    if(decoded==0){
        std::cout<<"Execute instruction: "<<std::endl;
        return 0;
    }
    Executed* executed = new Executed;
    std::cout<<"Execute instruction: "<<decoded->fetched->printString<<std::endl;
    executed->decoded=decoded;
    if(decoded->fetched->regWr){
        if(decoded->fetched->bType==1){
            executed->writeReg=31;
        } else if(decoded->fetched->regDest){
            executed->writeReg=decoded->fetched->rd;
        } else{
            executed->writeReg=decoded->fetched->rt;
        }
    } else{
        executed->writeReg=-1;
    }

    Fetched* ftchd = decoded->fetched;
    if(ftchd->instructionType=='I'||ftchd->instructionType=='R'){
        if((prevExec!=0)&&(ftchd->rs==prevExec->writeReg)){
            if(!(prevExec->decoded->fetched->memToReg)){
                decoded->read1=prevExec->result;
            } else{
                //TO DO:
                //If prev instruction is LW, stall
                //Except if jump

            }
        } else if((prevMem!=0)&&(ftchd->rs==prevMem->executed->writeReg)){
            if(!(prevMem->executed->decoded->fetched->memToReg)){
                decoded->read1 = prevMem->executed->result;
            } else{
                decoded->read1 = prevMem->read;
            }
        }
        if(!ftchd->aluSrc||ftchd->memWr){
            if((prevExec!=0)&&(ftchd->rt==prevExec->writeReg)){
                if(!(prevExec->decoded->fetched->memToReg)){
                    decoded->read2 = prevExec->result;
                } else{
                    //TO DO:
                    // If current instruction is not sw, stall on LW for prev instr
                    // If it is sw, handle forwarding in memory stage
                }
            } else if((prevMem!=0)&&(ftchd->rt==prevMem->executed->writeReg)){
                if(!(prevMem->executed->decoded->fetched->memToReg)){
                    decoded->read2 = prevMem->executed->result;
                } else{
                    decoded->read2 = prevMem->read;
                }
            }
        }
    }
    
    executed->result=aluOp(decoded);
    
    executed->zeroBit=(executed->result)?0:1;
    return executed;
}