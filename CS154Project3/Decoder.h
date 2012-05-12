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
struct Decoded{
    unsigned char op;
    unsigned char func;
    
    unsigned char rt;
    unsigned char rs;
    unsigned char rd;
    
    std::string instruction;
    char instructionType;
    
    int immi;
    int jumpAddr;
    
    bool memWr;
    bool memToReg;
    bool memRd;
    bool aluSrc;
    
    char bType;
    
    bool regDest;
    bool regWr;
    
    char aluOp;
    static Decoded* getControlBits(int);
};

class RegFile{
    int* registers;
public:
    unsigned short getControlBits(int);
    RegFile();
    int getRegister(unsigned char);
    void setRegister(unsigned char, int value);
    void writeBack( Decoded* controlBits,int aluInput, int memInput,int pcPlus4);
    void printRegisters();
};



#endif
