//
// Created by isabe on 17-05-2021.
//

#ifndef PROG_ISABELCASTRO_2018013160_TABULEIRO_H
#define PROG_ISABELCASTRO_2018013160_TABULEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


void printTabuleiro(int lin, int col, char **tab);
char** inicializaTabuleiro(int *lin, int *col);
char** alteraNLinhas(int *lin,int *col,char **tab);
char** preencheTabuleiro(int lin, int col, char **tab, int lEscolhida, int cEscolhida,char letra);
#endif //PROG_ISABELCASTRO_2018013160_TABULEIRO_H
