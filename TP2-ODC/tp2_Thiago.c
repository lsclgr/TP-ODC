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
    int cost = 0;

    int missC1 = 0;
    int hitC1 = 0;
    int missC2 = 0;
    int hitC2 = 0;
    int missC3 = 0;
    int hitC3 = 0;

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

            cost += memoryDataAdd1.cost;
            cost += memoryDataAdd2.cost;
            cost += memoryDataAdd3.cost;

            if (memoryDataAdd1.cacheHit == 1) {
                hitC1++;
            } else if (memoryDataAdd1.cacheHit == 2) {
                missC1++;
                hitC2++;
            } else if (memoryDataAdd1.cacheHit == 3) {
                missC1++;
                missC2++;
                hitC3++;
            } else {
                missC1++;
                missC2++;
                missC3++;
            }

            if (memoryDataAdd2.cacheHit == 1) {
                hitC1++;
            } else if (memoryDataAdd2.cacheHit == 2) {
                missC1++;
                hitC2++;
            } else if (memoryDataAdd2.cacheHit == 3) {
                missC1++;
                missC2++;
                hitC3++;
            } else {
                missC1++;
                missC2++;
                missC3++;
            }

            if (memoryDataAdd3.cacheHit == 1) {
                hitC1++;
            } else if (memoryDataAdd3.cacheHit == 2) {
                missC1++;
                hitC2++;
            } else if (memoryDataAdd3.cacheHit == 3) {
                missC1++;
                missC2++;
                hitC3++;
            } else {
                missC1++;
                missC2++;
                missC3++;
            }

            printf("Custo até o momento do programa em execução: %d\n", cost);
            printf(
                "Hits e Misses até o momento - C1 hit %d | C1 miss %d | C2 hit "
                "%d | C2 miss: %d | C3 hit %d | C3 miss: %d\n",
                hitC1, missC1, hitC2, missC2, hitC3, missC3);
        }

        switch (opcode) {
            case 0:
                /* code */
                break;
            case 1:
                /* code */
                break;
            case 2:
                /* code */
                break;
            default:
                break;
        }
        PC++;
    }
}