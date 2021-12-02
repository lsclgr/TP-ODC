#ifndef MACHINE_H
#define MACHINE_H
#include "MMU.h"
#include "TAD_Cache.h"

void setCache(MemoryBlock memoryData, MemoryBlock* RAM, MemoryBlock* cache1,
              MemoryBlock* cache2, MemoryBlock* cache3);

void machine(Instruction* instruction, MemoryBlock* RAM, MemoryBlock*,
             MemoryBlock*, MemoryBlock*);

void randomInstructions(MemoryBlock* RAM, MemoryBlock* cache1,
                        MemoryBlock* cache2, MemoryBlock* cache3);

#endif