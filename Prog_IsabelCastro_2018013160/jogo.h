//ISABEL RAMOS CASTRO
//2018013160
#ifndef PROG_ISABELCASTRO_2018013160_JOGO_H
#define PROG_ISABELCASTRO_2018013160_JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/unistd.h>
#include "utils.h"

typedef struct jogador jogador, *pJogador;
struct jogador {
    char nome;
    char jogada;
    int nPedras, nAdicoes;
};

typedef struct jogadas noJogada, *pJogada;
struct jogadas {
    jogador x;
    int linha, coluna;
    int tamTab[2];
    pJogada prox;
    pJogada prev;
};


pJogada iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int tamTab[2], char pc, int *stop);

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c, int tamTab[2]);

pJogada opcaoEscolhida(char **tab, pJogador x, pJogada listaJogadas, int tamTab[2], int *escolha);

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaB(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaC(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaD(char **tab, int tamTab[2], pJogador x, pJogada listaJogadas);

pJogada jogadaE(char **tab, int *escolha, pJogador x, pJogada listaJogadas, int tamTab[2]);

pJogada opcaoEscolhidaPC(char **tab, pJogador x, pJogada listaJogadas, int tamTab[2], int *escolha);

void printJogador(jogador x);

int verificaJogada(char **tab, int lJogador, int cJogador);

int procuraVencedor(pJogada listaJogadas, int x, int tipo);

void escolheJogada(pJogador x, int nTurnos, char **tab, int tam[2]);

void escolheJogadaPC(pJogador x, int nTurnos, char **tab, int tam[2]);

int countPecas(char **tab, char jogada, int tam[2]);

void freeListaJogadas(pJogada lista);

void initJogadores(jogador *j);

void atualizaJogadores(jogador *j,pJogada lista);

#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
