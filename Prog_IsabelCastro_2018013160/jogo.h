#ifndef PROG_ISABELCASTRO_2018013160_JOGO_H
#define PROG_ISABELCASTRO_2018013160_JOGO_H

#include "tabuleiro.h"
#include <ctype.h>
#include <sys/unistd.h>

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

pJogada iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int tamTab[2], char pc);

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c, int tamTab[2]);

void printJogador(jogador x);

int checkTabuleiro(char **tab, int tamTab[2], int *tipo);

int verificaJogada(char **tab, int lJogador, int cJogador);

int procuraVencedor(pJogada listaJogadas, int x, int tipo);

pJogada opcaoEscolhida(char **tab, pJogador x, pJogada listaJogadas, int tamTab[2], int *escolha);

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaB(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaC(char **tab, int tamTab[2], jogador x, pJogada listaJogadas);

pJogada jogadaD(char **tab, int tamTab[2], pJogador x, pJogada listaJogadas);

pJogada jogadaE(char **tab, int *escolha, pJogador x, pJogada listaJogadas, int tamTab[2]);

void escolheJogada(pJogador x, int nTurnos,char **tab,int tam[2]);

void escolheJogadaPC(pJogador x, int nTurnos,char **tab,int tam[2]);

pJogada opcaoEscolhidaPC(char **tab, pJogador x, pJogada listaJogadas, int tamTab[2], int *escolha);

int countPecas(char **tab, char jogada,int tam[2]);
#endif //PROG_ISABELCASTRO_2018013160_JOGO_H
