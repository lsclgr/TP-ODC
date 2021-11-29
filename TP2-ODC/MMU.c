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
    // ADICIONAR TEMPO

    for (int i = 0; i < sizeCache1; i++) {
        if (cache1[i].addBlock == add.addBlock) {
            cost += 10;
            cache1[i].cost = cost;
            cache1[i].cacheHit = 1;
            // cache1[i].updated = true;
            cache1[i].sec = sec;

            return cache1[i];
        }
    }
    for (int i = 0; i < sizeCache2; i++) {
        if (cache2[i].addBlock == add.addBlock) {
            cost += 110;
            // pq ele não colocou o custo?
            cache2[i].cacheHit = 2;
            // cache2[cache2Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 1);
        }
    }

    for (int i = 0; i < sizeCache3; i++) {
        if (cache3[i].addBlock == add.addBlock) {
            cost += 1110;
            // pq ele não colocou o custo?
            cache3[i].cacheHit = 3;
            // cache3[cache3Position].updated = true
            return cachesTest(i, cache1, cache2, cache3, cost, 0);
        }
    }
    for (int i = 0; i < sizeCache3; i++) {
        // buscar na RAM E O REPASSAR A C3 E DEPOIS A C2 E DEPOIS A C1
        cost += 11110;
        if (!cache3[i].updated) {
            cache3[i] = RAM[(int)add.addBlock];
            cache3[i].cacheHit = 4;
            return cachesTest(i, cache1, cache2, cache3, cost, 0);
        }
    }
    //  LANCE DO TEMPO
    //  Funcao PARA VERIFICAR A POSICAO QUE ESTA A MAIS TEMPO SEM SER CONVOCADA
    //  (MAIOR TEMPO)

    int cache3Position = getOldestPosition(sizeCache3, cache3);

    // RAM[cache3[cache3Position].addBlock] = cache3[cache3Position];
    // RAM[cache3[cache3Position].addBlock].updated = false;  // virar false

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
            if (!cache2[j].updated) {
                cache2position = j;
                verify = 1;
            }
        }
        if (verify == 0) {
            cache2position = getOldestPosition(sizeCache2, cache2);
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
        if (!cache1[j].updated) {
            cache1position = j;
            verify = 1;
        }
    }
    if (verify == 0) {
        cache1position = getOldestPosition(sizeCache1, cache1);
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
    time_t oldestTime;
    time(&oldestTime);
    int position;

    for (int i = 0; i < sizeCache; i++) {
        if (cache[i].sec < oldestTime) {
            oldestTime = cache[i].sec;
            position = i;
        }
    }

    // if (sizeCache == sizeCache1) {
    //     for (int i = 0; i < sizeCache1; i++) {
    //         if (cache[i].sec < oldestTime) {
    //             oldestTime = cache[i].sec;
    //             position = i;
    //         }
    //     }
    // }
    // if (sizeCache == sizeCache2) {
    //     for (int i = 0; i < sizeCache2; i++) {
    //         if (cache[i].sec < oldestTime) {
    //             oldestTime = cache[i].sec;
    //             position = i;
    //         }
    //     }
    // }
    // if (sizeCache == sizeCache3) {
    //     for (int i = 0; i < sizeCache3; i++) {
    //         if (cache[i].sec < oldestTime) {
    //             oldestTime = cache[i].sec;
    //             position = i;
    //         }
    //     }
    // }
    return position;
}