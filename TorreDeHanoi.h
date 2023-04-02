#include <stdio.h>
#include <stdlib.h>

typedef struct disco Disco;
typedef struct pino Pino;
struct disco{
    Disco *next; // Ponteiro para o proximo disco
    char tamDisco; // Tamanho do disco
};

struct pino{
    Disco *topo; // Ponteiro para o topo da pilha
    char numDiscos; // Quantidade de discos
};
Pino* criarPino(); // Função para criar um pino individual, sem discos, e o devolve.
Disco* criarDisco(int tam); // Função para criar um disco individual, e o devolve.
Disco* pop(Pino *pino); // Função para inserir um disco do topo de um pino
void push(Pino *pino, Disco *disco); // Função para retirar um disco do topo de um pino, e o devolve.
void excluirPino(Pino *pino); // Função para liberar a memória ocupada por um pino e seus discos.
