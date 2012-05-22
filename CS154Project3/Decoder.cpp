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
#include <stdio.h>
#include <assert.h>
#include "Decoder.h"

RegFile::RegFile(){
    registers = new int[32];
    for(int i = 0; i<32;i++)registers[i]=0;
}

int RegFile::getRegister(unsigned char regNum){
    assert(regNum<32);
    return registers[regNum];
}

void RegFile::setRegister(unsigned char regNum, int value){
    assert(regNum<32);
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

Decoded* RegFile::performDecode(Fetched *fetched, Decoded *prevDecode, Executed* prevExec){
    if(fetched==0){
        std::cout<<"Decode instruction: "<<std::endl;
        return 0;
    }
    Decoded* result = new Decoded(fetched);
    std::cout<<"Decode instruction: "<<result->printString<<std::endl;
    result->readReg1=getRegister(result->rs);
    result->readReg2=getRegister(result->rt);
    result->stall=false;
    
    //Handle branch stall
    if(result->branch){   
        if((prevDecode!=0 && prevDecode->regWr) && 
           (prevDecode->writeReg==result->rs || prevDecode->writeReg==result->rt)){
            result->stall=true;
        } else if((prevExec!=0 && prevExec->regWr && prevExec->memRd)&&
                  (prevExec->writeReg==result->rs || prevExec->writeReg==result->rt)){
            result->stall=true;
        }
    }
    if(!result->stall && (result->instructionType=='I'||result->instructionType=='R')){
        if((prevDecode!=0)&&(prevDecode->memToReg)){
            char prevDecodeWriteReg = (prevDecode->regDest)?(prevDecode->rd):(prevDecode->rt);
            char rs = result->rs;
            char rt = result->rt;
            if(prevDecodeWriteReg==rs || ((!result->aluSrc)&&(prevDecodeWriteReg==rt))){
                result->stall=true;
            }
        }    
    }
    
    //determine branch output

    
    if(!result->stall && result->branch){
        int wire1 = result->readReg1;
        int wire2 = result->readReg2;
        if(prevExec!=0 && prevExec->regWr && !prevExec->memRd){
            if (prevExec->writeReg==result->rs){
                wire1=prevExec->result;
            }
            if(prevExec->writeReg==result->rt){
                wire2=prevExec->result;
            }
        } 
        switch(result->bType){
            case 2:
                result->branchResult = (wire1>=wire2);
                break;
            case 3:
                result->branchResult = (wire1!=wire2);
                break;
            default:
                break;
        }
    }
    return result;
}
