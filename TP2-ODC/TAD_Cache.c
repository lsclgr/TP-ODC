#include "TAD_Cache.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

MemoryBlock *createRAM(MemoryBlock *RAM, int size) {
    RAM = (MemoryBlock *)malloc(size * sizeof(MemoryBlock));
    for (int i = 0; i < sizeRAM; i++) {
        RAM->addBlock = i;
        RAM->updated = false;
        RAM->cost = 0;
        RAM->cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            RAM->words[j] = rand() % 1000000;
        }
    }
    return RAM;
}

MemoryBlock *createEmptyCache(int size, MemoryBlock *cache) {
    cache = (MemoryBlock *)malloc(size * sizeof(MemoryBlock));
    for (int i = 0; i < size; i++) {
        cache->addBlock = MIN_VALUE;
        cache->updated = false;
        cache->cost = 0;
        cache->cacheHit = 0;
    }
    return cache;
}

MemoryBlock *createCacheWithData(int size, MemoryBlock *cache) {
    cache = (MemoryBlock *)malloc(size * sizeof(MemoryBlock));
    for (int i = 0; i < size; i++) {
        cache->addBlock = MIN_VALUE;
        cache->updated = false;
        cache->cost = 0;
        cache->cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            cache->words[j] = rand() % 1000000;
        }
    }
    return cache;
}