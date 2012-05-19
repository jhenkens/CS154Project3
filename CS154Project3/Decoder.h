//
//  Decoder.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_decoder_h
#define CS154Project3_decoder_h
#include <string>
#include "Executed.h"

class RegFile{
    int* registers;
public:
    unsigned short getControlBits(int);
    RegFile();
    int getRegister(unsigned char);
    void setRegister(unsigned char, int value);
    void printRegisters();
    Decoded* performDecode(Fetched *fetched, Decoded *prevDecode);
};



#endif
