#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#define LIN 3
#define COL 4

void menuPrincipal(){

    printf("\n--------------------------------------------------------\n"
           "                                                        \n"
           "          -------------------------------             \n"
           "                 JOGO DO SEMAFORO                     \n"
           "          -------------------------------             \n"
           "                   1. Iniciar jogo                    \n"
           "                   2. Sair                            \n"
           "--------------------------------------------------------\n"
           ">> ");




}
int main() {
//    int escolha = 0;
//    menuPrincipal();
//    do {
//
//        scanf("%d", &escolha);
//        switch (escolha) {
//            case 1:
//                printf("Jogo vai começar! \n");
//        }
//
//
//    } while (escolha != 2);




    int **tabuleiro ;
    int i, j ;

// aloca um vetor de LIN ponteiros para linhas
    tabuleiro = malloc (LIN * sizeof (int*)) ;

// aloca um vetor com todos os elementos da matriz
    tabuleiro[0] = malloc (LIN * COL * sizeof (int)) ;

// ajusta os demais ponteiros de linhas (i > 0)
    for (i=1; i < LIN; i++)
        tabuleiro[i] = tabuleiro[0] + i * COL ;

// percorre a matriz
    for (i=0; i < LIN; i++) {
        printf("\n");
        for (j = 0; j < COL; j++) {
            tabuleiro[i][j] = 0;

        }
    }

    printTabuleiro(LIN,COL,tabuleiro);

// libera a memória da matriz
     free(tabuleiro[0]);
     free(tabuleiro);
    return 0;
}
