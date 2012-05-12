//
//  fetch.cpp
//  Project1
//
//  Created by Johan Henkens on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 1 - Johan Henkens, Jay Mutarevic, Charlotte Hill
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "fetch.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

fetch::fetch(char* filename){
    std::vector<int> instructionsVect;
    std::ifstream file;
    file.open(filename);
    std::string line;
    getline(file,line);
    while (!file.eof()) {
        instructionsVect.push_back(atoi(line.c_str()));
        getline(file, line);
    }
    file.close();
    length = (unsigned int) instructionsVect.size();
    instructions = new int[length];
    for(int i = 0; i < length;i++){
        instructions[i]=instructionsVect[i];
    }
    pc = 0;
}

void fetch::setPCWithInfo(unsigned short controlBits, bool zeroBit, short offset, int jumpAddress){
    switch (((controlBits>>2)&0b11)) {
        case 0b00:
            return;
        case 0b01:
            //Jump
            pc=jumpAddress*4;
            break;
        case 0b10:
            //BGE
            if(zeroBit){
                pc+=4*offset;
            }
            break;
        case 0b11:
            //BNE
            if(!zeroBit){
                pc+=4*offset;
            }
            break;
        default:
            break;
    }
}

int fetch::nextInstruction(){
    int result = instructions[pc>>2];
    pc+=4;
    return result;
}

int fetch::programLength(){
    return length;
}

unsigned int fetch::getPC(){
    return pc;
}
