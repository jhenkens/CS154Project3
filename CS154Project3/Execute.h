//
//  execute.h
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_execute_h
#define Project1_execute_h
#include "Decoder.h"

class Execute{
    Execute();
public:
    static int aluOp(Decoded* controlBits, int reg1, int reg2, bool* zeroBitResult);
};

#endif