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

std::string WriteBack::performWriteBack(RegFile* reg, Memoried* mem, int* iE){
    if(mem==0){
        return "WriteBack instruction: ";
    }
    std::stringstream ss;
    ss<<"WriteBack instruction: "<<mem->printString;
    if(mem->regWr){
        unsigned char destReg = mem->writeReg;
        int writeData = mem->memToReg?mem->memRead:mem->result;
        reg->setRegister(destReg,writeData);
    }
    (*iE)++;
    return ss.str();
}