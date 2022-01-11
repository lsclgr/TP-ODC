#include "machine.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "MMU.h"

void machine(int PC, int interruption, Instruction* instruction, FILE* arquivo,
             FILE* arq, MemoryBlock* RAM, MemoryBlock* cache1,
             MemoryBlock* cache2, MemoryBlock* cache3, int HD_ou_SSD) {
    srand(time(NULL));
    int opcode = RAND_MAX;
    long long int cost = 0;
    //  int opcodeAux = instruction[0].opcode, pcAux = 0;
    // printf("\n\n");
    // while (opcodeAux != -1) {
    //     printf(
    //         "%d:%d:%d:%d:%d:%d:%d\n", instruction[pcAux].opcode,
    //         instruction[pcAux].add1.addBlock,
    //         instruction[pcAux].add1.addWord,
    //         instruction[pcAux].add2.addBlock,
    //         instruction[pcAux].add2.addWord,
    //         instruction[pcAux].add3.addBlock,
    //         instruction[pcAux].add3.addWord);
    //     opcodeAux = instruction[++pcAux].opcode;
    // }
    // printf("%d:%d:%d:%d:%d:%d:%d\n", instruction[pcAux].opcode,
    //        instruction[pcAux].add1.addBlock, instruction[pcAux].add1.addWord,
    //        instruction[pcAux].add2.addBlock, instruction[pcAux].add2.addWord,
    //        instruction[pcAux].add3.addBlock,
    //        instruction[pcAux].add3.addWord);

    int missC1 = 0;
    int hitC1 = 0;
    int missC2 = 0;
    int hitC2 = 0;
    int missC3 = 0;
    int hitC3 = 0;
    int missRAM = 0;
    int hitRAM = 0;
    int content1, content2, sum, sub, indexAdd1, indexAdd2, indexAdd3,
        contTime = 0;
    MemoryBlock memoryDataAdd1;
    MemoryBlock memoryDataAdd2;
    MemoryBlock memoryDataAdd3;
    Instruction inst;

    while (instruction[PC].opcode != -1) {
        inst = instruction[PC];
        printf(
            "\nOPCODE: %d  add1b: %d add1p: %d add2b: %d add2p: %d add3b: %d "
            "add3p: %d\n",
            instruction[PC].opcode, instruction[PC].add1.addBlock,
            instruction[PC].add1.addWord, instruction[PC].add2.addBlock,
            instruction[PC].add2.addWord, instruction[PC].add3.addBlock,
            instruction[PC].add3.addWord);

        printf("\nposicao PC %d\n", PC);

        // printf(
        //     "\nOPCODE: %d  add1b: %d add1p: %d add2b: %d add2p: %d add3b: %d
        //     " "add3p: %d\n", inst.opcode, inst.add1.addBlock,
        //     inst.add1.addWord, inst.add2.addBlock, inst.add2.addWord,
        //     inst.add3.addBlock, inst.add3.addWord);
        opcode = inst.opcode;
        if (opcode != -1) {
            // printf("NENHUM Search????????????????\n");
            indexAdd1 = searchInMemories(inst.add1, arq, RAM, cache1, cache2,
                                         cache3, &contTime, HD_ou_SSD);
            memoryDataAdd1 = cache1[indexAdd1];
            // printf("search 1 ??????????\n");

            indexAdd2 = searchInMemories(inst.add2, arq, RAM, cache1, cache2,
                                         cache3, &contTime, HD_ou_SSD);
            memoryDataAdd2 = cache1[indexAdd2];
            // printf("search 2 ??????????\n");

            indexAdd3 = searchInMemories(inst.add3, arq, RAM, cache1, cache2,
                                         cache3, &contTime, HD_ou_SSD);
            memoryDataAdd3 = cache1[indexAdd3];

            // printf("Passou do search\n");

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

                case 4:
                    hitRAM++;
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
                default:
                    missRAM++;
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

                case 4:
                    hitRAM++;
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
                default:
                    missRAM++;
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

                case 4:
                    hitRAM++;
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
                default:
                    missRAM++;
                    missC1++;
                    missC2++;
                    missC3++;
                    break;
            }

            printf("Custo até o momento do programa em execução: %lld\n", cost);
            printf(
                "Hits e Misses até o momento - C1 hit %d | C1 miss %d | C2 hit "
                "%d | C2 miss: %d | C3 hit %d | C3 miss: %d | RAM hit %d | RAM "
                "miss: %d\n",
                hitC1, missC1, hitC2, missC2, hitC3, missC3, hitRAM, missRAM);
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
                // FILE* file;
                // file = fopen("pc.dat", "rb+");
                // fwrite(&PC, sizeof(int), 1, file);
                printf("\nINICIO TRATADOR DE INTERRUPÇÃO\n");

                //    colocar tempinho para ficar realista
                int numRandomoInstrucions = (rand() % 40) + 1;
                printf("Instruções Geradas: %d\n", (numRandomoInstrucions - 1));
                system("sleep 02");
                //   Instruction* instInterruption = NULL;
                randomInstructions(numRandomoInstrucions, arquivo, arq, RAM,
                                   cache1, cache2, cache3, HD_ou_SSD);
                //   machine(0, 1, instInterruption, RAM, cache1,
                //   cache2,cache3);
                // generatorInstructions2(0, arquivo, arq, RAM, cache1, cache2,
                // cache3);
                printf("\nFIM TRATADOR DE INTERRUPÇÃO\n");
                system("sleep 02");
                // exit(1);
                //    fread(&PC, sizeof(int), 1, file);
                //    fclose(file);
                //   break;
            }
        }
    }
}

