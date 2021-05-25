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

void iniciaJogo(char **tab, jogador x[], int *lin, int *col);

pJogador criaJogadores(pJogador jogador, int *totalJogadores);

void printJogadas();

int verificaJogada(char **tab, int lJogador, int cJogador);

void jogadaA(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog);

void jogadaB(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog);

void jogadaC(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog);

#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
