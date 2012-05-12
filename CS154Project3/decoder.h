//
//  decoder.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CS154Project3_decoder_h
#define CS154Project3_decoder_h
struct decoded{
    unsigned char op;
    unsigned char func;
    
    unsigned char rt;
    unsigned char rs;
    unsigned char rd;
    
    char immi;
    char jumpAddr;
    
    bool memWr;
    bool memToReg;
    bool memRd;
    bool aluSrc;
    
    char bType;
    
    bool regDest;
    bool regWr;
    
    char aluOp;
    static decoded* getControlBits(int);
};

class regFile{
    int* registers;
public:
    unsigned short getControlBits(int);
    reGfile();
    int getRegister(unsigned char);
    void setRegister(unsigned char, int value);
    int getRegister(char reg);
    void writeBack(int aluInput, int memInput, int instruction, int controlBits,int pc);
    void printRegisters();
};



#endif