void randomInstructions(int nInst, FILE* arquivo, FILE* arq, MemoryBlock* RAM,
                        MemoryBlock* cache1, MemoryBlock* cache2,
                        MemoryBlock* cache3, int HD_ou_SSD) {
    Instruction inst;
    // Instruction* instInterruption = malloc(nInst * sizeof(Instruction));

    Instruction instInterruption[nInst];

    for (int i = 0; i < (nInst - 1); i++) {
        inst.opcode = rand() % 4;
        inst.add1.addBlock = rand() % 1000;
        inst.add1.addWord = rand() % 4;

        inst.add2.addBlock = rand() % 1000;
        inst.add2.addWord = rand() % 4;

        inst.add3.addBlock = rand() % 1000;
        inst.add3.addWord = rand() % 4;
        // printf("%d:%d:%d:%d:%d:%d:%d\n", inst.opcode, inst.add1.addBlock,
        //        inst.add1.addWord, inst.add2.addBlock, inst.add2.addWord,
        //        inst.add3.addBlock, inst.add3.addWord);
        instInterruption[i] = inst;
    }

    instInterruption[nInst - 1].opcode = -1;
    instInterruption[nInst - 1].add1.addBlock = -1;
    instInterruption[nInst - 1].add1.addWord = -1;
    instInterruption[nInst - 1].add2.addBlock = -1;
    instInterruption[nInst - 1].add2.addWord = -1;
    instInterruption[nInst - 1].add3.addBlock = -1;
    instInterruption[nInst - 1].add3.addWord = -1;

    machine(0, 1, instInterruption, arquivo, arq, RAM, cache1, cache2, cache3,
            HD_ou_SSD);
    // free(instInterruption);
}

void generatorInstructions(int PC, FILE* arquivo, FILE* arq, MemoryBlock* RAM,
                           MemoryBlock* cache1, MemoryBlock* cache2,
                           MemoryBlock* cache3, int HD_ou_SSD) {
    // instGenerator();
    FILE* arquivo2 = fopen("instrucoes.txt", "r");
    char aux[21], aux2[4];
    Instruction *instruction = NULL, inst;
    int cont = 0;
    instruction = malloc(10001 * sizeof(Instruction));
    for (int i = 0; i < 10000; i++) {
        cont = 0;
        fgets(aux, 21, arquivo2);
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
    fclose(arquivo2);
    machine(PC, 0, instruction, arquivo, arq, RAM, cache1, cache2, cache3,
            HD_ou_SSD);

    free(instruction);
}

// void generatorInstructions2(int PC, FILE* arquivo, FILE* arq, MemoryBlock*
// RAM,
//                             MemoryBlock* cache1, MemoryBlock* cache2,
//                             MemoryBlock* cache3) {
//     // instGenerator();

//     char aux[21], aux2[4];
//     Instruction instructionG[51], inst;
//     int cont = 0;
//     // instructionG = malloc(10001 * sizeof(Instruction));
//     for (int i = 0; i < 50; i++) {
//         cont = 0;
//         fgets(aux, 21, arquivo);
//         for (int j = 0; j < 21; j++) {
//             if (aux[j] == '\n') {
//                 aux[j] = '\0';
//             }
//         }
//         for (int j = 0; j < 21;) {
//             if (aux[j] == '\0') {
//                 break;
//             }
//             for (int k = 0; k < 4; k++) {
//                 if (aux[j] != ':' && aux[j] != '\0') {
//                     aux2[k] = aux[j];
//                     j++;
//                 } else {
//                     cont++;
//                     aux2[k] = '\0';
//                     j++;
//                     break;
//                 }
//             }
//             switch (cont) {
//                 case 1:
//                     inst.opcode = atoi(aux2);

//                     break;
//                 case 2:
//                     inst.add1.addBlock = atoi(aux2);

//                     break;
//                 case 3:
//                     inst.add1.addWord = atoi(aux2);

//                     break;
//                 case 4:
//                     inst.add2.addBlock = atoi(aux2);

//                     break;
//                 case 5:
//                     inst.add2.addWord = atoi(aux2);

//                     break;
//                 case 6:
//                     inst.add3.addBlock = atoi(aux2);

//                     break;
//                 case 7:
//                     inst.add3.addWord = atoi(aux2);

//                     break;
//                 default:
//                     break;
//             }
//         }
//         instructionG[i] = inst;
//     }
//     instructionG[50].opcode = -1;
//     int pcAux = 0;

//     while (instructionG[pcAux].opcode != -1) {
//         printf(
//             "%d:%d:%d:%d:%d:%d:%d\n", instructionG[pcAux].opcode,
//             instructionG[pcAux].add1.addBlock,
//             instructionG[pcAux].add1.addWord,
//             instructionG[pcAux].add2.addBlock,
//             instructionG[pcAux].add2.addWord,
//             instructionG[pcAux].add3.addBlock,
//             instructionG[pcAux].add3.addWord);
//         pcAux++;
//     }
//     printf(
//         "%d:%d:%d:%d:%d:%d:%d\n", instructionG[pcAux].opcode,
//         instructionG[pcAux].add1.addBlock, instructionG[pcAux].add1.addWord,
//         instructionG[pcAux].add2.addBlock, instructionG[pcAux].add2.addWord,
//         instructionG[pcAux].add3.addBlock, instructionG[pcAux].add3.addWord);

//     machine(PC, 1, instructionG, arquivo, arq, RAM, cache1, cache2, cache3);

//     // free(instructionG);
// }