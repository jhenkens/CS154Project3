//
//  Fetched.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include <string>
#include <sstream>
#include "Fetched.h"

Fetched::Fetched(){
    
}

Fetched::Fetched(int instruction, unsigned int pc){
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
    
    
    this->PC=pc;
    
    if(add){
        this->instructionName="add";
        this->instructionType='R';
    } else if(addi){
        this->instructionName="addi";
        this->instructionType='I';
    } else if(slt){
        this->instructionName="slt";
        this->instructionType='R';
    } else if(sub){
        this->instructionName="sub";
        this->instructionType='R';
    } else if(xori){
        this->instructionName="xori";
        this->instructionType='I';
    } else if(lw){
        this->instructionName="lw";
        this->instructionType='I';
    } else if(sw){
        this->instructionName="sw";
        this->instructionType='I';
    } else if(bne){
        this->instructionName="bne";
        this->instructionType='I';
    } else if(bge){
        this->instructionName="bge";
        this->instructionType='I';
    } else if(jal){
        this->instructionName="jal";
        this->instructionType='J';
    }
    
    
    this->op=op;
    this->func=func;
    this->rs=(unsigned char)((instruction>>21)&0x1F);
    this->rt=(unsigned char)((instruction>>16)&0x1F);
    this->rd=(unsigned char)((instruction>>11)&0x1F);
    
    //sign extension
    if((instruction>>15)&0x1){
        this->immi=(0xFFFF0000|(instruction&0xFFFF));
    } else{
        this->immi=(instruction&0xFFFF);
    }
    this->jumpAddr=(instruction&0x3FFFFFF);
    
    this->memWr = sw;
	this->memToReg = lw;
	this->memRd = lw;
	this->aluSrc = (sw||lw||xori||addi);
	this->bType = ((bne||bge)<<1);
	this->bType+= (bne||jal);
	
	this->regDest = (add||slt||sub);
	this->regWr = (addi||xori||add||slt||sub||lw||jal);
	
	this->aluOp = ((xori||slt||bne||bge)<<2);
	this->aluOp+= ((addi||add||slt||sub||lw||sw||bge||jal)<<1);
	this->aluOp+= (xori||sub||bne);
    
    if(this->regWr){
        if(this->bType==1){
            this->writeReg=31;
        } else if(this->regDest){
            this->writeReg=this->rd;
        } else{
            this->writeReg=this->rt;
        }
    } else{
        this->writeReg=-1;
    }
    this->instruction=instruction;
    
    branch = (bType>1);
    this->stall = false;
    
    
    std::stringstream ss;
    switch(this->instructionType){
        case 'J':
            ss<<this->instructionName<<" "<<this->jumpAddr;
            break;
        case 'I':
            ss<<this->instructionName<<" $";
            if(branch){
                ss<<((short)this->rs)<<", $"<<((short)this->rt);
            } else{
                ss<<((short)this->rt)<<", $"<<((short)this->rs);
            }
            ss<<", "<<this->immi;
            break;
        case 'R':
            ss<<this->instructionName<<" $"<<((short)this->rd)<<", $"<<((short)this->rs)<<", $"<<((short)this->rt);
            break;            
    }
    this->printString=ss.str();
}

void Fetched::setIfStalls(Fetched *prevFetch, Fetched *prevDecode){
    
}

Fetched::~Fetched(){
    
}

unsigned int Fetched::getPredictedOffset(){
    if(branch && branchPredictorWhenMade){
#ifdef DEBUG
        std::cerr<<"Predicting taken!"<<std::endl;
#endif
        return immi<<2;
    } else{
#ifdef DEBUG
        std::cerr<<"Predicting not taken!"<<std::endl;
#endif
        return 0;
    }
}