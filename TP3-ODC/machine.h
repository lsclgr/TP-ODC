#ifndef MACHINE_H
#define MACHINE_H
#include <stdio.h>
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"

void machine(int PC, int interruption, Instruction* instruction, FILE* arq,
             MemoryBlock* RAM, MemoryBlock*, MemoryBlock*, MemoryBlock*);

void randomInstructions(int nInst, FILE* arq, MemoryBlock* RAM,
                        MemoryBlock* cache1, MemoryBlock* cache2,
                        MemoryBlock* cache3);

void generatorInstructions(int PC, FILE* arq, MemoryBlock* RAM,
                           MemoryBlock* cache1, MemoryBlock* cache2,
                           MemoryBlock* cache3);

void generatorInstructions2(int PC, FILE* arq, MemoryBlock* RAM,
                            MemoryBlock* cache1, MemoryBlock* cache2,
                            MemoryBlock* cache3);
#endif