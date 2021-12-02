#ifndef TAD_CACHE_H
#define TAD_CACHE_H

#include <stdbool.h>
#include <time.h>

#define sizeRAM 1000
#define sizeCache1 16
#define sizeCache2 32
#define sizeCache3 64
#define sizeProgram 10001
#define MIN_VALUE -2147483648

typedef struct {
    double addBlock;
    double addWord;

} Address;

typedef struct {
    double words[4];
    int addBlock;
    bool updated;
    int cost;
    int cacheHit;
    int sec;
    bool isEmpty;
} MemoryBlock;

typedef struct {
    int opcode;
    Address add1;
    Address add2;
    Address add3;
} Instruction;

MemoryBlock *createRAM(MemoryBlock *RAM);
MemoryBlock *createEmptyCache(int size, MemoryBlock *cache);
MemoryBlock *createCacheWithData(int size, MemoryBlock *cache);

#endif