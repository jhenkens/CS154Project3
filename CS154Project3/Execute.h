//
//  Execute.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_execute_h
#define Project1_execute_h
#include "Decoder.h"
#include "Executed.h"
#include "Memoried.h"

#define NEITHER 0
#define TOP 1
#define BOTTOM 2
#define BOTH 3

class Execute{
    Execute();
public:
    static int aluOp(Executed* decoded);
    static Executed* performExecute(Decoded* decoded, Executed* prevExec, Memoried* prevMem);
};

#endif
