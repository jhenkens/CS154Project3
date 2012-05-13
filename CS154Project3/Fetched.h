//
//  Fetched.h
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#ifndef CS154Project3_Fetched_h
#define CS154Project3_Fetched_h

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


#endif
