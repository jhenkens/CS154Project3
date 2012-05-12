//
//  WriteBack.cpp
//  CS154Project3
//
//  Created by Charlotte Hill on 5/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "WriteBack.h"
void WriteBack::performWriteBack(RegFile* reg, Memoried* mem){
    Fetched* controlBits = mem->executed->decoded->fetched;
    if(controlBits->memWr){
        if(controlBits->bType==1) reg->setRegister(31,0); // TO DO - HANDLE PCPLUS4 WRITE?! instead of 0
        else{ 
            unsigned char destReg = controlBits->regDest?controlBits->rd:controlBits->rt;
            int writeData = controlBits->memToReg?mem->read:mem->executed->result;
            reg->setRegister(destReg,writeData);
        }
    }
}