//
//  Fetch.cpp
//  CS154Project3
//
//  Created by Johan Henkens on 5/12/12.
//  Copyright (c) 2012. All rights reserved.
//  For CS154 UCSB Spring 2012
//  Project 3 - Johan Henkens, Jay Mutarevic, Charlotte Hill
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
    maxPC = length*4;
    instructions = new int[length];
    for(int i = 0; i < length;i++){
        instructions[i]=instructionsVect[i];
    }
    pc = 0;
}

void Fetch::updatePC(Fetched* controlBits, bool zeroBit){
    if(controlBits==0){
        pc=getPCPlus4();
        return;
    }
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
    return instructions[pc>>2];
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

bool Fetch::isDone(){
    return pc>=maxPC;
}

Fetched* Fetch::performFetch(){
    if(isDone()){
        std::cout<<"Fetch instruction: "<<std::endl;
        return 0;
    }
    Fetched* brokenDown = Fetched::getControlBits(nextInstruction());
    std::cout<<"Fetch instruction: "<<brokenDown->printString<<std::endl;
    return brokenDown;
}

