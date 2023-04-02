#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TorreDeHanoi.h" 

int qnt_pinos () { // Função que devolve a quantidade de pinos inserida pelo usuário.
    int n;
    printf("Insira a quantidade de pinos: [3..5] ");
    scanf("%d", &n);
    if (n >= 3 && n <= 5) { // Verifica se a entrada é elegível e a devolve.
        return n;
    }
    else { // Verifica se não é elegível, e devolve 0 para continuar o While.
        printf("Entrada invalida\n");
        return 0;
    }
}

int qnt_discos () { // Função que devolve a quantidade de discos inserida pelo usuário.
    int m;
    printf("Insira a quantidade de discos: [3..5] ");
    scanf("%d", &m);
    if (m >= 3 && m <= 5) { // Verifica se a entrada é elegível e a devolve.
        return m;
    }
    else { // Verifica se não é elegível, e devolve 0 para continuar o While.
        printf("Entrada invalida\n");
        return 0;
    }
}

void repete_char (char c[] , int conta){ // Função para repetir um caractere recebido, uma recebida quantidade de vezes.
    for (int i = 0; i < conta;i++){
        printf("%s", c);
    }
}

void base_imprime (int discos) { // Função auxiliar para imprimir a base de cada pino.
    repete_char("_",discos+1);
    printf("|");
    repete_char("_",discos+1);

}

Pino** criarPinos(int n) { // Função para alocar um vetor de ponteiros para pinos (Struct).
    int i;
    Pino** pinos = (Pino**) malloc(n*sizeof(Pino*));
    for (i = 0; i < n; i++) {
        pinos[i] = criarPino();
    }
    return pinos;
}

int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino) { // Função para mover um disco de um pino origem para um pino destino.
    int indice_origem = pinoOrigem - 1, indice_destino = pinoDestino - 1;
    if (indice_origem == indice_destino) { // Verifica se as entradas de origem e destino são iguais, para devolver 0 e receber outra entrada.
        return 0;
    }
    if ((indice_origem >= 0 && indice_origem <= 4) && (indice_destino >= 0 && indice_destino <= 4)) { // Verifica se as entradas de origem de destino são elegíveis.
        if ((pinos[indice_origem]->numDiscos > 0 && pinos[indice_destino]->numDiscos >= 0)) { // Verifica se o pino de origem não está vazio e se o de destino está vazio ou não.
            if (!pinos[indice_destino]->topo || pinos[indice_destino]->topo->tamDisco > pinos[indice_origem]->topo->tamDisco) { // Verifica se o topo de destino não está vazio, ou se o disco que será movido é maior que o do disco no topo do pino de destino.
                push(pinos[indice_destino], pop(pinos[indice_origem])); // Retira o disco do pino de origem e aloca no topo do pino destino.
                return 1;
            }
        }
    }
    return 0; // Se alguma das condições impostas acimas não forem cumpridas, a função retornará 0 para continuar recebendo entradas no While.
}

void inicializa_pinos (Pino** pinos, int numDiscos) { // Insere a quantidade recebida de discos no primeiro pino.
    for (size_t i = 0, t = numDiscos; i < numDiscos; i++, t--) {
        Disco* disco;
        disco = criarDisco(t);
        push(pinos[0],disco);
    }
}

void imprimir(Pino **pinos, int numPinos, int numDiscos) { // Função para imprimir os pinos, seus respectivos discos e movimentos feitos pelo usuário.
    int base = 2 * numDiscos + 3;
    int base_metade = base/2;
    printf("\n");
    
    for(int i = 0; i < numPinos; i++) { // Cada execução desenha um pino e seus discos, indo para o próximo após finalizar.
        Disco* aux = pinos[i]->topo;
        int numDiscos_real = numDiscos - pinos[i]->numDiscos;
        for(int j = 0; j < numDiscos ; j++) { // Cada execução desenha uma linha de um pino juntamente com o disco presente (ou não) nela, e pula para a próxima.
            if(pinos[i]->topo != NULL) {
                if (numDiscos_real <= j) {
                    numDiscos_real++;
                    repete_char(" ", base_metade - aux->tamDisco);
                    repete_char("_", aux->tamDisco);
                    printf("|");
                    repete_char("_", aux->tamDisco);
                    aux = aux->next;
                    printf("\n");
                }
                else {
                    repete_char(" ", base_metade);
                    printf("|");
                    repete_char(" ", base_metade);
                    printf("\n");
                }
            }
            else {
                repete_char(" ", base_metade);
                printf("|");
                repete_char(" ", base_metade);
                printf("\n");
            }
        }
        base_imprime(numDiscos);
        printf("\n");
        printf("\n");
        repete_char(" ", numDiscos+1);
        printf("%d", i+1);
        printf("\n");
        printf("\n");
    }
}

void verifica_vitoria (Pino** pinos, int pin, int dis, int* ganhou) { // Verifica se todos os discos estão alocados em qualquer outro pino que não seja o primeiro, para finalizar o programa.
    for (int i = 1; i < pin; i++) {
        if(pinos[i]->numDiscos == dis) {
            *ganhou = 1;
        }
    }
}

int main () {
    int pinos = 0, discos = 0; //Variáveis que conterão a quantidade de pinos e discos recebidos de entrada pelo usuário.

    while(!pinos) { // Caso não receba uma entrada válida de pinos, o programa repetirá o While até receber e sairá do loop.
        pinos = qnt_pinos();
    }
    while(!discos) { // Caso não receba uma entrada válida de discos, o programa repetirá o While até receber e sairá do loop.
        discos = qnt_discos();
    } 

    Pino** pins = criarPinos(pinos); // Cria o vetor de pinos, com cada elemento do vetor sendo um pino alocado.

    inicializa_pinos(pins, discos); // Insere os discos no primeiro pino.

    int vitoria = 0; //Variável return da função para identificar que o jogo está ocorrendo, caso receba 1, o programa finalizará.
    int jogadas = 0; // Variável que conta a quantidade de entradas (jogadas) feitas pelo usuário.
    int origem, destino; //Variáveis input do usuário que conterão os pinos origem e destino para mover um disco de um para outro.

    while (!vitoria) { // Enquanto todos os pinos não forem alocados ordenadamente em um pino diferente do primeiro, o programa continuará ocorrendo.
        int jogada = 0;
        while (!jogada) { // Caso não receba uma jogada válida, o loop se reinicirá e pedirá outra entrada válida. Mesmo que seja válida, o loop mais interno acabará e o mais externo ocorrerá, iniciando o loop interno novamente.
            imprimir(pins, pinos, discos); // Imprime o estado atual do jogo.
            printf("Insira os pinos de origem e destino: ");
            scanf("%d %d", &origem, &destino); 
            jogada = moverDisco(pins, origem, destino); // Move o disco do pino origem para destino.
            if(!jogada) { // Verifica elegibilidade da jogada e pede outro movimento caso não seja elegível.
                printf("Movimento invalido.");
                printf("\n");
            }
            jogadas++; // Contador para quantidade de jogadas.
            verifica_vitoria(pins, pinos, discos, &vitoria); // Verifica se o programa deve terminar.
        }
    }
    imprimir(pins, pinos, discos); // Imprime a última execução do programa.
    printf("PARABENS VOCE CONSEGUIU\n");
    printf("TOTAL DE JOGADAS: %d", jogadas);
    
    for (int i = 0; i < pinos; i++) { // Libera todos os pinos e discos alocados da memória.
        excluirPino(pins[i]);
    }
} 