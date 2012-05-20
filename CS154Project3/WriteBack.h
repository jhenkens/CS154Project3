//
//  WriteBack.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_WriteBack_h
#define CS154Project3_WriteBack_h
#include "Memoried.h"
#include "Decoder.h"

class WriteBack{
public:
    static std::string performWriteBack(RegFile* reg, Memoried* mem,int* iE);
    
};

#endif
