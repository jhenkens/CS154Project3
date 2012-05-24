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

Fetched::Fetched(int inst, unsigned int currPC){
    instruction=inst;
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
    
    
    PC=currPC;
    
    if(add){
        instructionName="add";
        instructionType='R';
    } else if(addi){
        instructionName="addi";
        instructionType='I';
    } else if(slt){
        instructionName="slt";
        instructionType='R';
    } else if(sub){
        instructionName="sub";
        instructionType='R';
    } else if(xori){
        instructionName="xori";
        instructionType='I';
    } else if(lw){
        instructionName="lw";
        instructionType='I';
    } else if(sw){
        instructionName="sw";
        instructionType='I';
    } else if(bne){
        instructionName="bne";
        instructionType='I';
    } else if(bge){
        instructionName="bge";
        instructionType='I';
    } else if(jal){
        instructionName="jal";
        instructionType='J';
    }
    
    
    op=op;
    func=func;
    rs=(unsigned char)((instruction>>21)&0x1F);
    rt=(unsigned char)((instruction>>16)&0x1F);
    rd=(unsigned char)((instruction>>11)&0x1F);
    
    //sign extension
    if((instruction>>15)&0x1){
        immi=(0xFFFF0000|(instruction&0xFFFF));
    } else{
        immi=(instruction&0xFFFF);
    }
    jumpAddr=(instruction&0x3FFFFFF);
    
    memWr = sw;
	memToReg = lw;
	memRd = lw;
	aluSrc = (sw||lw||xori||addi);
	bType = ((bne||bge)<<1);
	bType+= (bne||jal);
	
	regDest = (add||slt||sub);
	regWr = (addi||xori||add||slt||sub||lw||jal);
	
	aluOp = ((xori||slt||bne||bge)<<2);
	aluOp+= ((addi||add||slt||sub||lw||sw||bge||jal)<<1);
	aluOp+= (xori||sub||bne);
    
    if(regWr){
        if(bType==1){
            writeReg=31;
        } else if(regDest){
            writeReg=rd;
        } else{
            writeReg=rt;
        }
    } else{
        writeReg=-1;
    }
    
    branch = (bType>1);
    
    
    std::stringstream ss;
    switch(instructionType){
        case 'J':
            ss<<instructionName<<" "<<jumpAddr;
            break;
        case 'I':
            ss<<instructionName<<" $";
            if(branch){
                ss<<((short)rs)<<", $"<<((short)rt);
            } else{
                ss<<((short)rt)<<", $"<<((short)rs);
            }
            ss<<", "<<immi;
            break;
        case 'R':
            ss<<instructionName<<" $"<<((short)rd)<<", $"<<((short)rs)<<", $"<<((short)rt);
            break;            
    }
    printString=ss.str();
}

Fetched::~Fetched(){
    
}

