//
//  Decoded.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Decoded.h"

Decoded::Decoded(Fetched* fetched){
    this->PC=fetched->PC;
    this->op=fetched->op;
    this->func=fetched->func;
    this->rt=fetched->rt;
    this->rs=fetched->rs;
    this->rd=fetched->rd;
    this->instructionName=fetched->instructionName;
    this->printString=fetched->printString;
    this->instructionType=fetched->instructionType;
    this->immi=fetched->immi;
    this->jumpAddr=fetched->jumpAddr;
    this->memWr=fetched->memWr;
    this->memToReg=fetched->memToReg;
    this->memRd=fetched->memRd;
    this->aluSrc=fetched->aluSrc;
    this->bType=fetched->bType;
    this->regDest=fetched->regDest;
    this->regWr=fetched->regWr;
    this->aluOp=fetched->aluOp;
    this->instruction=fetched->instruction;
    this->branchPredictorWhenMade=fetched->branchPredictorWhenMade;
    this->writeReg=fetched->writeReg;
    this->branch=fetched->branch;
}

// TO DO: Remove!
unsigned int Decoded::getProperBranchPC(){
    unsigned int result = PC+4;
    if(branchResult) result+=(immi<<2);
    return result;
}

Decoded::~Decoded(){
    
}