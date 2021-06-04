#ifndef PROG_ISABELCASTRO_2018013160_TABULEIRO_H
#define PROG_ISABELCASTRO_2018013160_TABULEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "jogo.h"


void printTabuleiro(int tam[2], char **tab);

char **inicializaTabuleiro(int *lin, int *col);

char **inicializaTabuleiroEstados(int *lin, int *col);

char **alteraNLinhas(int *tam, char **tab);

char **alteraNColunas(int *tam, char **tab);

char **preencheTabuleiro(int tam[2], char **tab, int lEscolhida, int cEscolhida, char letra);


#endif //PROG_ISABELCASTRO_2018013160_TABULEIRO_H
