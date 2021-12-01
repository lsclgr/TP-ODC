#include "instructionGenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void instGenerator() {
    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
    srand(time(NULL));

    for (int i = 0; i < N_FOR; i++) {
        random = rand() % N_OPCODE;
        rep[i][0] = random;
        for (int j = 1; j <= instruc[random]; j++) {
            rep[i][j] = rand() % N_MEM;
        }
    }
    // for (int i = 0; i < N_FOR; i++) {
    //     for (int j = 0; j < instruc[random]; j++) {
    //         inst[i][j] = rep[i][j];
    //     }
    // }

    for (int i = 0; i < N_INST;) {
        random = (rand() % 100) + 1;
        if (random <= N_PROB && i + N_FOR < N_INST) {
            i += N_FOR;
            for (int j = 0; j < N_FOR; j++) {
                for (int k = 0; k < 7; k++) {
                    inst[i][k] = rep[j][k];
                }
            }
        } else {
            i++;
            random = rand() % N_OPCODE;
            rep[i][0] = random;
            for (int j = 1; j <= instruc[random]; j++) {
                inst[i][j] = rand() % N_MEM;
            }
        }
    }
}