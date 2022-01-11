#ifndef MACHINE_H
#define MACHINE_H
#include <stdio.h>
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"

void machine(int PC, int interruption, Instruction* instruction, FILE* arquivo,
             FILE* arq, MemoryBlock* RAM, MemoryBlock*, MemoryBlock*,
             MemoryBlock*, int HD_ou_SSD);

void randomInstructions(int nInst, FILE* arquivo, FILE* arq, MemoryBlock* RAM,
                        MemoryBlock* cache1, MemoryBlock* cache2,
                        MemoryBlock* cache3, int HD_ou_SSD);

void generatorInstructions(int PC, FILE* arquivo, FILE* arq, MemoryBlock* RAM,
                           MemoryBlock* cache1, MemoryBlock* cache2,
                           MemoryBlock* cache3, int HD_ou_SSD);

// void generatorInstructions2(int PC, FILE* arquivo, FILE* arq, MemoryBlock*
// RAM,
//                             MemoryBlock* cache1, MemoryBlock* cache2,
//                             MemoryBlock* cache3);

#endif