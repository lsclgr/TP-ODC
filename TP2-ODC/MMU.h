#ifndef MMU_H
#define MMU_H

#include "TAD_Cache.h"

MemoryBlock searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1, MemoryBlock *cache2, MemoryBlock *cache3);
MemoryBlock CachesTest(int Cache1Position, int Cache2Position, int Cache3Position, MemoryBlock *cache1, MemoryBlock *cache2, MemoryBlock *cache3, int cost);

#endif