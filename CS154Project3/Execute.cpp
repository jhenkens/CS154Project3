//
//  execute.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Execute.h"

int Execute::aluOp(Decoded* decoded){
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

Executed* Execute::performExecute(Decoded* decoded){
    if(decoded==0){
        std::cout<<"Execute instruction: "<<std::endl;
        return 0;
    }
    Executed* executed = new Executed;
    std::cout<<"Execute instruction: "<<decoded->fetched->printString<<std::endl;
    executed->decoded=decoded;
    executed->result=aluOp(decoded);
    executed->zeroBit=(executed->result)?0:1;
    return executed;
}