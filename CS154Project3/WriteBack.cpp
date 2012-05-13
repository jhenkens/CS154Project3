//
//  WriteBack.cpp
//  CS154Project3
//
//  Created by Charlotte Hill on 5/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "WriteBack.h"
#include <sstream>
std::string WriteBack::performWriteBack(RegFile* reg, Memoried* mem){
    if(mem==0){
        return "WriteBack instruction: ";
    }
    Fetched* controlBits = mem->executed->decoded->fetched;
    std::stringstream ss;
    ss<<"WriteBack instruction: "<<controlBits->printString;
    if(controlBits->regWr){
        if(controlBits->bType==1) reg->setRegister(31,0); // TO DO - HANDLE PCPLUS4 WRITE?! instead of 0
        else{ 
            unsigned char destReg = controlBits->regDest?controlBits->rd:controlBits->rt;
            int writeData = controlBits->memToReg?mem->read:mem->executed->result;
            reg->setRegister(destReg,writeData);
        }
    }
    return ss.str();
}