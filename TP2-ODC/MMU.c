#include "MMU.h"

#include <stdio.h>
#include <stdlib.h>

// maquina -> cache1 -> cache2 -> cache3 -> RAM

MemoryBlock searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                             MemoryBlock *cache2, MemoryBlock *cache3) {
    // int cache1Position = (int)add.addBlock % sizeCache1;  // valor entre 0 e
    // 15 int cache2Position = (int)add.addBlock % sizeCache2;  // valor entre 0
    // e 31 int cache3Position = (int)add.addBlock % sizeCache3;  // valor entre
    // 0 e 63
    int cost = 0;
    time_t sec;
    time(&sec);

    cost += 10;
    for (int i = 0; i < sizeCache1; i++) {
        if (cache1[i].addBlock == add.addBlock) {
            cache1[i].cost = cost;
            cache1[i].cacheHit = 1;
            // cache1[i].updated = true;
            cache1[i].sec = sec;

            return cache1[i];
        }
    }

    cost += 100;
    for (int i = 0; i < sizeCache2; i++) {
        if (cache2[i].addBlock == add.addBlock) {
            cache2[i].cacheHit = 2;
            // cache2[cache2Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 1);
        }
    }

    cost += 1000;
    for (int i = 0; i < sizeCache3; i++) {
        if (cache3[i].addBlock == add.addBlock) {
            cache3[i].cacheHit = 3;
            // cache3[cache3Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 0);
        }
    }

    cost += 10000;
    for (int i = 0; i < sizeCache3; i++) {
        // buscar na RAM E O REPASSAR A C3 E DEPOIS A C2 E DEPOIS A C1
        if ((!cache3[i].updated) && cache3[i].isEmpty) {
            cache3[i] = RAM[(int)add.addBlock];
            cache3[i].cacheHit = 4;
            cache3[i].sec = sec;

            return cachesTest(i, cache1, cache2, cache3, cost, 0);
        }
    }

    int cache3Position = getOldestPosition(sizeCache3, cache3);
    printf("\ncache 3 position %d\n", cache3Position);

    RAM[cache3[cache3Position].addBlock] = cache3[cache3Position];
    RAM[cache3[cache3Position].addBlock].updated = false;  // virar false
    RAM[cache3[cache3Position].addBlock].isEmpty = false;  // virar false

    cache3[cache3Position] = RAM[(int)add.addBlock];
    cache3[cache3Position].cacheHit = 4;
    cache3[cache3Position].sec = sec;
    return cachesTest(add.addBlock, cache1, cache2, cache3, cost, 0);
}
MemoryBlock cachesTest(int i, MemoryBlock *cache1, MemoryBlock *cache2,
                       MemoryBlock *cache3, int cost, int isCache2) {
    MemoryBlock aux;
    int cache1position, cache2position, verify = 0;
    time_t sec;
    time(&sec);

    if (!isCache2) {
        for (int j = 0; j < sizeCache2; j++) {
            if ((!cache2[j].updated) && cache2[j].isEmpty) {
                cache2position = j;
                verify = 1;
            }
        }
        if (verify == 0) {
            cache2position = getOldestPosition(sizeCache2, cache2);
            printf("\ncache 2 position %d\n", cache2position);
            aux = cache2[cache2position];
            cache2[cache2position] = cache3[i];
            cache3[i] = aux;
        } else {
            cache2[cache2position] = cache3[i];
        }
        cache2[cache2position].sec = sec;
    }

    verify = 0;
    for (int j = 0; j < sizeCache1; j++) {
        if ((!cache1[j].updated) && cache1[j].isEmpty) {
            cache1position = j;
            verify = 1;
        }
    }
    if (verify == 0) {
        cache1position = getOldestPosition(sizeCache1, cache1);
        printf("\ncache 1 position %d\n", cache1position);
        aux = cache1[cache1position];
        cache1[cache1position] = cache2[cache2position];
        cache2[cache2position] = aux;
    } else {
        cache1[cache1position] = cache2[cache2position];
    }

    cache1[cache1position].sec = sec;

    cache1[cache1position].cost = cost;
    return cache1[cache1position];
}

int getOldestPosition(int sizeCache, MemoryBlock *cache) {
    time_t oldestTime = cache[0].sec;
    // time(&oldestTime);
    int position = 0;
    printf("\n\n size cache: %d\n", sizeCache);
    for (int i = 1; i < sizeCache; i++) {
        // printf("\n i dentro do for: %d\n", i);
        if (cache[i].sec < oldestTime) {
            oldestTime = cache[i].sec;
            position = i;
        }
    }
    // printf("\nposition antes do retorno: %d\n", position);
    return position;
}