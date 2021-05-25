
//
// Created by isabe on 18-05-2021.
//


#include "jogo.h"

void iniciaJogo(char **tab, jogador x[], int *lin, int *col) {
    int fimJogo = 0, nTurnos = 0;
    int a = 0, b = 1, v;
    int linha = 0, coluna = 0;

    do {

        printTabuleiro(*lin, *col, tab);
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printJogadas(&nTurnos, &x[0]);

        if (nTurnos == 0) {
            while (!((int) x[0].jogada == 65)) {
                printf("\n>>");
                scanf("%s", &x[0].jogada);
                fflush(stdout);
            }
        } else {
            while (!((int) x[0].jogada >= 65 && (int) x[0].jogada <= 69)) {
                printf("\n>>");
                scanf("%s", &x[0].jogada);
                fflush(stdout);
            }
        }
        if (toupper(x[0].jogada) == 'A') {
            jogadaA(tab, linha, coluna, *lin, *col, x, 0);
        }

        linha = 0, coluna = 0;
        printf("Jogador %c e a sua vez! ", x[1].nome);
        printJogadas(&nTurnos, &x[1]);
        if (nTurnos == 0) {
            while (!((int) x[1].jogada == 65)) {
                printf("\n>>");
                scanf("%s", &x[1].jogada);
                fflush(stdout);
            }
        } else {
            while (!((int) x[1].jogada >= 65 && (int) x[1].jogada <= 69)) {

                printf("\n>>");
                scanf("%s", &x[1].jogada);
                fflush(stdout);
            }
        }
        if (toupper(x[1].jogada) == 'A') {
            jogadaA(tab, linha, coluna, *lin, *col, x, 1);
        }
        nTurnos++;
    } while (1);

}    // fimJogo=1;



int verificaJogada(char **tab, int lJogador, int cJogador) {
    //devolve 0 se não for possivel, 1 se for possivel
    if (tab[lJogador][cJogador] == '-')
        return 1;
    else
        return 0;

}

void printJogadas(int *count, jogador x) {
    if (*count == 0) {
        printf("\n----------------------\nSó pode jogar uma peça verde! (A)\n----------------------\n");

    } else if (*count >= 1) {
        printf("\n----------------------\nJa pode fazer as seguintes jogadas\n----------------------\n"
               "(A)- Colocar uma peça Verde numa célula vazia\n"
               "(B)- Trocar uma peça Verde que esteja colocada no tabuleiro por uma peça Amarela\n"
               "(C)- Trocar uma peça Amarela que esteja colocada no tabuleiro por uma peça Vermelha\n");
        printf("(D)- Colocar uma pedra numa célula vazia.(Usado %d vezes)\n", x.nPedras);
        printf("(E)- Adicionar uma linha ou uma coluna ao final do tabuleiro.(Usado %d vezes)\n", x.nAdicoes);
    }
}

void jogadaA(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog) {
    int v;
    do {

        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x[0].nome);
        scanf("%d %d", &linha, &coluna);
        fflush(stdout);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0)
            printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) && v == 0);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'G');
    printTabuleiro(lin, col, tab);
}

void jogadaB(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog) {
    int v;
    do {

        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x[0].nome);
        scanf("%d %d", &linha, &coluna);
        fflush(stdout);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0)
            printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) && v == 0);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'G');
    printTabuleiro(lin, col, tab);
}

void jogadaC(char **tab, int linha, int coluna, int lin, int col, jogador x[], int jog) {
    int v;
    do {

        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x[0].nome);
        scanf("%d %d", &linha, &coluna);
        fflush(stdout);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0)
            printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) && v == 0);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'G');
    printTabuleiro(lin, col, tab);
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