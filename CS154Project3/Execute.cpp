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
//    int a1 = forwardControl1?forwardedData1:b1;
//    int a2 = forwardControl2?forwardedData2:b2;
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
        switch(decoded->fetched->instructionType){
                case 'J':
                executed->writeReg=31;
                break;
                case 'I':
                executed->writeReg=decoded->fetched->rt;
                break;
                case 'R':
                executed->writeReg=decoded->fetched->rd;
                break;
        }
    } else{
        executed->writeReg=-1;
    }
    
//    int forwardedData1 = 0;
//    bool forwardControl1 = false;
//    int forwardedData2 = 0;
//    bool forwardControl2 = false;
    
    Fetched* ftchd = decoded->fetched;
    if(ftchd->instructionType=='I'||ftchd->instructionType=='R'){
        if((prevExec!=0)&&(ftchd->rs==prevExec->writeReg)){
            if(!(prevExec->decoded->fetched->memToReg)){
                decoded->read1=prevExec->result;
//                forwardedData1 = prevExec->result;
            } else{
                //TO DO:
                //STALL FOR LW
            }
//            forwardControl1=true;
        } else if((prevMem!=0)&&(ftchd->rs==prevMem->executed->writeReg)){
            if(!(prevMem->executed->decoded->fetched->memToReg)){
                decoded->read1 = prevMem->executed->result;
//                forwardedData1 = prevMem->executed->result;
            } else{
                decoded->read1 = prevMem->read;
//                forwardedData1 = prevMem->read;
            }
//            forwardControl1=true;
        }
        if((!ftchd->aluSrc)||ftchd->memWr){
            if((prevExec!=0)&&(ftchd->rt==prevExec->writeReg)){
                if(!(prevExec->decoded->fetched->memToReg)){
                    decoded->read2 = prevExec->result;
                    //                forwardedData2 = prevExec->result;
                } else{
                    //TO DO:
                    //STALL FOR LW
                }
                //            forwardControl2=true;
            } else if((prevMem!=0)&&(ftchd->rt==prevMem->executed->writeReg)){
                if(!(prevMem->executed->decoded->fetched->memToReg)){
                    decoded->read2 = prevMem->executed->result;
                    //                forwardedData2 = prevMem->executed->result;
                } else{
                    decoded->read2 = prevMem->read;
                    //                forwardedData2 = prevMem->read;
                }
                //            forwardControl2=true;
            }
        }
    }
    
    executed->result=aluOp(decoded);
    
    executed->zeroBit=(executed->result)?0:1;
    return executed;
}