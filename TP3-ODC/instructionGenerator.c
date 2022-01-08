#include "instructionGenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void instGenerator() {
    FILE *arquivo = fopen("instrucoes.txt", "w");
    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
    srand(time(NULL));

    for (int i = 0; i < N_FOR; i++) {
        random = rand() % N_OPCODE;
        rep[i][0] = random;
        for (int j = 1; j <= (instruc[random]); j += 2) {
            rep[i][j] = rand() % N_MEM;
            rep[i][j + 1] = rand() % N_WORD;
            // printf("%d ", rep[i][j]);
        }
        // printf("\n");
    }
    // for (int i = 0; i < N_FOR; i++) {
    //     for (int j = 0; j < instruc[random]; j++) {
    //         inst[i][j] = rep[i][j];
    //     }
    // }

    for (int i = 0; i < N_INST;) {
        random = (rand() % 100) + 1;
        if (random <= N_PROB && i + N_FOR < N_INST) {
            for (int j = 0; j < N_FOR; j++) {
                for (int k = 0; k < 7; k++) {
                    inst[i + j][k] = rep[j][k];
                }
            }
            i += N_FOR;
        } else {
            random = rand() % N_OPCODE;
            rep[i][0] = random;
            for (int j = 1; j <= instruc[random]; j += 2) {
                inst[i][j] = rand() % N_MEM;
                rep[i][j + 1] = rand() % N_WORD;
            }
            i++;
        }
    }
    for (int i = 0; i < N_INST; i++) {
        for (int k = 0; k < 6; k++) {
            fprintf(arquivo, "%d:", inst[i][k]);
        }
        fprintf(arquivo, "%d\n", inst[i][6]);
    }

    fclose(arquivo);
}