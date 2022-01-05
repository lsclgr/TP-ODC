#include "MMU.h"

#include <stdio.h>
#include <stdlib.h>

// maquina -> cache1 -> cache2 -> cache3 -> RAM

int searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                     MemoryBlock *cache2, MemoryBlock *cache3, int contTime) {
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
            cache1[i].sec = ++contTime;

            return i;
        }
    }

    cost += 11;
    for (int i = 0; i < sizeCache2; i++) {
        if (cache2[i].addBlock == add.addBlock) {
            cache2[i].cacheHit = 2;
            // cache2[cache2Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 1, contTime);
        }
    }

    cost += 12;
    for (int i = 0; i < sizeCache3; i++) {
        if (cache3[i].addBlock == add.addBlock) {
            cache3[i].cacheHit = 3;
            // cache3[cache3Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 0, contTime);
        }
    }

    cost += 13;
    for (int i = 0; i < sizeCache3; i++) {
        // buscar na RAM E O REPASSAR A C3 E DEPOIS A C2 E DEPOIS A C1
        if ((!cache3[i].updated) && cache3[i].isEmpty) {
            cache3[i] = RAM[(int)add.addBlock];
            cache3[i].cacheHit = 4;
            // cache3[i].sec = sec;
            //  printf("\n55\n");

            return cachesTest(i, cache1, cache2, cache3, cost, 0, contTime);
        }
        // printf("59 cache3[%d] = %d ", i, cache3[i].addBlock);
    }

    int cache3Position = getOldestPosition(sizeCache3, cache3, contTime);
    // printf("\n61cache 3 position %d\n", cache3Position);
    // printf("62 :p %d\n", cache3[cache3Position].addBlock);
    RAM[cache3[cache3Position].addBlock] = cache3[cache3Position];
    RAM[cache3[cache3Position].addBlock].updated = false;  // virar false
    RAM[cache3[cache3Position].addBlock].isEmpty = false;  // virar false

    cache3[cache3Position] = RAM[(int)add.addBlock];
    cache3[cache3Position].cacheHit = 4;
    // cache3[cache3Position].sec = sec;
    // printf("70 70 e 70 dnv\n");
    return cachesTest(cache3Position, cache1, cache2, cache3, cost, 0,
                      contTime);
}
int cachesTest(int i, MemoryBlock *cache1, MemoryBlock *cache2,
               MemoryBlock *cache3, int cost, int isCache2, int contTime) {
    MemoryBlock aux;
    int cache1position, cache2position, verify = 0;
    time_t sec;
    time(&sec);

    if (!isCache2) {
        for (int j = 0; j < sizeCache2; j++) {
            if ((!cache2[j].updated) && cache2[j].isEmpty) {
                cache2position = j;
                verify = 1;
                break;
            }
            // printf("89 cache2[%d] = %d ", j, cache2[j].addBlock);
        }
        if (verify == 0) {
            cache2position = getOldestPosition(sizeCache2, cache2, contTime);
            // printf("\ncache 2 position %d\n", cache2position);
        }
        // printf("\ncache2[%d] %d\n", cache2position,
        //    cache2[cache2position].addBlock);
        // printf("\ncache3[%d] %d\n", i, cache3[i].addBlock);
        aux = cache2[cache2position];
        cache2[cache2position] = cache3[i];
        cache3[i] = aux;
        // cache2[cache2position].sec = sec;
    } else {
        cache2position = i;
    }

    verify = 0;
    for (int j = 0; j < sizeCache1; j++) {
        if ((!cache1[j].updated) && cache1[j].isEmpty) {
            cache1position = j;
            verify = 1;
            break;
        }
    }
    if (verify == 0) {
        cache1position = getOldestPosition(sizeCache1, cache1, contTime);
        // printf("\ncache 1 position %d\n", cache1position);
        // printf("cache 2 position %d\n", cache2position);
    }

    aux = cache1[cache1position];
    cache1[cache1position] = cache2[cache2position];
    cache2[cache2position] = aux;

    cache1[cache1position].sec = ++contTime;

    cache1[cache1position].cost = cost;
    // printf("\n121cache 1 position %d\n", cache1position);
    return cache1position;
}

int getOldestPosition(int sizeCache, MemoryBlock *cache, int contTime) {
    time_t oldestTime = ++contTime;
    time(&oldestTime);
    int position = 0;
    // printf("\n\n size cache: %d\n", sizeCache);
    for (int i = 1; i < sizeCache; i++) {
        // printf("\n i dentro do for: %d\n", i);
        // printf("cache[%d].sec %ld \n", i, oldestTime);
        if (cache[i].sec < oldestTime) {
            oldestTime = cache[i].sec;
            position = i;
        }
    }
    // printf("\nposition antes do retorno: %d\n", position);
    return position;
}