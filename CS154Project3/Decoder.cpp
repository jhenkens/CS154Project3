//
//  decoder.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include "Decoder.h"

Decoded::~Decoded(){
    delete fetched;
}

RegFile::RegFile(){
    registers = new int[32];
    for(int i = 0; i<32;i++)registers[i]=0;
}

int RegFile::getRegister(unsigned char regNum){
    assert(regNum<32 && regNum>=0);
    return registers[regNum];
}

void RegFile::setRegister(unsigned char regNum, int value){
    assert(regNum<32 && regNum>=0);
    if (regNum != 0) {
        registers[regNum]=value;
    }
}


void RegFile::printRegisters(){
    for(int i = 0; i<8; i++){
        for(int o = 0; o<4; o++){
            int reg = i+o*8;
            std::cout<<"$"<<reg<<": ";
            if(reg<10) std::cout<<" ";
            printf("%-8d",registers[reg]);
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

Decoded* RegFile::performDecode(Fetched *fetched){
    if(fetched==0){
        std::cout<<"Decode instruction: "<<std::endl;
        return 0;
    }
    Decoded* result = new Decoded;
    std::cout<<"Decode instruction: "<<fetched->printString<<std::endl;
    result->fetched=fetched;
    result->read1=getRegister(fetched->rs);
    result->read2=getRegister(fetched->rt);
    return result;
}
