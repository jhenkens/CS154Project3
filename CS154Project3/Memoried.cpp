//
//  Memoried.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include "Memoried.h"


Memoried::Memoried(Executed* exec): Executed(exec){
    this->result=exec->result;
    this->zeroBit=exec->zeroBit;
    this->writeReg=exec->writeReg;
}