#ifndef MMU_H
#define MMU_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "TAD_Cache.h"
int searchInMemories(Address add, FILE* arq, MemoryBlock* RAM,
                     MemoryBlock* cache1, MemoryBlock* cache2,
                     MemoryBlock* cache3, int* contTime, int HD_ou_SSD);
int cachesTest(int, MemoryBlock*, MemoryBlock*, MemoryBlock*, MemoryBlock*,
               int cost, int isCache2, int* contTime);
int getOldestPosition(int sizeCache, MemoryBlock* cache, int* contTime);
void limpa_linha(void);
#endif