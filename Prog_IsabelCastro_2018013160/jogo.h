//
// Created by isabe on 18-05-2021.
//

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
    jogador x; //pq é que nao pode ser *pJogador?
    int linha, coluna;
    pJogada prox;
};

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col);

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c);

void printJogador(jogador x);

void printListaJogadas(pJogada lista);

void printJogadas(int count, jogador x);

int verificaJogada(char **tab, int lJogador, int cJogador);

pJogada jogadaA(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaB(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaC(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaD(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaE(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

void analisaPecas(char **tab,int l,int c,int *countG,int *countY,int *countR);

#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
