#ifndef MACHINE_H
#define MACHINE_H
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"

void setCache(MemoryBlock memoryData, MemoryBlock* RAM, MemoryBlock* cache1,
              MemoryBlock* cache2, MemoryBlock* cache3);

void machine(int PC, int interruption, Instruction* instruction,
             MemoryBlock* RAM, MemoryBlock*, MemoryBlock*, MemoryBlock*);

void randomInstructions(int nInst, Instruction** instInterruption,
                        MemoryBlock* RAM, MemoryBlock* cache1,
                        MemoryBlock* cache2, MemoryBlock* cache3);

void generatorInstructions(MemoryBlock* RAM, MemoryBlock* cache1,
                           MemoryBlock* cache2, MemoryBlock* cache3);

#endif