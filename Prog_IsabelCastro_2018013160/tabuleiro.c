//
// Created by isabe on 17-05-2021.
//

#include "tabuleiro.h"


void printTabuleiro(int LIN, int COL, int **tab) {

    //imprime identificacao das colunas x0
    for (int i = 0; i < COL; i++) {
        if (i == 0) {
            printf("       x%d", i);
        } else {
            printf("     x%d", i);
        }
    }

    //divisoria 1
    printf("\n     ");
    for (int i = 0; i < COL * 7; i++) {
        printf("-");
    }
    printf("\n");

    //imprime dados da matriz
    for (int i = 0; i < LIN; i++) {
        for (int x = 0; x < COL; x++) {
            if (x == 0) {
                printf("x%d   | ", i); //imprime identificacao das linhas x0
            }
            printf("%d   |  ", tab[i][x]);
        }
        //divisoria entre linhas -----
        printf("\n     ");
        for (int i = 0; i < COL * 7; i++) {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

