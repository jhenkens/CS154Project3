//
//  WriteBack.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
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