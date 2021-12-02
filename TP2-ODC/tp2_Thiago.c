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
    MemoryBlock memoryDataAdd1;

    MemoryBlock memoryDataAdd2;

    MemoryBlock memoryDataAdd3;
    Instruction inst;

    while (opcode != -1) {
        inst = instruction[PC];
        opcode = inst.opcode;
        if (opcode != -1) {
            memoryDataAdd1 =
                searchInMemories(inst.add1, RAM, cache1, cache2, cache3);
            memoryDataAdd2 =
                searchInMemories(inst.add2, RAM, cache1, cache2, cache3);
            memoryDataAdd3 =
                searchInMemories(inst.add3, RAM, cache1, cache2, cache3);

            cost += memoryDataAdd1.cost;
            cost += memoryDataAdd2.cost;
            cost += memoryDataAdd3.cost;

            switch (memoryDataAdd1.cacheHit) {
                case 1:
                    hitC1++;
                    break;
                case 2:
                    missC1++;
                    hitC2++;
                    break;
                case 3:
                    missC1++;
                    missC2++;
                    hitC3++;
                    break;

                default:
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
            }

            switch (memoryDataAdd2.cacheHit) {
                case 1:
                    hitC1++;
                    break;
                case 2:
                    missC1++;
                    hitC2++;
                    break;
                case 3:
                    missC1++;
                    missC2++;
                    hitC3++;
                    break;

                default:
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
            }

            switch (memoryDataAdd3.cacheHit) {
                case 1:
                    hitC1++;
                    break;
                case 2:
                    missC1++;
                    hitC2++;
                    break;
                case 3:
                    missC1++;
                    missC2++;
                    hitC3++;
                    break;

                default:
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
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
                int content1 = memoryDataAdd1.words[(int)inst.add1.addWord];
                int content2 = memoryDataAdd2.words[(int)inst.add2.addWord];
                int sum = content1 + content1;
                memoryDataAdd3.words[(int)inst.add3.addWord] = sum;

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