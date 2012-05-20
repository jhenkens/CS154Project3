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

int Execute::aluOp(Executed* decoded){
    int reg1 = decoded->readReg1;
    int reg2 = decoded->readReg2;
    int a1=reg1;
    int a2=(decoded->aluSrc)?decoded->immi:reg2;
    int result;
    switch (decoded->aluOp) {
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
    Executed* executed = new Executed(decoded);
    std::cout<<"Execute instruction: "<<executed->printString<<std::endl;
    if(executed->instructionType=='I'||executed->instructionType=='R'){
        if((prevExec!=0)&&(executed->rs==prevExec->writeReg)){
            if(!(prevExec->memToReg)){
                executed->readReg1=prevExec->result;
            } else{
                //TO DO:
                //If prev instruction is LW, stall
                //Except if jump

            }
        } else if((prevMem!=0)&&(executed->rs==prevMem->writeReg)){
            if(!(prevMem->memToReg)){
                executed->readReg1 = prevMem->result;
            } else{
                executed->readReg1 = prevMem->memRead;
            }
        }
        if(!executed->aluSrc||executed->memWr){
            if((prevExec!=0)&&(executed->rt==prevExec->writeReg)){
                if(!(prevExec->memToReg)){
                    executed->readReg2 = prevExec->result;
                } else{
                    //TO DO:
                    // If current instruction is not sw, stall on LW for prev instr
                    // If it is sw, handle forwarding in memory stage
                }
            } else if((prevMem!=0)&&(executed->rt==prevMem->writeReg)){
                if(!(prevMem->memToReg)){
                    executed->readReg2 = prevMem->result;
                } else{
                    executed->readReg2 = prevMem->memRead;
                }
            }
        }
    }
    
    if(executed->instructionType!='J') executed->result=aluOp(executed);
    else executed->result=executed->PC+4;
    executed->zeroBit=(executed->result)?0:1;
    return executed;
}