//ISABEL RAMOS CASTRO
//2018013160
#ifndef PROG_ISABELCASTRO_2018013160_TABULEIRO_H
#define PROG_ISABELCASTRO_2018013160_TABULEIRO_H
#include "jogo.h"

void printTabuleiro(int tam[2], char **tab);

char **inicializaTabuleiro(int *lin, int *col);

char **inicializaTabuleiroEstados(int *lin, int *col);

char **alteraNLinhas(int *tam, char **tab);

char **alteraNColunas(int *tam, char **tab);

char **preencheTabuleiro(int tam[2], char **tab, int lEscolhida, int cEscolhida, char letra);

char **recuperaTabuleiro(pJogada pJogadas, int tam[2]);

int checkTabuleiro(char **tab, int tamTab[2], int *tipo);

void freeTabuleiro(char **tab,int lin);
#endif //PROG_ISABELCASTRO_2018013160_TABULEIRO_H
