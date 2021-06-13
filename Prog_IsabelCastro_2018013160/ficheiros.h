//ISABEL RAMOS CASTRO
//2018013160
#ifndef MAIN_C_FICHEIROS_H
#define MAIN_C_FICHEIROS_H

#include "jogo.h"

#define JOGREC "jogo.dat"

int gravaRelJogadas(pJogada lista, char pc, char *fichJog);

void preencheFichBinario(pJogada lista, int pc, int numJogadas);

pJogada preencheListaRec(pJogada lista, int *pc, int *numJogadas);


#endif //MAIN_C_FICHEIROS_H
