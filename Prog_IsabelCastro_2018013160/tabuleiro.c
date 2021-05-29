//
// Created by isabe on 17-05-2021.
//

#include "tabuleiro.h"


void printTabuleiro(int lin, int col, char **tab) {

    //imprime identificacao das colunas x0
    for (int i = 0; i < col; i++) {
        if (i == 0) {
            printf("       x%d", i);
        } else {
            printf("     x%d", i);
        }
    }

    //divisoria 1
    printf("\n     ");
    for (int i = 0; i < col * 7; i++) {
        printf("-");
    }
    printf("\n");

    //imprime dados da matriz
    for (int i = 0; i < lin; i++) {
        for (int x = 0; x < col; x++) {
            if (x == 0) {
                printf("x%d   | ", i); //imprime identificacao das linhas x0
            }
            printf("%c   |  ", tab[i][x]);
        }
        //divisoria entre linhas -----
        printf("\n     ");
        for (int i = 0; i < col * 7; i++) {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

char **inicializaTabuleiro(int *lin, int *col) {


    *lin = intUniformRnd(3, 5); // esta sempre a dar 5 E NÃO CRIA
    *col = *lin;

    char **tab;

// aloca um vetor de lin ponteiros para linhas
    tab = (char **) malloc(*lin * sizeof(char *));

    if (tab == NULL) {
        puts("tabuleiro nao foi alocado");
        return tab;
    }

// ajusta os demais ponteiros de linhas (i > 0)
    for (int i = 0; i < *lin; i++) {
        tab[i] = (char *) malloc(sizeof(char) * (*col));
        if (tab == NULL) {
            puts("tabuleiro nao foi alocado");
            return tab;
        }
    }
    //printTabuleiro(*lin, *col, tab); //imprimir tabuleiro sem ser inicializado
    for (int i = 0; i < *lin; i++) {

        for (int j = 0; j < *col; j++) {
            tab[i][j] = '-'; //SEGMENTATION FAULT LINHA 4 COLUNA 0
        }
    }
    return tab;
}

char **alteraNLinhas(int *lin, int *col, char **tab) {

    char **tabNovo = realloc(tab, sizeof *tab * (*lin + 1));
    if (tabNovo) {
        tab = tabNovo;
        for (int i = 0; i < 1; i++) {
            tab[*lin + i] = malloc(sizeof *tabNovo[*lin + i] * (*col));
        }
        //printTabuleiro(*lin + 1, *col, tabNovo);
        //mete as linhas adicionadas bem a -
        for (int i = *lin; i < *lin + 1; ++i) {
            for (int j = 0; j < *col; ++j) {
                tab[i][j] = '-';
            }
        }

        (*lin)++;
    }

    //printTabuleiro(*lin, *col, tab);
    return tab;
}

char **alteraNColunas(int *lin, int *col, char **tab) {

    char **tabNovo = realloc(tab, sizeof *tab * (*col + 1));
    if (tabNovo) {
        tab = tabNovo;
        for (int i = 0; i < 1; i++) {
            tab[*col + i] = malloc(sizeof *tabNovo[*col + i] * (*lin));
        }
        //printTabuleiro(*lin + 1, *col, tabNovo);
        //mete as colunas adicionadas bem a -
        for (int i = 0; i < *lin; ++i) {
            for (int j = *col; j < *col + 1; ++j) {
                tab[i][j] = '-';
            }
        }
        (*col)++;
        //printTabuleiro(*lin, *col, tab);
    }
    return tab;
}

char **preencheTabuleiro(int lin, int col, char **tab, int lEscolhida, int cEscolhida, char letra) {

    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == lEscolhida && j == cEscolhida)
                tab[i][j] = letra;
        }
    }
    return tab;
}

