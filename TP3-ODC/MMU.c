#include "MMU.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// maquina -> cache1 -> cache2 -> cache3 -> RAM

int searchInMemories(Address add, FILE* arq, MemoryBlock* RAM,
                     MemoryBlock* cache1, MemoryBlock* cache2,
                     MemoryBlock* cache3, int* contTime, int HD_ou_SSD) {
    // arq = fopen("EM.dat", "rb+");

    // printf("entrou no search\n");

    MemoryBlock blockEM;
    int cost = 0;
    cost += 10;
    *contTime = *contTime + 1;

    for (int i = 0; i < sizeCache1; i++) {
        if (cache1[i].addBlock == add.addBlock) {
            cache1[i].cost = cost;
            cache1[i].cacheHit = 1;
            cache1[i].sec = *contTime;

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

    // printf("Verificou memorias\n");

    // primeiramente pegar o bloco do arquivo
    cost += 14;
    for (int i = 0; i < sizeRAM; i++) {
        if ((!RAM[i].updated) && RAM[i].isEmpty) {
            // pegar do arquivo
            // arq = fopen("EM.dat", "rb");
            // if (!arq) {
            //     perror("Erro ao abrir arquivo60");
            //     exit(1);
            // }
            if (HD_ou_SSD == 1) {
                printf("\nBuscando na Memória:\n");

                for (int w = 0; w <= 100; w = w + 25) {
                    printf("%d%%  ", w);
                    fflush(stdout);  // garante a escrita de dados imediatamente
                                     // na tela
                    // repare mod 10, eu limito a qtd de pontos q serao gerados
                    for (int z = 0; z < w / 8; z++) {
                        printf(".");
                    }
                    fflush(stdout);  // garante a escrita de dados imediatamente
                                     // na tela
                    usleep(500000);  // função espera por tempo, parametro em
                                     // microsegundos.
                    if (w != 100) {
                        limpa_linha();
                    }
                }
                printf("\n\n -- Bloco encontrado --\n\n");
            }
            fseek(arq, add.addBlock * sizeof(MemoryBlock),
                  SEEK_SET);  // usar o fseek para pegar o bloco
            fread(&blockEM, sizeof(MemoryBlock), 1, arq);
            RAM[i] = blockEM;
            // lembrar de salvar o bloco do arquivo em uma variavel do tipo
            // memoryBlock para passa-la direto para a ram ou então é preciso
            // usar cada prosição da tad
            RAM[i].cacheHit = 5;
            // fclose(arq);
            return cachesTest(i, RAM, cache1, cache2, cache3, cost, 3,
                              contTime);
        }
    }

    int RAMposition = getOldestPosition(sizeRAM, RAM, contTime);
    // printf("%d 78\n", RAMposition);

    RAM[RAMposition].updated = false;
    RAM[RAMposition].isEmpty = false;
    blockEM = RAM[RAMposition];
    // arq = fopen("EM.dat", "rb+");
    //  if (!arq) {
    //      perror("Erro ao abrir arquivo119");
    //      exit(1);
    //  }
    if (HD_ou_SSD == 1) {
        printf("\nBuscando na Memória:\n");

        for (int w = 0; w <= 100; w = w + 25) {
            printf("%d%%  ", w);
            fflush(stdout);  // garante a escrita de dados imediatamente na tela
            // repare mod 10, eu limito a qtd de pontos q serao gerados
            for (int z = 0; z < w / 8; z++) {
                printf(".");
            }
            fflush(stdout);  // garante a escrita de dados imediatamente na tela
            usleep(500000);  // função espera por tempo, parametro em
                             // microsegundos.
            if (w != 100) {
                limpa_linha();
            }
        }
        printf("\n\n -- Bloco encontrado --\n\n");
    }
    fseek(arq, RAM[RAMposition].addBlock * sizeof(MemoryBlock),
          SEEK_SET);  // usar o fseek para pegar o bloco
    MemoryBlock getEM;
    fread(&getEM, sizeof(MemoryBlock), 1, arq);
    fwrite(&blockEM, sizeof(MemoryBlock), 1, arq);
    // fclose(arq);
    RAM[RAMposition] = getEM;
    RAM[RAMposition].cacheHit = 5;
    return cachesTest(RAMposition, RAM, cache1, cache2, cache3, cost, 3,
                      contTime);
}
int cachesTest(int i, MemoryBlock* RAM, MemoryBlock* cache1,
               MemoryBlock* cache2, MemoryBlock* cache3, int cost, int isCache2,
               int* contTime) {
    MemoryBlock aux;
    int cache1position = 0, cache2position, cache3position, verify = 0;

    if (isCache2 == 3) {
        for (int j = 0; j < sizeCache3; j++) {
            if ((!cache3[j].updated) && cache3[j].isEmpty) {
                cache3position = j;
                verify = 1;
                break;
            }
        }
        if (verify == 0) {
            cache3position = getOldestPosition(sizeCache3, cache3, contTime);
        }

        aux = cache3[cache3position];
        cache3[cache3position] = RAM[i];
        RAM[i] = aux;
        isCache2 = 2;
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

    cache1[cache1position].sec = *contTime;

    cache1[cache1position].cost = cost;
    return cache1position;
}

int getOldestPosition(int sizeCache, MemoryBlock* cache, int* contTime) {
    int oldestTime = *contTime;
    // printf("tempo oldest position %d\n", contTime);
    int position = 0;
    for (int i = 0; i < sizeCache; i++) {
        if (cache[i].sec < oldestTime) {
            oldestTime = cache[i].sec;
            position = i;
        }
    }
    return position;
}

void limpa_linha() {
    int i;  // indice do caracter na linha
    int max_caracter =
        50;  // indica o maximo de caracter que a linha pode chegar a ter, para
             // linhas com mt texto, coloque um nmr bem maior
    printf(
        "\r");  // retorna para o inicio da linha que pretende reutilizar, isso
                // não limpa a linha, apenas posiciona cursor ao inicio da linha

    // Agora precisamos limpar a linha,
    // substitui todos os caracteres existentes por espaço em branco
    for (i = 0; i < max_caracter; i++) {
        printf(" ");  // vai preenchendo a linha com espaços em branco
    }

    printf("\r");  // volta ao inicio da linha , dessa vez ela está em branco.
}
