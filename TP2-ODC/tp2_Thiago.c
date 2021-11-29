#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"

void machine(Instruction* instruction, MemoryBlock* RAM, MemoryBlock*,
             MemoryBlock*, MemoryBlock*);

int main() {
    MemoryBlock *RAM, *cache1, *cache2, *cache3;

    int ram;
    srand(time(NULL));

    return 0;
}

void machine(Instruction* instruction, MemoryBlock* RAM, MemoryBlock* cache1,
             MemoryBlock* cache2, MemoryBlock* cache3) {
    int PC = 0;
    int opcode = RAND_MAX;
    int custo = 0;

    int missC1 = 0;
    int hitC1 = 0;
    int missC2 = 0;
    int hitC2 = 0;

    while (opcode != -1) {
        Instruction inst = instruction[PC];
        opcode = inst.opcode;
        if (opcode != -1) {
            MemoryBlock memoryDataAdd1 =
                searchInMemories(inst.add1, RAM, cache1, cache2, cache3);
            MemoryBlock memoryDataAdd2 =
                searchInMemories(inst.add2, RAM, cache1, cache2, cache3);
            MemoryBlock memoryDataAdd3 =
                searchInMemories(inst.add3, RAM, cache1, cache2, cache3);
        }
    }
}