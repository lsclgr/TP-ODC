#ifndef MMU_H
#define MMU_H

#include "TAD_Cache.h"

MemoryBlock searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                             MemoryBlock *cache2, MemoryBlock *cache3);
MemoryBlock cachesTest(int, MemoryBlock *, MemoryBlock *,
                       MemoryBlock *, int, int);
int getOldestPosition(int sizeCache, MemoryBlock *cache);

#endif