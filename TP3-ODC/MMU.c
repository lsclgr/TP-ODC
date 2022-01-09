#include "MMU.h"

#include <stdio.h>
#include <stdlib.h>

// maquina -> cache1 -> cache2 -> cache3 -> RAM

int searchInMemories(Address add, MemoryBlock *RAM, MemoryBlock *cache1,
                     MemoryBlock *cache2, MemoryBlock *cache3, int contTime) {
    FILE *arq;
    arq = fopen("EM.dat", "rb+");
    MemoryBlock blockEM;
    int cost = 0;
    cost += 10;
    contTime++;
    for (int i = 0; i < sizeCache1; i++) {
        if (cache1[i].addBlock == add.addBlock) {
            cache1[i].cost = cost;
            cache1[i].cacheHit = 1;
            cache1[i].sec = contTime;

            return i;
        }
    }

    cost += 11;
    for (int i = 0; i < sizeCache2; i++) {
        if (cache2[i].addBlock == add.addBlock) {
            cache2[i].cacheHit = 2;
            return cachesTest(i, RAM, cache1, cache2, cache3, cost, 1,
                              contTime);
        }
    }

    cost += 12;
    for (int i = 0; i < sizeCache3; i++) {
        if (cache3[i].addBlock == add.addBlock) {
            cache3[i].cacheHit = 3;
            return cachesTest(i, RAM, cache1, cache2, cache3, cost, 2,
                              contTime);
        }
    }

    cost += 13;
    for (int i = 0; i < sizeRAM; i++) {
        if (RAM[i].addBlock == add.addBlock) {
            RAM[i].cacheHit = 4;
            return cachesTest(i, RAM, cache1, cache2, cache3, cost, 3,
                              contTime);
        }
    }

    // primeiramente pegar o bloco do arquivo
    cost += 14;
    for (int i = 0; i < sizeRAM; i++) {
        if ((!RAM[i].updated) && RAM[i].isEmpty) {
            // pegar do arquivo
            //arq = fopen("EM.dat", "r");
            if (!arq) {
                perror("Erro ao abrir arquivo");
                exit(1);
            }
            fseek(arq, add.addBlock * sizeof(MemoryBlock),
                  SEEK_SET);  // usar o fseek para pegar o bloco
            fread(&blockEM, sizeof(MemoryBlock), 1, arq);
            RAM[i] = blockEM;
            // lembrar de salvar o bloco do arquivo em uma variavel do tipo
            // memoryBlock para passa-la direto para a ram ou então é preciso
            // usar cada prosição da tad
            RAM[i].cacheHit = 5;
            fclose(arq);
            return cachesTest(i, RAM, cache1, cache2, cache3, cost, 3,
                              contTime);
        }
    }

    // verificar se vai usar essa porra aqui

    // cost += 13;
    // for (int i = 0; i < sizeCache3; i++) {
    //     if ((!cache3[i].updated) && cache3[i].isEmpty) {
    //         cache3[i] = RAM[(int)add.addBlock];
    //         cache3[i].cacheHit = 4;

    //         return cachesTest(i, cache1, cache2, cache3, cost, 2, contTime);
    //     }
    // }

    // cost += 14;
    // for (int i = 0; i < sizeRAM; i++) {
    //     if ((!RAM[i].updated) && RAM[i].isEmpty) {
    //         // pegar do arquivo
    //         // RAM[i] = RAM[(int)add.addBlock];
    //         RAM[i].cacheHit = 4;

    //         return cachesTest(i, cache1, cache2, cache3, cost, 3, contTime);
    //     }
    // }

    // implementar HD blablabla
    // int cache3Position = getOldestPosition(sizeCache3, cache3, contTime);
    // RAM[cache3[cache3Position].addBlock] = cache3[cache3Position];
    // RAM[cache3[cache3Position].addBlock].updated = false;  // virar false
    // RAM[cache3[cache3Position].addBlock].isEmpty = false;  // virar false

    // cache3[cache3Position] = RAM[(int)add.addBlock];
    // cache3[cache3Position].cacheHit = 5;
    // return cachesTest(cache3Position, RAM, cache1, cache2, cache3, cost, 0,
    //                   contTime);

    int RAMposition = getOldestPosition(sizeRAM, RAM, contTime);
    printf("%d\n", RAMposition);

    RAM[RAMposition].updated = false;
    RAM[RAMposition].isEmpty = false;
    blockEM = RAM[RAMposition];
    //arq = fopen("EM.dat", "rb+");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fseek(arq, RAM[RAMposition].addBlock * sizeof(MemoryBlock),
          SEEK_SET);  // usar o fseek para pegar o bloco
    MemoryBlock getEM;
    fread(&getEM, sizeof(MemoryBlock), 1, arq);
    fwrite(&blockEM, sizeof(MemoryBlock), 1, arq);
    fclose(arq);
    RAM[RAMposition] = getEM;
    RAM[RAMposition].cacheHit = 5;
    return cachesTest(RAMposition, RAM, cache1, cache2, cache3, cost, 3,
                      contTime);
}
int cachesTest(int i, MemoryBlock *RAM, MemoryBlock *cache1,
               MemoryBlock *cache2, MemoryBlock *cache3, int cost, int isCache2,
               int contTime) {
    MemoryBlock aux;
    int cache1position, cache2position, cache3position, verify = 0;

    if (isCache2 == 3) {
        for (int j = 0; j < sizeCache3; j++) {
            if ((!cache3[j].updated) && cache3[j].isEmpty) {
                cache3position = j;
                verify = 1;
                break;
            }
        }
        if (verify == 0) {
            cache3position = getOldestPosition(sizeCache2, cache2, contTime);
        }

        aux = cache3[cache3position];
        cache3[cache3position] = RAM[i];
        RAM[i] = aux;
    } else if (isCache2 == 2) {
        cache3position = i;
    }
    verify = 0;
    if (isCache2 == 2) {
        for (int j = 0; j < sizeCache2; j++) {
            if ((!cache2[j].updated) && cache2[j].isEmpty) {
                cache2position = j;
                verify = 1;
                break;
            }
        }
        if (verify == 0) {
            cache2position = getOldestPosition(sizeCache2, cache2, contTime);
        }
        aux = cache2[cache2position];
        cache2[cache2position] = cache3[cache3position];
        cache3[cache3position] = aux;
    }
    if (isCache2) {
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
    }

    aux = cache1[cache1position];
    cache1[cache1position] = cache2[cache2position];
    cache2[cache2position] = aux;

    cache1[cache1position].sec = contTime;

    cache1[cache1position].cost = cost;
    return cache1position;
}

int getOldestPosition(int sizeCache, MemoryBlock *cache, int contTime) {
    int oldestTime = contTime;
    int position = 0;
    for (int i = 0; i < sizeCache; i++) {
        if (cache[i].sec < oldestTime) {
            oldestTime = cache[i].sec;
            position = i;
        }
    }
    return position;
}