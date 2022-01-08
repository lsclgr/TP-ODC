#include "machine.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "MMU.h"
#include "instructionGenerator.h"

void machine(int PC, int interruption, Instruction* instruction,
             MemoryBlock* RAM, MemoryBlock* cache1, MemoryBlock* cache2,
             MemoryBlock* cache3) {
    srand(time(NULL));
    int opcode = RAND_MAX;
    long long int cost = 0;

    int missC1 = 0;
    int hitC1 = 0;
    int missC2 = 0;
    int hitC2 = 0;
    int missC3 = 0;
    int hitC3 = 0;
    int content1, content2, sum, sub, indexAdd1, indexAdd2, indexAdd3,
        contTime = 0;
    MemoryBlock memoryDataAdd1;
    MemoryBlock memoryDataAdd2;
    MemoryBlock memoryDataAdd3;
    Instruction inst;

    while (opcode != -1) {
        inst = instruction[PC];
        // if (PC == 100) {
        //     exit(1);
        // }
        printf("\nposicao PC %d\n", PC);
        printf(
            "\nOPCODE: %d  add1b: %d add1p: %d add2b: %d add2p: %d add3b: %d "
            "add3p: %d\n",
            inst.opcode, inst.add1.addBlock, inst.add1.addWord,
            inst.add2.addBlock, inst.add2.addWord, inst.add3.addBlock,
            inst.add3.addWord);
        opcode = inst.opcode;
        if (opcode != -1) {
            indexAdd1 = searchInMemories(inst.add1, RAM, cache1, cache2, cache3,
                                         contTime);
            memoryDataAdd1 = cache1[indexAdd1];

            indexAdd2 = searchInMemories(inst.add2, RAM, cache1, cache2, cache3,
                                         contTime);
            memoryDataAdd2 = cache1[indexAdd2];

            indexAdd3 = searchInMemories(inst.add3, RAM, cache1, cache2, cache3,
                                         contTime);
            memoryDataAdd3 = cache1[indexAdd3];

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

            printf("Custo até o momento do programa em execução: %lld\n", cost);
            printf(
                "Hits e Misses até o momento - C1 hit %d | C1 miss %d | C2 hit "
                "%d | C2 miss: %d | C3 hit %d | C3 miss: %d\n",
                hitC1, missC1, hitC2, missC2, hitC3, missC3);
        }

        // printf("\n%d\n", inst.opcode);
        switch (opcode) {
            case 0:
                memoryDataAdd3.words[inst.add3.addWord] = inst.add3.addWord;
                memoryDataAdd3.updated = true;
                cache1[indexAdd3] = memoryDataAdd3;
                break;
            case 1:
                content1 = memoryDataAdd1.words[inst.add1.addWord];
                content2 = memoryDataAdd2.words[inst.add2.addWord];
                sum = content1 + content2;
                memoryDataAdd3.words[inst.add3.addWord] = sum;
                memoryDataAdd3.updated = true;
                cache1[indexAdd3] = memoryDataAdd3;
                break;
            case 2:
                // printf("\nsegmentacao case 2\n");
                content1 = memoryDataAdd1.words[inst.add1.addWord];
                content2 = memoryDataAdd2.words[inst.add2.addWord];
                sub = content1 - content2;
                memoryDataAdd3.words[inst.add3.addWord] = sub;
                memoryDataAdd3.updated = true;
                cache1[indexAdd3] = memoryDataAdd3;
                break;
            case 3:
                instruction[PC].add1.addWord = memoryDataAdd1.words[0];
                break;
            default:
                break;
        }
        PC++;
        // lembrar de salvar posição pc caso ocorra uma interrupção para voltar
        // do mesmo lugar dps que acabar a interrupção
        if (interruption == 0) {  // interruption=1 tem interrupção, =0 é normal
            // aqui dentro sorteia a prob de 25% de ocorrer uma interrupção e se
            // for chama a maquina de novo, agr com a interrupçao
            int probInterruption = rand() % 4;
            printf("%d\n", probInterruption);
            if (probInterruption == 0) {
                printf("\nINICIO TRATADOR DE INTERRUPÇÃO\n");
                system("sleep 02");
                // colocar tempinho para ficar realista
                int numRandomoInstrucions = rand() % 100;
                printf("%d\n", numRandomoInstrucions);
                Instruction* instInterruption = NULL;
                randomInstructions(numRandomoInstrucions, &instInterruption,
                                   RAM, cache1, cache2, cache3);
                machine(0, 1, instInterruption, RAM, cache1, cache2, cache3);
                printf("\nFIM TRATADOR DE INTERRUPÇÃO\n");
                system("sleep 02");
                break;
            }
        }
    }
}

