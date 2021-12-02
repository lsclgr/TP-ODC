#include "machine.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    int content1, content2;
    MemoryBlock memoryData;
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

                memoryData.addBlock = inst.add1.addBlock;
                memoryData.words[0] = inst.add1.addWord;
                memoryData.updated = true;
                memoryData.isEmpty = true;
                memoryData.cost = 0;
                memoryData.cacheHit = 0;
                setCache(memoryData, RAM, cache1, cache2, cache3);
                break;
            case 1:
                content1 = memoryDataAdd1.words[(int)inst.add1.addWord];
                content2 = memoryDataAdd2.words[(int)inst.add2.addWord];
                printf("%d\n", (int)inst.add2.addWord);
                int sum = content1 + content1;
                memoryDataAdd3.words[(int)inst.add3.addWord] = sum;
                memoryDataAdd3.updated = true;
                setCache(memoryDataAdd3, RAM, cache1, cache2, cache3);

                printf("Somando %d com %d e gerando %d\n", content1, content2,
                       sum);
                break;
            case 2:
                content1 = memoryDataAdd1.words[(int)inst.add1.addWord];
                content2 = memoryDataAdd2.words[(int)inst.add2.addWord];
                int sub = content1 + content1;
                memoryDataAdd3.words[(int)inst.add3.addWord] = sub;
                memoryDataAdd3.updated = true;
                setCache(memoryDataAdd3, RAM, cache1, cache2, cache3);

                printf("Subtraindo %d com %d e gerando %d\n", content1,
                       content2, sub);
                break;
            case 3:
                instruction[PC].add1.addWord = memoryDataAdd1.words[0];
                break;
            default:
                break;
        }
        PC++;
    }
}

void setCache(MemoryBlock memoryData, MemoryBlock* RAM, MemoryBlock* cache1,
              MemoryBlock* cache2, MemoryBlock* cache3) {
    int verify = 0, cache1position, cache2position, cache3position;

    for (int j = 0; j < sizeCache1; j++) {
        if ((!cache1[j].updated) && cache1[j].isEmpty) {
            cache1position = j;
            verify = 1;
        }
    }
    if (verify) {
        cache1[cache1position] = memoryData;
        return;
    } else {
        cache1position = getOldestPosition(sizeCache1, cache1);
        verify = 0;
        for (int j = 0; j < sizeCache2; j++) {
            if ((!cache2[j].updated) && cache2[j].isEmpty) {
                cache2position = j;
                verify = 1;
            }
        }
        if (verify) {
            cache2[cache2position] = cache1[cache1position];
            cache1[cache1position] = memoryData;
            return;
        } else {
            cache2position = getOldestPosition(sizeCache2, cache2);
            verify = 0;
            for (int j = 0; j < sizeCache3; j++) {
                if ((!cache3[j].updated) && cache3[j].isEmpty) {
                    cache3position = j;
                    verify = 1;
                }
            }
            if (verify) {
                cache3[cache3position] = cache2[cache2position];
                cache2[cache2position] = cache1[cache1position];
                cache1[cache1position] = memoryData;
                return;
            } else {
                RAM[cache3[cache3position].addBlock] = cache3[cache3position];
                RAM[cache3[cache3position].addBlock].updated =
                    false;  // virar false
                RAM[cache3[cache3position].addBlock].isEmpty =
                    false;  // virar false
                cache3[cache3position] = cache2[cache2position];
                cache2[cache2position] = cache1[cache1position];
                cache1[cache1position] = memoryData;
                return;
            }
        }
    }
}

void randomInstructions(MemoryBlock* RAM, MemoryBlock* cache1,
                        MemoryBlock* cache2, MemoryBlock* cache3) {
    Instruction *instruction, inst;

    instruction = malloc(1001 * sizeof(Instruction));

    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        inst.opcode = rand() % 4;
        inst.add1.addBlock = rand() % 1000;
        inst.add1.addWord = rand() % 4;

        inst.add2.addBlock = rand() % 1000;
        inst.add2.addWord = rand() % 4;

        inst.add3.addBlock = rand() % 1000;
        inst.add3.addWord = rand() % 4;

        instruction[i] = inst;
    }

    instruction[1000].opcode = -1;
    machine(instruction, RAM, cache1, cache2, cache3);
}