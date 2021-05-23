#include <sys/cdefs.h>
//
// Created by isabe on 18-05-2021.
//

#include "jogo.h"

void iniciaJogo(char **tab, jogador x[], int *lin, int *col) {
    int fimJogo = 0, nTurnos = 0;
    int a = 0, b = 1;
    int linha = 0, coluna = 0;

   while(!fimJogo) {

       printTabuleiro(*lin, *col, tab);
       printf("Jogador %c e a sua vez! ", x[0].nome);
       printJogadas(&nTurnos,&x[0]);
       scanf("%s", &x[0].jogada);
       printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x[0].nome);
       scanf("%d %d", &linha, &coluna);
       fflush(stdout);
       tab = preencheTabuleiro(*lin, *col, tab, linha, coluna, x[0].jogada);
       printTabuleiro(*lin, *col, tab);

       printf("Jogador %c e a sua vez! ", x[1].nome);
       printJogadas(&nTurnos,&x[1]);
       scanf("%s", &x[1].jogada);
       printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x[1].nome);
       scanf("%d %d", &linha, &coluna);
       fflush(stdout);
       tab = preencheTabuleiro(*lin, *col, tab, linha, coluna, x[1].jogada);
       nTurnos++;
   }    // fimJogo=1;

}

void printJogadas(int *count,jogador x) {
    if (*count==0) {
        printf("\n----------------------\nSó pode escolher uma peça verde (G)!\n----------------------\n>>");

    }else if (*count>=1) {
        printf("\n----------------------\nJa pode fazer as seguintes jogadas\n----------------------\n"
               "(A)- Colocar uma peça Verde numa célula vazia\n"
               "(B)- Trocar uma peça Verde que esteja colocada no tabuleiro por uma peça Amarela\n"
               "(C)- Trocar uma peça Amarela que esteja colocada no tabuleiro por uma peça Vermelha\n");
        printf("(D)- Colocar uma pedra numa célula vazia.(Usado %d vezes)\n", x.nPedras);
        printf("(E)- Adicionar uma linha ou uma coluna ao final do tabuleiro.(Usado %d vezes)\n\n>>", x.nAdicoes);
    }
}

/*pJogador criaJogadores(pJogador jogador, int *totalJogadores) {

    jogador[*totalJogadores].nJogadas = 0;
    jogador[*totalJogadores].jogada = '-';

    if (*totalJogadores == 0)
        strcpy(&jogador[*totalJogadores].nome, "A");
    else
        strcpy(&jogador[*totalJogadores].nome, "B");

    (*totalJogadores)++;


    return jogador;
}
 */