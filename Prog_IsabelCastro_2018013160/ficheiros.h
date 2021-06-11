#ifndef MAIN_C_FICHEIROS_H
#define MAIN_C_FICHEIROS_H


#include "jogo.h"
#include "historico.h"
#define JOGREC "jogo.dat"

int gravaRelJogadas(pJogada lista, char pc, char *fichJog);

char **preencheTabRec(char **tab);

void preencheFichBinario(pJogada lista, int pc,int numJogadas);

pJogada preencheListaRec(pJogada lista,int *pc,int *numJogadas);

pJogada adicionaFimListaRec(pJogada lista);


#endif //MAIN_C_FICHEIROS_H
