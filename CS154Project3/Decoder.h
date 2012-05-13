//
//  decoder.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CS154Project3_decoder_h
#define CS154Project3_decoder_h
#include <string>
#include "Fetch.h"

struct Decoded{
    Fetched* fetched;
    ~Decoded();
    int read1;
    int read2;
};

class RegFile{
    int* registers;
public:
    unsigned short getControlBits(int);
    RegFile();
    int getRegister(unsigned char);
    void setRegister(unsigned char, int value);
    void printRegisters();
    Decoded* performDecode(Fetched* fetched);
};



#endif
