#include "jogo.h"

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col) {
    int fimJogo = 0, nTurnos = 0;
    int a = 0, b = 1, v;
    int linha = 0, coluna = 0;
    int countG = 0, countY = 0, countR = 0;

    do {
        printTabuleiro(*lin, *col, tab);

        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printJogadas(nTurnos, x[0]);

        if (nTurnos == 0) {
            do {
                printf("\n>>");
                scanf("%s", &x[0].jogada);
            } while (!((int) x[0].jogada == 65));
        } else if (nTurnos > 0) {
            do {
                printf("\n>>");
                scanf("%s", &x[0].jogada);
            } while (!((int) x[0].jogada >= 65 && (int) x[0].jogada <= 69));
        }
        if (toupper(x[0].jogada) == 'A') {
            listaJogadas = jogadaA(tab, *lin, *col, x[0], listaJogadas);
        } else if (toupper(x[0].jogada) == 'B') {
            listaJogadas = jogadaB(tab, *lin, *col, x[0], listaJogadas);
        } else if (toupper(x[0].jogada) == 'C') {
            listaJogadas = jogadaC(tab, *lin, *col, x[0], listaJogadas);
        } else if (toupper(x[0].jogada) == 'D' && x[0].nPedras == 0) {
            listaJogadas = jogadaD(tab, *lin, *col, x[0], listaJogadas);
        } else if (toupper(x[0].jogada) == 'E' && x[0].nAdicoes <= 2) {
            listaJogadas = jogadaE(tab, lin, col, x[0], listaJogadas);
        }

        //printf("Linhas  %d Colunas %d\n",*lin,*col); // atualiza bem o numero de linhas
        printTabuleiro(*lin, *col, tab);
        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[1].nome);
        printJogadas(nTurnos, x[1]);

        if (nTurnos == 0) {
            do {
                printf("\n>>");
                scanf("%s", &x[1].jogada);
            } while (!((int) x[1].jogada == 65));
        } else if (nTurnos > 0) {
            do {
                printf("\n>>");
                scanf("%s", &x[1].jogada);
            } while (!((int) x[1].jogada >= 65 && (int) x[1].jogada <= 69));
        }
        if (toupper(x[1].jogada) == 'A') {
            listaJogadas = jogadaA(tab, *lin, *col, x[1], listaJogadas);
        } else if (toupper(x[1].jogada) == 'B') {
            listaJogadas = jogadaB(tab, *lin, *col, x[1], listaJogadas);
        } else if (toupper(x[1].jogada) == 'C') {
            listaJogadas = jogadaC(tab, *lin, *col, x[1], listaJogadas);
        } else if (toupper(x[1].jogada) == 'D' && x[1].nPedras == 0) {
            listaJogadas = jogadaD(tab, *lin, *col, x[1], listaJogadas);
        } else if (toupper(x[1].jogada) == 'E' && x[1].nAdicoes <= 2) {
            listaJogadas = jogadaE(tab, lin, col, x[1], listaJogadas);
        }

        ///////////////////////////// FIM DO TURNO/JOGADA ///////////////////////////////////
        printListaJogadas(listaJogadas);
        nTurnos++;
    } while (1);
}


int verificaJogada(char **tab, int lJogador, int cJogador) {
    //devolve 0 se não for possivel, 1 se for possivel
    if (tab[lJogador][cJogador] == '-')
        return 1;
    else if (tab[lJogador][cJogador] == 'G')
        return 2;
    else if (tab[lJogador][cJogador] == 'Y')
        return 3;
    else
        return 0;
}

void printJogadas(int count, jogador x) {
    if (count == 0) {
        printf("\n----------------------\nSó pode jogar uma peça verde! (A)\n----------------------\n");

    } else if (count >= 1) {
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

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0 || v == 2) printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) || v == 0 || v == 2);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'G');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna);
    return listaJogadas;
}

pJogada jogadaB(char **tab, int lin, int col, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v != 2) printf("\nNao ha pecas verdes!\n");
    } while (!(linha <= lin && coluna <= col) || v != 2);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'Y');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna);
    return listaJogadas;
}

pJogada jogadaC(char **tab, int lin, int col, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;
    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v != 3) printf("\nNao ha pecas amarelas!\n");
    } while (!(linha <= lin && coluna <= col) || v != 3);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'R');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna);
    return listaJogadas;
}

pJogada jogadaD(char **tab, int lin, int col, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0) printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= lin && coluna <= col) || v == 0);

    tab = preencheTabuleiro(lin, col, tab, linha, coluna, 'P');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna);
    return listaJogadas;
}

pJogada jogadaE(char **tab, int *lin, int *col, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;
    char **tabuleiro=NULL;

    do {
        printf("\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", x.nome);
        scanf("%d", &linha);
        if(linha==1){
            tab= alteraNLinhas(lin,col,tab);
        }
        else if(linha==2){
            tab= alteraNLinhas(lin,col,tab); //altera colunas
        }

    } while (!(linha <=2 && coluna ==0  && x.nAdicoes<2));

    listaJogadas = adicionaFimLista(listaJogadas, x, -1, -1);
    printTabuleiro(*lin ,*col,tab);
    return listaJogadas;
}



////////////////////// LISTA LIGADA ///////////////////////////////
pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c) {
    noJogada j;
    pJogada novaJogada, aux;
    j.x = x;
    j.linha = l;
    j.coluna = c;

    novaJogada = malloc(sizeof(noJogada));
    if (novaJogada == NULL) {
        fprintf(stderr, "ERRO A ALOCAR MEMORIA");
        return lista;
    }
    *novaJogada = j;

    if (lista == NULL) {
        printf("\naqui\n");
        lista = novaJogada;
        novaJogada->prox = NULL;
    } else {
        aux = lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novaJogada;
        novaJogada->prox = NULL;
    }
    return lista;
}

void printJogador(jogador x) {
    printf("Jogador %c\n", x.nome);
    printf("Ultima jogada %c\n", x.jogada);
    printf("N. pedras usadas %d\n", x.nPedras);
    printf("N. de adicoes feitas %d\n", x.nAdicoes);
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

void analisaPecas(char **tab, int l, int c, int *countG, int *countY, int *countR) {

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (tab[i][j] == 'G')
                *countG++;
            else if (tab[i][j] == 'Y')
                *countY++;
            else if (tab[i][j] == 'R')
                *countR++;
        }
    }
}
