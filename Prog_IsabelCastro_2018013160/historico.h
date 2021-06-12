#ifndef MAIN_C_HISTORICO_H
#define MAIN_C_HISTORICO_H

#include "jogo.h"

void printListaJogadas(pJogada lista);

void printJogadas(int count, jogador x);

void printEstados(pJogada p, int k);

void printListaJogadasReverso(pJogada head);

int nNosLista(pJogada head);

void printTabuleiroEstados(pJogada tabAtual, pJogada head, int n);

void printPedirEstados(pJogada x, int nTurnos);



#endif //MAIN_C_HISTORICO_H