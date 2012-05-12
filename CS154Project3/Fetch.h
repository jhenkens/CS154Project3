//
//  fetch.h
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef Project1_fetch_h
#define Project1_fetch_h

struct Fetched{
    unsigned char op;
    unsigned char func;
    
    unsigned char rt;
    unsigned char rs;
    unsigned char rd;
    
    std::string instructionName;
    std::string printString;
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
    static Fetched* getControlBits(int);
    int instruction;
};

class Fetch{
    int* instructions;
    unsigned int pc;
    unsigned int maxPC;
    unsigned int length;
public:
    Fetch(char*);
    int nextInstruction();
    int programLength();
    unsigned int getPC();
    unsigned int getPCPlus4();
    void updatePC(Fetched* controlBits, bool zeroBit);
    Fetched* performFetch();
    bool isDone();
};


#endif
