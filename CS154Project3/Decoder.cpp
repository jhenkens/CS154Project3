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

Decoded* Decoded::getControlBits(int instruction){
    unsigned char op = (unsigned char)((instruction&0xFC000000)>>26);
    unsigned char func = (unsigned char)((instruction&0x3F));
    bool add = ((op==0x0)&&(func==0xA));
	bool slt = ((op==0x0)&&(func==0xC));
	bool sub = ((op==0x0)&&(func==0x11));
    bool addi = (op==0xE);
    bool xori = (op==0x14);
    bool lw = (op==0x3);
    bool sw = (op==0x7);
    bool bne = (op==0x2C);
    bool bge = (op==0x22);
    bool jal = (op==0x24);
    
    
    
    
    Decoded* result = new Decoded;
    
    if(add){
        result->instruction="add";
        result->instructionType='R';
    } else if(addi){
        result->instruction="addi";
        result->instructionType='I';
    } else if(slt){
        result->instruction="slt";
        result->instructionType='R';
    } else if(sub){
        result->instruction="sub";
        result->instructionType='R';
    } else if(xori){
        result->instruction="xori";
        result->instructionType='I';
    } else if(lw){
        result->instruction="lw";
        result->instructionType='I';
    } else if(sw){
        result->instruction="sw";
        result->instructionType='I';
    } else if(bne){
        result->instruction="bne";
        result->instructionType='I';
    } else if(bge){
        result->instruction="bge";
        result->instructionType='I';
    } else if(jal){
        result->instruction="jal";
        result->instructionType='J';
    } 
    
    result->op=op;
    result->func=func;
    result->rs=(unsigned char)((instruction>>21)&0x1F);
    result->rt=(unsigned char)((instruction>>16)&0x1F);
    result->rd=(unsigned char)((instruction>>11)&0x1F);
    
    //sign extension
    result->immi=((instruction>>15)&0x1)?(0xFFFF0000||(instruction&0xFFFF)):(0x00000000||(instruction&0xFFFF));
    result->jumpAddr=((instruction&0x3FFFFFF));
    
    result->memWr = sw;
	result->memToReg = lw;
	result->memRd = lw;
	result->aluSrc = (sw||lw||xori||addi);
	result->bType = ((bne||bge)<<1);
	result->bType+= (bne||jal);
	
	result->regDest = (add||slt||sub);
	result->regWr = (addi||xori||add||slt||sub||lw||jal);
	
	result->aluOp = ((xori||slt||bne||bge)<<2);
	result->aluOp+= ((addi||add||slt||sub||lw||sw||bge||jal)<<1);
	result->aluOp+= (xori||sub||bne);
    return result;
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

void RegFile::writeBack( Decoded* controlBits,int aluInput, int memInput,int pcPlus4){
    if(controlBits->memWr){
        if(controlBits->bType==1) setRegister(31,pcPlus4);
        else{ 
            unsigned char destReg = controlBits->regDest?controlBits->rd:controlBits->rt;
            int writeData = controlBits->memToReg?memInput:aluInput;
            setRegister(destReg,writeData);
        }
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
