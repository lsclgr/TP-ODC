#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARQUIVO "numeros.dat"
#define NUMVAL 10

int main(int argc, char* argv[]) {
    FILE* arq;
    int i, ret;
    int* value = (int*)malloc(NUMVAL * sizeof(int));

    // abre o arquivo em modo "append"
    arq = fopen(ARQUIVO, "wb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // inicia gerador de aleatórios
    srand(time(NULL));

    // gera NUMVAL valores aleatórios reais
    for (i = 0; i < NUMVAL; i++) value[i] = rand() % 1000;

    // escreve os valores gerados no final do arquivo
    ret = fwrite(value, sizeof(int), NUMVAL, arq);
    if (ret)
        printf("Gravou %d valores com sucesso!\n", ret);
    else
        printf("Erro ao gravar...\n");

    // fecha o arquivo
    fclose(arq);
    int v;

    // abre o arquivo em modo leitura
    arq = fopen(ARQUIVO, "rb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // lê e imprime os valores contidos no arquivo
    fread(&v, sizeof(int), 1, arq);
    while (!feof(arq)) {
        printf("%d\n", v);
        fread(&v, sizeof(int), 1, arq);
    }

    // fecha o arquivo
    fclose(arq);

    // abre o arquivo em modo "append"
    arq = fopen(ARQUIVO, "rb+");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    int x = 7000;
    fseek(arq, 5 * sizeof(int), SEEK_SET);
    fwrite(&x, sizeof(int), 1, arq);
    fclose(arq);
    free(value);
    arq = fopen(ARQUIVO, "rb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // lê e imprime os valores contidos no arquivo
    // fseek(arq, 5 * sizeof(int), SEEK_SET);
    fread(&v, sizeof(int), 1, arq);
    printf("%d\n", v);
    while (!feof(arq)) {
        printf("%d\n", v);
        fread(&v, sizeof(int), 1, arq);
    }

    // fecha o arquivo
    fclose(arq);
    return (0);
}