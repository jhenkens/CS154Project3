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

int Execute::aluOp(Decoded* decoded, int forwardedData,char forwardLocation){
    Fetched* controlBits= decoded->fetched;
    int reg1 = decoded->read1;
    int reg2 = decoded->read2;
    int a2=(controlBits->aluSrc)?controlBits->immi:reg2;
    int a1=reg1;
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

Executed* Execute::performExecute(Decoded* decoded, Executed* prevExec, Memoried* prevMem, char forwardingContol){
    if(decoded==0){
        std::cout<<"Execute instruction: "<<std::endl;
        return 0;
    }
    Executed* executed = new Executed;
    std::cout<<"Execute instruction: "<<decoded->fetched->printString<<std::endl;
    executed->decoded=decoded;
    executed->result=aluOp(decoded,0,0);
    executed->zeroBit=(executed->result)?0:1;
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
    return executed;
}