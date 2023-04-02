#include <stdio.h>
#include <stdlib.h>
#include "TorreDeHanoi.h"

Pino* criarPino() { // Função para criar um pino individual, sem discos, e o devolve.
    Pino* pino = malloc(sizeof(Pino)); // Aloca memória para o pino.
    pino->topo = NULL;
    pino->numDiscos = 0;
    return pino;
}

Disco* criarDisco(int tam) { // Função para criar um disco individual, e o devolve.
    Disco* disco = (Disco*) malloc(sizeof(Disco)); // Aloca memória para o disco.
    disco->next = NULL;
    disco->tamDisco = tam;
    return disco;
}

void push(Pino* pino, Disco* disco) { // Função para inserir um disco do topo de um pino.
    Disco* aux = pino->topo;
    pino->numDiscos += 1;
    disco->next = aux;
    pino->topo = disco;
}

Disco* pop(Pino* pino) { // Função para retirar um disco do topo de um pino, e o devolve.
    Disco* aux = pino->topo;
    pino->numDiscos -= 1;
    pino->topo = aux->next;
    return aux;
} 

void excluirPino(Pino *pino) { // Função para liberar a memória ocupada por um pino e seus discos.
    Disco* q = pino->topo;
    while(q!=NULL) {
        Disco* t = q->next;
        free(q);
        q = t;
    }
    free(pino);
}
