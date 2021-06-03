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
    pJogada prev;
};

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col);

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c);

void printJogador(jogador x);

int CheckLinhas(char **tab, int lin, int col);

int checkColunas(char **tab, int lin, int col);

int verificaJogada(char **tab, int lJogador, int cJogador);

pJogada jogadaA(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaB(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaC(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaD(char **tab, int lin, int col, jogador x, pJogada listaJogadas);

pJogada jogadaE(char **tab, int *escolha, jogador x, pJogada listaJogadas);

void procuraVencedor(pJogada listaJogadas,int x,int tipo);

void printPedirEstados(pJogada x, int nTurnos, int lin, int col);

pJogada opcaoEscolhida(char **tab,jogador x,pJogada listaJogadas,int lin,int col,int *escolha);
#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
