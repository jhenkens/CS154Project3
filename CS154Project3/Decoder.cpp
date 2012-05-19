//
//  Decoder.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include <assert.h>
#include "Decoder.h"

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

Decoded* RegFile::performDecode(Fetched *fetched, Decoded *prevDecode){
    if(fetched==0){
        std::cout<<"Decode instruction: "<<std::endl;
        return 0;
    }
    Decoded* result = new Decoded;
    std::cout<<"Decode instruction: "<<fetched->printString<<std::endl;
    result->fetched=fetched;
    result->read1=getRegister(fetched->rs);
    result->read2=getRegister(fetched->rt);
    result->stall=false;
    
    if(fetched->instructionType=='I'||fetched->instructionType=='R'){
        if((prevDecode!=0)&&(prevDecode->fetched->memToReg)){
            char prevDecodeWriteReg = (prevDecode->fetched->regDest)?(prevDecode->fetched->rd):(prevDecode->fetched->rt);
            char rs = fetched->rs;
            char rt = fetched->rt;
            if(prevDecodeWriteReg==rs || ((!fetched->aluSrc)&&(prevDecodeWriteReg==rt))){
                result->stall=true;
            }
        }    
    }
    switch(fetched->bType){
        case 2:
            result->branch = (result->read1>=result->read2);
            break;
        case 3:
            result->branch = (result->read1!=result->read2);
            break;
        default:
            result->branch = false;
            break;
    }
    return result;
}
