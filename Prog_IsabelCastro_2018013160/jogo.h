#ifndef PROG_ISABELCASTRO_2018013160_JOGO_H
#define PROG_ISABELCASTRO_2018013160_JOGO_H

#include "tabuleiro.h"
#include <ctype.h>

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

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col);

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c, int tamTab[2]);

void printJogador(jogador x);

int CheckLinhas(char **tab, int tamTab[2]);

int checkColunas(char **tab, int tamTab[2]);

int verificaJogada(char **tab, int lJogador, int cJogador);

int procuraVencedor(pJogada listaJogadas, int x, int tipo);

void printPedirEstados(pJogada x, int nTurnos, int tamTab[2]);

pJogada opcaoEscolhida(char **tab, jogador x, pJogada listaJogadas, int tamTab[2], int *escolha);

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaB(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaC(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaD(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaE(char **tab, int *escolha, jogador x, pJogada listaJogadas, int tamTab[2]);

#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
