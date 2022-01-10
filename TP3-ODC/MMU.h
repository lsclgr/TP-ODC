#ifndef MMU_H
#define MMU_H

#include <stdio.h>

#include "TAD_Cache.h"

int searchInMemories(Address add, FILE *arq, MemoryBlock *RAM,
                     MemoryBlock *cache1, MemoryBlock *cache2,
                     MemoryBlock *cache3, int *contTime);
int cachesTest(int, MemoryBlock *, MemoryBlock *, MemoryBlock *, MemoryBlock *,
               int, int, int);
int getOldestPosition(int sizeCache, MemoryBlock *cache, int contTime);

#endif