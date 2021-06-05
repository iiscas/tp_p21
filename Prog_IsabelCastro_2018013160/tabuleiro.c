//
// Created by isabe on 17-05-2021.
//

#include "tabuleiro.h"


void printTabuleiro(int tam[2], char **tab) {

    //imprime identificacao das colunas x0
    for (int i = 0; i < tam[1]; i++) {
        if (i == 0) {
            printf("       x%d", i);
        } else {
            printf("     x%d", i);
        }
    }

    //divisoria 1
    printf("\n     ");
    for (int i = 0; i < tam[1] * 7; i++) {
        printf("-");
    }
    printf("\n");

    //imprime dados da matriz
    for (int i = 0; i < tam[0]; i++) {
        for (int x = 0; x < tam[1]; x++) {
            if (x == 0) {
                printf("x%d   | ", i); //imprime identificacao das linhas x0
            }
            printf("%c   |  ", tab[i][x]);
        }
        //divisoria entre linhas -----
        printf("\n     ");
        for (int i = 0; i < tam[1] * 7; i++) {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

char **inicializaTabuleiro(int *lin, int *col) {

    *lin = intUniformRnd(2, 3); // esta sempre a dar 5 E NÃO CRIA
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

char **inicializaTabuleiroEstados(int *lin, int *col) {

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

char **alteraNLinhas(int *tam, char **tab) {

    char **tabNovo = realloc(tab, sizeof *tab * (tam[0] + 1));
    if (tabNovo) {
        tab = tabNovo;
        for (int i = 0; i < 1; i++) {
            tab[tam[0] + i] = malloc(sizeof *tabNovo[tam[0] + i] * (tam[1]));
        }
        (tam[0])++;
        //mete as linhas adicionadas bem a -
        for (int i = tam[0] - 1; i < tam[0]; i++) {
            for (int j = 0; j < tam[1]; j++) {
                tab[i][j] = '-';
            }
        }
    }
    //int tam[2]={*lin,*col};
    //printf("\n<--dentro do altera \n");
    //printTabuleiro(tam, tab);
    //printf("\n<--dentro do altera \n");
    return tab;
}

char **alteraNColunas(int *tam, char **tab) {

    char **tabNovo = realloc(tab, sizeof *tab * (tam[1] + 1));
    if (tabNovo) {
        tab = tabNovo;
        for (int i = 0; i < 1; i++) {
            tab[tam[1] + i] = malloc(sizeof *tabNovo[tam[1] + i] * (tam[0]));
        }
        (tam[1])++;
        //printTabuleiro(tam, tab);
        for (int i = 0; i < tam[0]; i++) {
            for (int j = 0; j < tam[1]; j++) {
                if (tab[i][j]!='G' && tab[i][j]!='Y' && tab[i][j]!='R' && tab[i][j]!='P')
                    tab[i][j] = '-';
            }
        }
        //tab[0][tam[1]] = '-'; //nem assim funciona wtf
        //printTabuleiro(tam, tab);
        //printf("\n<--dentro do altera \n");
    }
    return tab;
}

char **preencheTabuleiro(int tam[2], char **tab, int lEscolhida, int cEscolhida, char letra) {

    for (int i = 0; i < tam[0]; ++i) {
        for (int j = 0; j < tam[1]; ++j) {
            if (i == lEscolhida && j == cEscolhida)
                tab[i][j] = letra;
        }
    }
    return tab;
}

