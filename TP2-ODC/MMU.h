#ifndef MMU_H
#define MMU_H

#include "TAD_Cache.h"

MemoryBlock searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                             MemoryBlock *cache2, MemoryBlock *cache3);
MemoryBlock CachesTest(int, int, int, MemoryBlock *, MemoryBlock *,
                       MemoryBlock *, int, int);

#endif