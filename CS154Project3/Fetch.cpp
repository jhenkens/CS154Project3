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
#include "Fetch.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

Fetch::Fetch(char* filename){
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

void Fetch::updatePC(Decoded* controlBits, bool zeroBit){
    switch (controlBits->bType) {
        case 0:
            pc=getPCPlus4();
            return;
        case 1:
            //Jump
            pc=controlBits->jumpAddr*4;
            break;
        case 2:
            //BGE
            if(zeroBit){
                pc+=4*controlBits->immi;
            }
            break;
        case 3:
            //BNE
            if(!zeroBit){
                pc+=4*controlBits->immi;
            }
            break;
        default:
            break;
    }
}

int Fetch::nextInstruction(){
    int result = instructions[pc>>2];
    return result;
}

int Fetch::programLength(){
    return length;
}

unsigned int Fetch::getPC(){
    return pc;
}
unsigned int Fetch::getPCPlus4(){
    return pc+4;
}
