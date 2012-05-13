//
//  driver.h
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_driver_h
#define Project1_driver_h
#include "Fetch.h"
#include "Memoried.h"


bool shouldContinue(Fetch* instMem, Fetched* instr,Decoded* dec, Executed* exec, Memoried* mem);

#endif
