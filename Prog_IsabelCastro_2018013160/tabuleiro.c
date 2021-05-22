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

char **inicializaTabuleiro(int lin, int col) {

    char **tab;

// aloca um vetor de lin ponteiros para linhas
    tab = (char **) malloc(lin * sizeof(char));

    if (tab == NULL) {
        puts("tabuleiro nao foi alocado");
        return tab;
    }

// ajusta os demais ponteiros de linhas (i > 0)
    for (int i = 0; i < lin; i++) {
        tab[i] = (char *) malloc(sizeof(char) * col);
        if (tab == NULL) {
            puts("tabuleiro nao foi alocado");
            return tab;
        }
    }
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            strcpy(&tab[i][j], "-");
        }
    }


    return tab;
}

char **alteraNLinhas(int add, int lin, int col, char **tab) {


    char **tabNovo = realloc(tab, sizeof *tab * (lin + add));
    if (tabNovo) {

        //tab = tabNovo;
        for (size_t i = 0; i < add; i++) {
            tabNovo[lin + i] = malloc(sizeof *tabNovo[lin + i] * col);

        }
        for (int i = lin; i < lin + add; ++i) {
            for (int j = 0; j < col; ++j) {
                strcpy(&tabNovo[i][j], "a");
            }
        }
    }

    return tabNovo;
}

