#ifndef MAIN_C_HISTORICO_H
#define MAIN_C_HISTORICO_H

#include "jogo.h"
#include "tabuleiro.h"

void printListaJogadas(pJogada lista);

void printJogadas(int count, jogador x);

void printEstados(pJogada p, int k, int tamTab[2]);

void printListaJogadasReverso(pJogada head);

int nNosLista(pJogada head);

void printTabuleiroEstados(pJogada tabAtual, pJogada head, int n);

void printPedirEstados(pJogada x, int nTurnos, int tamTab[2]);

int gravaRelJogadas(pJogada lista, char pc, char *fichJog);

#endif //MAIN_C_HISTORICO_H