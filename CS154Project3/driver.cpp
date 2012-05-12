//
//  driver.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 . All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill

/*
 Question for TA:
 JAL: What register is $ra? is it register 31? - it is register 31  
 JAL: ALU OP? does it matter?
 
 BGE: Branch Greater than or Equal? Use ALUop slt?
 
 What do you do for the ALU 'not' operator? - I think it was answeres in piazza - invert first word
 
 
 Is it OK that writeback is in the same class as decoder? It is pretty much just our registry IO class
 Is it OK that branch support is just in our fetch class?
 For decoder, is what we did alright? read two registers in separate instructions, store in ints
 
 For branching/jumping support, do we have to only use the zerobit from the ALUResult? This messing things up with xor and sub, only works with slt
 
 Ask Prof:
 For BNE - should we use sub or xor? if we use XOR, then both BNE and BGE branch of aluresult ==0
 If we use sub or xor, it would change the ALUop value in the printout, even if the result was the same

 
 
 
 */
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include "driver.h"
#include "fetch.h"
#include "execute.h"
#include "decoder.h"
#include "memory.h"

#define TEST
using namespace std;


int main(int argc, char * argv[])
{
    if(argc!=3 || strncmp(argv[1], "-file",5)!=0) {
        printf("Invalid Arguments!");
        return 1;
    }
    
    Fetch instMem(argv[2]);
    RegFile reg;
    Memory mem;
    int lines = instMem.programLength()*4;
#ifdef TEST
    for(int i = 0; instMem.getPC()<lines;i++){
        //F
        int instruction = instMem.nextInstruction();
        if(!instruction) return 0;
        cout<<"Instruction "<<i<<": "<<instruction<<endl;
        printInstruction(instruction);
        Decoded* controlBits = Decoded::getControlBits(instruction);
        //TO FIX
        //printControlBits(controlBits);
        //D
        int rs = reg.getRegister(controlBits->rs);
        int rt = reg.getRegister(controlBits->rt);
        //X
        bool zeroBit = 0;
        int aluResult = Execute::aluOp(controlBits,rs,rt,&zeroBit);
        cout<<"ALU Result: "<<aluResult<<endl;
        //M
        int memoryRead = mem.getMemoryOutput(aluResult, rt, controlBits);
        //To Fix
        //printMemResult(controlBits,memoryRead);
        //W
        reg.writeBack(controlBits, aluResult, memoryRead, instMem.getPCPlus4());
        reg.printRegisters();
        //Update PC:
        instMem.updatePC(controlBits, zeroBit);
    }
#endif
    
    return 0;
}

void printMemResult(unsigned short controlBits, int memoryRead){
    cout<<"Mem Result: ";
    if((controlBits>>5)&0b1){
        cout<<memoryRead;
    } else{
        cout<<"X";
    }
    cout<<endl;
}

void printControlBits(unsigned short bits){
    cout<<"Control Bits:"<<endl;
    cout<<"{alu: "<<(bits>>8)<<", mw: "<<((bits>>7)&0b1)<<", mr: "<<((bits>>5)&0b1)<<", mtr: ";
    cout<<((bits>>6)&0b1)<<", asrc: "<<((bits>>4)&0b1)<<", bt: "<<((bits>>2)&0b11)<<", rdst: ";
    cout<<((bits>>1)&0b1)<<", rw: "<<(bits&0b1)<<"}"<<endl;
}

void printInstruction(int instruction){
    char instType = 0;
    switch ((instruction & 0xFC000000)>>26) {
        case 14:
            //addi
            cout<<"addi ";
            instType = 'I';
            break;
        case 20:
            //xori
            cout<<"xori ";
            instType = 'I';
            break;
        case 0:
            instType = 'R';
            switch (instruction & 0x0000003F) {
                case 10:
                    //add
                    cout<<"add ";
                    break;
                case 12:
                    cout<<"slt ";
                    break;
                case 17:
                    cout<<"sub ";
                    break;
                default:
                    //BAD MATCH
                    break;
            }
            break;
        case 3:
            //lw
            cout<<"lw ";
            instType = 'I';
            break;
        case 7:
            //sw
            cout<<"sw ";
            instType = 'I';
            break;
        case 44:
            //bne
            cout<<"bne ";
            instType = 'I';
            break;
        case 34:
            //bge
            cout<<"bge ";
            instType = 'I';
            break;
        case 36:
            cout<<"jal ";
            instType = 'J';
            //jal
            // ?? Not sure about this guy here
            break;
        default:
            //BAD MATCH
            break;
    }
    
    switch (instType) {
        case 'I':
            cout<<"$"<<((instruction&0x1F0000)>>16)<<", $"<<((instruction&0x3E00000)>>21)<<", ";
            cout<<((short)(instruction&0x0000FFFF));
            break;
        case 'R':
            cout<<"$"<<((instruction&0x0000F800)>>11)<<", $"<<((instruction>>21)&0b11111)<<", $";
            cout<<((instruction>>16)&0b11111);
            break;
        case 'J':
            cout<<((instruction&0x3FFFFFF));
        default:
            break;
    }
    cout<<endl;
    cout<<"Fields: {rd: "<<((instruction>>11)&0b11111)<<", rs: "<<((instruction>>21)&0b11111)<<", rt: ";
    cout<<((instruction>>16)&0b11111)<<", imm: "<<((short)(instruction&0xFFFF))<<"}"<<endl;

}