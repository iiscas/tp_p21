#include <stdbool.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "sucessaoJogadas.h"


void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int *lin, int *col) {
    int fimJogo = 0, nTurnos = 0;
    int a = 0, b = 1, v;
    int linha = 0, coluna = 0;
    int countG = 0, countY = 0, countR = 0;
    int escolha = 0;

    do {
        printTabuleiro(*lin, *col, tab);

        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printPedirEstados(listaJogadas, nTurnos, *lin, *col);
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
        listaJogadas = opcaoEscolhida(tab, x[0], listaJogadas, *lin, *col, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(lin, col, tab);
        } else if (escolha == 2) {
            tab = alteraNColunas(lin, col, tab); //altera colunas
        }
        a = CheckLinhas(tab, *lin, *col);
        printTabuleiro(*lin, *col, tab);
        if (a != -1)
            procuraVencedor(listaJogadas, a, 0);
        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[1].nome);
        printPedirEstados(listaJogadas, nTurnos, *lin, *col); // ARRANJAR FORMA DE IDENTIFICAR QUANDO AUMENTA AS LINHAS
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
        listaJogadas = opcaoEscolhida(tab, x[1], listaJogadas, *lin, *col, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(lin, col, tab);
        } else if (escolha == 2) {
            tab = alteraNColunas(lin, col, tab); //altera colunas
        }

        a = CheckLinhas(tab, *lin, *col);
        if (a != -1)
            procuraVencedor(listaJogadas, a, 0);
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

pJogada jogadaE(char **tab, int *escolha, jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", x.nome);
        scanf("%d", &linha);
    } while (!(linha <= 2 && x.nAdicoes < 2));
    *escolha = linha;
    listaJogadas = adicionaFimLista(listaJogadas, x, -1, -1);
    //printTabuleiro(*lin ,*col,tab);
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

void printPedirEstados(pJogada x, int nTurnos, int lin, int col) {
    int k = 0;
    char escolha;
    int count = 0;
    do {
        printf("\nPretende visualizar o estado do tabuleiro? (S)/(N):\n>>");
        scanf(" %c", &escolha);
    } while (!(escolha == 'S' || escolha == 'N'));

    if (escolha == 'S') {
        if (nNosLista(x) > 0) {
            do {
                printf("\nQuantas jogadas quer visualizar?\n>> ");
                scanf("%d", &k);
            } while (k > nNosLista(x));
            printEstados(x, k, lin, col);
        } else {
            printf("\n-----------------------\nNao ha jogadas ainda!\nJogo vai continuar...\n-----------------------\n");
            return;
        }
    } else
        return;

}


int CheckLinhas(char **tab, int lin, int col) {
    int count = 1, linha = 0;
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-') {
                count++;
                linha = i;
            }

        }

    }
    if (count == col) {
        printf("HA MATCH NA LINHA %d \n", linha);
        return linha;
    } else
        return -1;
}

int checkColunas(char **tab, int lin, int col) {
    int count = 1, coluna = 0;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < lin; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-') {
                count++;
                coluna = i;
            }

        }

    }
    if (count == col)
        printf("HA MATCH NA COLUNA %d \n", coluna);
    return coluna;
}

pJogada opcaoEscolhida(char **tab, jogador x, pJogada listaJogadas, int lin, int col, int *escolha) {
    if (x.jogada == 'A') {
        listaJogadas = jogadaA(tab, lin, col, x, listaJogadas);
    } else if (x.jogada == 'B') {
        listaJogadas = jogadaB(tab, lin, col, x, listaJogadas);
    } else if (x.jogada == 'C') {
        listaJogadas = jogadaC(tab, lin, col, x, listaJogadas);
    } else if (x.jogada == 'D' && x.nPedras == 0) {
        listaJogadas = jogadaD(tab, lin, col, x, listaJogadas);
    } else if (x.jogada == 'E' && x.nAdicoes <= 2) {
        listaJogadas = jogadaE(tab, escolha, x, listaJogadas);
    }
    return listaJogadas;
}

void procuraVencedor(pJogada listaJogadas, int x, int tipo) {

    pJogada revertido = NULL;
    revertido= copiaListaJogadas(listaJogadas);


    printf("\n AQUIII\n");
    printListaJogadas(listaJogadas);

    while (revertido != NULL) {
        if (tipo == 0) { //procura ultima jogada na linha x
            if (revertido->linha == x) {
                printf("\nUltima jogada do jogador %c\n na linha/coluna:%d %d \n", revertido->x.nome, revertido->linha,
                       revertido->coluna);
                return;
            }
        }
        revertido = revertido->prox;
    }
    free(revertido);

}

/*int checkDiagonais(char **tab, int lin, int col) {
    int match = 1;
    int ganhou = 0;

    // Check the first diagonal.
    for (int i = 0; i < lin && !ganhou; lin++) {
        if (tab[lin][lin] != 'G') {
            match = 0;
        }
        if (tab[lin][lin] != 'Y') {
            match = 0;
        }
        if (tab[lin][lin] != 'R') {
            match = 0;
        }
    }

    if (match != 1) {
        int coluna = lin - 1;
        for (row = 0; row < tab && !won; row++, col--) {
            if (tab[row][col] != mark) {
                match = 0;
            }
        }
    }
    won = match;


    return 0;
}
 */