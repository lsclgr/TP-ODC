#include <stdio.h>
#include <stdlib.h>

#define sizeRAM 1000
#define sizeCache1 16
#define sizeCache2 32
#define sizeCache3 64
#define sizeProgram 10001
#define MIN_VALUE -2147483648

typedef struct {
    int addBlock;
    int addWord;
} Address;

typedef struct {
    int words[4];
    int addBlock;
    int updated;
    int cost;
    int cacheHit;
} MemoryBlock;

typedef struct {
    int opcode;
    Address add1;
    Address add2;
    Address add3;
} Instruction;

MemoryBlock RAM[sizeRAM];
MemoryBlock cache1[sizeCache1];
MemoryBlock cache2[sizeCache2];
MemoryBlock cache3[sizeCache3];

void createRAM();
void createEmptyCache(int size, MemoryBlock *cache);
void createCacheWithData(int size, MemoryBlock *cache);

int main() {
    int ram;
    srand(time(NULL));
    return 0;
}

void createRAM() {
    for (int i = 0; i < sizeRAM; i++) {
        RAM->addBlock = i;
        RAM->updated = 1;
        RAM->cost = 0;
        RAM->cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            RAM->words[j] = rand() % 1000000;
        }
    }
}

void createEmptyCache(int size, MemoryBlock *cache) {
    for (int i = 0; i < size; i++) {
        cache->addBlock = MIN_VALUE;
        cache->updated = 1;
        cache->cost = 0;
        cache->cacheHit = 0;
    }
}

void createCacheWithData(int size, MemoryBlock *cache) {
    for (int i = 0; i < size; i++) {
        cache->addBlock = MIN_VALUE;
        cache->updated = 1;
        cache->cost = 0;
        cache->cacheHit = 0;
        for (int j = 0; j < 4; j++) {
            cache->words[j] = rand() % 1000000;
        }
    }
}