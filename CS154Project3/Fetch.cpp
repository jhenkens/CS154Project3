//
//  fetch.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Fetch.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

Fetched* Fetched::getControlBits(int instruction){
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
    
    
    
    
    Fetched* result = new Fetched;
    
    if(add){
        result->instructionName="add";
        result->instructionType='R';
    } else if(addi){
        result->instructionName="addi";
        result->instructionType='I';
    } else if(slt){
        result->instructionName="slt";
        result->instructionType='R';
    } else if(sub){
        result->instructionName="sub";
        result->instructionType='R';
    } else if(xori){
        result->instructionName="xori";
        result->instructionType='I';
    } else if(lw){
        result->instructionName="lw";
        result->instructionType='I';
    } else if(sw){
        result->instructionName="sw";
        result->instructionType='I';
    } else if(bne){
        result->instructionName="bne";
        result->instructionType='I';
    } else if(bge){
        result->instructionName="bge";
        result->instructionType='I';
    } else if(jal){
        result->instructionName="jal";
        result->instructionType='J';
    } 
    
    result->op=op;
    result->func=func;
    result->rs=(unsigned char)((instruction>>21)&0x1F);
    result->rt=(unsigned char)((instruction>>16)&0x1F);
    result->rd=(unsigned char)((instruction>>11)&0x1F);
    
    //sign extension
    if((instruction>>15)&0x1){
        result->immi=(0xFFFF0000||(instruction&0xFFFF));
    } else{
        result->immi=(instruction&0xFFFF);
    }
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
    
    result->instruction=instruction;
    
    std::stringstream ss;
    switch(result->instructionType){
            case 'J':
            ss<<result->instructionName<<" "<<result->jumpAddr;
            break;
            case 'I':
            ss<<result->instructionName<<" $"<<((short)result->rt)<<", $"<<((short)result->rs)<<", "<<result->immi;
            break;
            case 'R':
            ss<<result->instructionName<<" $"<<((short)result->rd)<<", $"<<((short)result->rs)<<", $"<<((short)result->rt);
            break;            
    }
    result->printString=ss.str();
    return result;
}

Fetch::Fetch(char* filename){
    std::vector<int> instructionsVect;
    std::ifstream file;
    file.open(filename);
    std::string line;
    getline(file,line);
    while (!file.eof()) {
        instructionsVect.push_back(atoi(line.c_str()));
        getline(file, line);
    }
    file.close();
    length = (unsigned int) instructionsVect.size();
    maxPC = length*4;
    instructions = new int[length];
    for(int i = 0; i < length;i++){
        instructions[i]=instructionsVect[i];
    }
    pc = 0;
}

void Fetch::updatePC(Fetched* controlBits, bool zeroBit){
    if(controlBits==0){
        pc=getPCPlus4();
        return;
    }
    switch (controlBits->bType) {
        case 0:
            pc=getPCPlus4();
            return;
        case 1:
            //Jump
            pc=controlBits->jumpAddr*4;
            break;
        case 2:
            //BGE
            if(zeroBit){
                pc+=4*controlBits->immi;
            }
            break;
        case 3:
            //BNE
            if(!zeroBit){
                pc+=4*controlBits->immi;
            }
            break;
        default:
            break;
    }
}

int Fetch::nextInstruction(){
    return instructions[pc>>2];
}

int Fetch::programLength(){
    return length;
}

unsigned int Fetch::getPC(){
    return pc;
}
unsigned int Fetch::getPCPlus4(){
    return pc+4;
}

bool Fetch::isDone(){
    return pc>=maxPC;
}

Fetched* Fetch::performFetch(){
    if(isDone()){
        std::cout<<"Fetch instruction: "<<std::endl;
        return 0;
    }
    Fetched* brokenDown = Fetched::getControlBits(nextInstruction());
    std::cout<<"Fetch instruction: "<<brokenDown->printString<<std::endl;
    return brokenDown;
}

