//
//  Executed.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Executed.h"   

Executed::Executed(Decoded* decoded): Decoded(decoded){
    this->readReg1=decoded->readReg1;
    this->readReg2=decoded->readReg2;
    this->stall=decoded->stall;
    this->branch=decoded->branch;
    this->branchResult=decoded->branchResult;
}

Executed::~Executed(){
    
}