void randomInstructions(int nInst, Instruction** instInterruption,
                        MemoryBlock* RAM, MemoryBlock* cache1,
                        MemoryBlock* cache2, MemoryBlock* cache3) {
    Instruction inst;
    *instInterruption = malloc(nInst * sizeof(Instruction));
    for (int i = 0; i < nInst - 1; i++) {
        inst.opcode = rand() % 4;
        inst.add1.addBlock = rand() % 1000;
        inst.add1.addWord = rand() % 4;

        inst.add2.addBlock = rand() % 1000;
        inst.add2.addWord = rand() % 4;

        inst.add3.addBlock = rand() % 1000;
        inst.add3.addWord = rand() % 4;
        (*instInterruption)[i] = inst;
    }

    (*instInterruption)[nInst - 1].opcode = -1;
    (*instInterruption)[nInst - 1].add1.addBlock = -1;
    (*instInterruption)[nInst - 1].add1.addWord = -1;
    (*instInterruption)[nInst - 1].add2.addBlock = -1;
    (*instInterruption)[nInst - 1].add2.addWord = -1;
    (*instInterruption)[nInst - 1].add3.addBlock = -1;
    (*instInterruption)[nInst - 1].add3.addWord = -1;

    // machine(0, 1, instruction, RAM, cache1, cache2, cache3);
    //  free(instruction);
}

void generatorInstructions(MemoryBlock* RAM, MemoryBlock* cache1,
                           MemoryBlock* cache2, MemoryBlock* cache3) {
    instGenerator();
    FILE* arquivo = fopen("instrucoes.txt", "r");
    char aux[21], aux2[4];
    Instruction *instruction = NULL, inst;
    int cont = 0;
    instruction = malloc(10001 * sizeof(Instruction));
    for (int i = 0; i < 10000; i++) {
        cont = 0;
        fgets(aux, 21, arquivo);
        for (int j = 0; j < 21; j++) {
            if (aux[j] == '\n') {
                aux[j] = '\0';
            }
        }
        for (int j = 0; j < 21;) {
            if (aux[j] == '\0') {
                break;
            }
            for (int k = 0; k < 4; k++) {
                if (aux[j] != ':' && aux[j] != '\0') {
                    aux2[k] = aux[j];
                    j++;
                } else {
                    cont++;
                    aux2[k] = '\0';
                    j++;
                    break;
                }
            }
            switch (cont) {
                case 1:
                    inst.opcode = atoi(aux2);

                    break;
                case 2:
                    inst.add1.addBlock = atoi(aux2);

                    break;
                case 3:
                    inst.add1.addWord = atoi(aux2);

                    break;
                case 4:
                    inst.add2.addBlock = atoi(aux2);

                    break;
                case 5:
                    inst.add2.addWord = atoi(aux2);

                    break;
                case 6:
                    inst.add3.addBlock = atoi(aux2);

                    break;
                case 7:
                    inst.add3.addWord = atoi(aux2);

                    break;
                default:
                    break;
            }
        }
        instruction[i] = inst;
    }
    instruction[10000].opcode = -1;
    machine(0, 0, instruction, RAM, cache1, cache2, cache3);

    // free(instruction);
    fclose(arquivo);
}