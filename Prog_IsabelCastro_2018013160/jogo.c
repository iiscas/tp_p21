
//
// Created by isabe on 18-05-2021.
//


#include "jogo.h"

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col) {
    int fimJogo = 0, nTurnos = 0;
    int a = 0, b = 1, v;
    int linha = 0, coluna = 0;

    do {
        printTabuleiro(*lin, *col, tab);
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printJogadas(&nTurnos, x[0]);

        if (nTurnos >= 0) {
            do {
                printf("\n>>");
                scanf("%s", &x[0].jogada);
                //fflush(stdout);
            } while (!((int) x[0].jogada == 65));
        }
        if (toupper(x[0].jogada) == 'A') {
            listaJogadas = jogadaA(tab, *lin, *col, x[0], listaJogadas);
        }

        printTabuleiro(*lin, *col, tab);
        printListaJogadas(listaJogadas);
        printf("Jogador %c e a sua vez! ", x[1].nome);
        printJogadas(&nTurnos, x[1]);

        if (nTurnos >= 0) {
            do {
                //printf("aqui\n");
                printf(">>");
                scanf("%s", &x[1].jogada);
                //fflush(stdout);
            } while (!((int) x[1].jogada == 65));
        }
        if (toupper(x[1].jogada) == 'A') {
            listaJogadas = jogadaA(tab, *lin, *col, x[1], listaJogadas);
        }
        printListaJogadas(listaJogadas);
        nTurnos++;
    } while (1);
}


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

pJogada jogadaA(char **tab, int lin, int col, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;
    //pJogada temp=NULL;
    do {

        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        fflush(stdout);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0)
            printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) || v == 0);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'G');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna);
    //printListaJogadas(listaJogadas);
    //printTabuleiro(lin, col, tab);
    return listaJogadas;
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

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c) {
    noJogada j;


    j.x->nome = x.nome;
    j.x->jogada = x.jogada;

    j.x->nPedras = x.nPedras;
    j.x->nAdicoes = x.nAdicoes;
    j.linha = l;
    j.coluna = c;
    printf("\nNome do jogador %c\n", j.x->nome);

    pJogada novaJogada =  malloc(sizeof(noJogada));
    if (novaJogada == NULL) {
        fprintf(stderr, "ERRO A ALOCAR MEMORIA");
        return lista;
    }
    *novaJogada = j;

    if (lista == NULL) {
        printf("\naqui\n");
        lista = novaJogada;
        novaJogada->prox = NULL;
    }
    else {
        pJogada aux = lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novaJogada;
        novaJogada->prox = NULL;
    }
    printListaJogadas(lista); // quando só tem uma jogada imprime só os dados de A mas dps
                              // imprime o B em cima dos dados de A
    return lista;

}

void printJogador(jogador *x) {
    printf("Jogador %c\n", x->nome);
    printf("Ultima jogada %c\n", x->jogada);
    printf("N. pedras usadas %d\n", x->nPedras);
    printf("N. de adicoes feitas %d\n", x->nAdicoes);
}

void printListaJogadas(pJogada lista) {
    int i = 1;
    if (lista == NULL) {
        puts("lista vazia");
    }
    pJogada aux = lista;
    printf("\n--------------------\nLista de jogadas\n--------------------\n");
    while (aux != NULL) {
        printf("--%d--\n", i);
        printJogador(aux->x);
        printf("Posicao da jogada no tabuleiro: %d %d\n", aux->linha, aux->coluna);
        printf("--------------------\n");
        aux = aux->prox;
        i++;
    }
}