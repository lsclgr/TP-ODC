#include "TAD_Cache.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

MemoryBlock *createRAM(MemoryBlock *RAM) {
    RAM = (MemoryBlock *)malloc(sizeRAM * sizeof(MemoryBlock));
    for (int i = 0; i < sizeRAM; i++) {
        RAM[i].addBlock = i;
        RAM[i].updated = false;
        RAM[i].isEmpty = true;
        RAM[i].cost = 0;
        RAM[i].cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            RAM[i].words[j] = rand() % 1000000;
        }
    }
    return RAM;
}

MemoryBlock *createEmptyCache(int size, MemoryBlock *cache) {
    cache = (MemoryBlock *)malloc(size * sizeof(MemoryBlock));
    for (int i = 0; i < size; i++) {
        cache[i].addBlock = MIN_VALUE;
        cache[i].updated = false;
        cache[i].isEmpty = true;
        cache[i].cost = 0;
        cache[i].cacheHit = 0;
    }
    return cache;
}

MemoryBlock *createCacheWithData(int size, MemoryBlock *cache) {
    cache = (MemoryBlock *)malloc(size * sizeof(MemoryBlock));
    for (int i = 0; i < size; i++) {
        cache[i].addBlock = MIN_VALUE;
        cache[i].updated = false;
        cache[i].isEmpty = true;
        cache[i].cost = 0;
        cache[i].cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            cache[i].words[j] = rand() % 1000000;
        }
    }
    return cache;
}