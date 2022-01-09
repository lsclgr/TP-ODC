#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "MMU.h"
#include "TAD_Cache.h"
#include "machine.h"

int main() {
    MemoryBlock *HD = NULL, *RAM = NULL, *cache1 = NULL, *cache2 = NULL,
                *cache3 = NULL;
    FILE *arq;
    int ret;
    int y = 1000;

    arq = fopen("EM.dat", "wb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    srand(time(NULL));

    HD = createEM(HD, sizeHD);
    // criar arquivo e salvar nele o HD
    // escreve os valores gerados no final do arquivo
    ret = fwrite(HD, sizeof(MemoryBlock), sizeHD, arq);
    if (ret)
        printf("Gravou %d valores com sucesso!\n", ret);
    else
        printf("Erro ao gravar...\n");

    // fecha o arquivo
    fclose(arq);

    MemoryBlock v;

    // abre o arquivo em modo leitura
    arq = fopen("EM.dat", "r");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // lê e imprime os valores contidos no arquivo
    fread(&v, sizeof(MemoryBlock), 1, arq);
    while (!feof(arq)) {
        printf("%d %d %lld %d %d %d %d \n", v.addBlock, v.cacheHit, v.cost,
               v.words[0], v.words[1], v.words[2], v.words[3]);
        fread(&v, sizeof(MemoryBlock), 1, arq);
    }

    // fecha o arquivo
    fclose(arq);

    RAM = createEmptyCache(sizeRAM, RAM);
    cache1 = createEmptyCache(sizeCache1, cache1);
    cache2 = createEmptyCache(sizeCache2, cache2);
    cache3 = createEmptyCache(sizeCache3, cache3);

    // randomInstructions(y, RAM, cache1, cache2, cache3);
    generatorInstructions(0, RAM, cache1, cache2, cache3);

    return 0;
}
