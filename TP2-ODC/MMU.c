#include "MMU.h"

#include <stdio.h>
#include <stdlib.h>

MemoryBlock searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                             MemoryBlock *cache2, MemoryBlock *cache3) {
    // int cache1Position = (int)add.addBlock % sizeCache1;  // valor entre 0 e 15
    // int cache2Position = (int)add.addBlock % sizeCache2;  // valor entre 0 e 31
    // int cache3Position = (int)add.addBlock % sizeCache3;  // valor entre 0 e 63
    int cost = 0;
    // ADICIONAR TEMPO

    for (int i = 0; i < sizeCache1; i++) {
        if (cache1[i].addBlock == add.addBlock) {
            // ADICIONAR TEMPO

            cost += 10;
            cache1[i].cost = cost;
            cache1[i].cacheHit = 1;
            // cache1[cache1Position].updated = true
            return cache1[i];
        }
    }
    for (int i = 0; i < sizeCache2; i++) {
        if (cache2[i].addBlock == add.addBlock) {
            cost += 110;
            // pq ele não colocou o custo?
            cache2[i].cacheHit = 2;
            // cache2[cache2Position].updated = true
            return CachesTest(i, cache1, cache2, cache3, cost, 1);
        }
    }

    for (int i = 0; i < sizeCache3; i++) {
        if (cache3[i].addBlock == add.addBlock) {
            cost += 1110;
            // pq ele não colocou o custo?
            cache3[i].cacheHit = 3;
            // cache3[cache3Position].updated = true
            return CachesTest(i, cache1, cache2, cache3, cost, 0);
        }
    }
    else {
        // buscar na ram E O REPASSAR A C2 E DEPOIS A C1
        cost += 11110;
        if (!cache3[cache3Position].updated) {
            cache3[cache3Position] = RAM[(int)add.addBlock];
            cache3[cache3Position].cacheHit = 4;
            return CachesTest(cache1Position, cache2Position,
                              cache3Position, cache1, cache2, cache3,
                              cost, 0);

        } else {
            RAM[cache3[cache3Position].addBlock] = cache3[cache3Position];
            RAM[cache3[cache3Position].addBlock].updated = false;  // virar false

            cache3[cache3Position] = RAM[(int)add.addBlock];
            cache3[cache3Position].cacheHit = 4;
            return CachesTest(cache1Position, cache2Position,
                              cache3Position, cache1, cache2, cache3,
                              cost, 0);
            ;
        }
    }
}
}

MemoryBlock CachesTest(int i, MemoryBlock *cache1,
                       MemoryBlock *cache2, MemoryBlock *cache3, int cost,
                       int isCache2) {
    MemoryBlock aux;
    if (!isCache2) {
        if (!cache2->updated) {
            cache2[cache2Position] = cache3[cache3Position];
        } else {
            aux = cache2[cache2Position];
            cache2[cache2Position] = cache3[cache3Position];
            cache3[cache3Position] = aux;
        }
    }
    if (!cache1->updated) {
        cache1[cache1Position] = cache2[cache2Position];
    } else {
        aux = cache1[cache1Position];
        cache1[cache1Position] = cache2[cache2Position];
        cache2[cache2Position] = aux;
    }
    cache1[cache1Position].cost = cost;
    return cache1[cache1Position];
}