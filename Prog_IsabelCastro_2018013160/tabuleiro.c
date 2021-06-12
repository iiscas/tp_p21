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
    *lin = intUniformRnd(3, 3); // esta sempre a dar 5 E NÃO CRIA
    *col = *lin;
    char **tab;
// aloca um vetor de lin ponteiros para linhas
    tab = (char **) malloc(*lin * sizeof(char *));
    if (tab == NULL) {
        puts("Tabuleiro nao foi alocado!");
        return tab;
    }
// ajusta os demais ponteiros de linhas (i > 0)
    for (int i = 0; i < *lin; i++) {
        tab[i] = (char *) malloc(sizeof(char) * (*col));
        if (tab == NULL) {
            puts("Tabuleiro nao foi alocado!");
            return tab;
        }
    }
    for (int i = 0; i < *lin; i++) {
        for (int j = 0; j < *col; j++) {
            tab[i][j] = '-';
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
        puts("Tabuleiro nao foi alocado!");
        return tab;
    }
// ajusta os ponteiros de linhas (i > 0)
    for (int i = 0; i < *lin; i++) {
        tab[i] = (char *) malloc(sizeof(char) * (*col));
        if (tab == NULL) {
            puts("Tabuleiro nao foi alocado!");
            return tab;
        }
    }
    for (int i = 0; i < *lin; i++) {
        for (int j = 0; j < *col; j++) {
            tab[i][j] = '-';
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
                if (tab[i][j] != 'G' && tab[i][j] != 'Y' && tab[i][j] != 'R' && tab[i][j] != 'P')
                    tab[i][j] = '-';
            }
        }
        //tab[0][tam[1]] = '-'; //nem assim funciona wtf //printTabuleiro(tam, tab); //printf("\n<--dentro do altera \n");
    }
    return tab;
}

char **preencheTabuleiro(int tam[2], char **tab, int lEscolhida, int cEscolhida, char letra) {
    for (int i = 0; i < tam[0]; ++i) {
        for (int j = 0; j < tam[1]; ++j) {
            if (i == lEscolhida && j == cEscolhida) tab[i][j] = letra;
        }
    }
    return tab;
}

char **recuperaTabuleiro(pJogada listaJ) {

    char **tabAux = NULL;
    pJogada head = listaJ;
    int tam[2];
    //a = nNosLista(head) - n;
    tabAux = inicializaTabuleiroEstados(&head->tamTab[0], &head->tamTab[1]);
    //preencher com jogadas antes do pedido
    while (head != NULL) {
        if (head->x.jogada == 'A') {
            tabAux[head->linha][head->coluna] = 'G';
        } else if (head->x.jogada == 'B') {
            tabAux[head->linha][head->coluna] = 'Y';
        } else if (head->x.jogada == 'C') {
            tabAux[head->linha][head->coluna] = 'R';
        } else if (head->x.jogada == 'D') {
            tabAux[head->linha][head->coluna] = 'P';
        } else if (head->x.jogada ==
                   'E') { //fazer aqui um realloc para ter espaço para inserir a linha //foi alterado a linha na proxima
            if (head->prev->tamTab[0] != head->tamTab[0]) {
                tam[0] = head->prev->tamTab[0];
                tam[1] = head->prev->tamTab[1];
                tabAux = alteraNLinhas(tam, tabAux);
            }
            if (head->prev->tamTab[1] != head->tamTab[1]) {
                tam[0] = head->prev->tamTab[0];
                tam[1] = head->prev->tamTab[1];
                tabAux = alteraNColunas(tam, tabAux);
            }
        }
        for (int i = 0; i < head->tamTab[0]; i++) {
            for (int j = 0; j < head->tamTab[1]; j++) {
                if (tabAux[i][j] != 'G' && tabAux[i][j] != 'Y' && tabAux[i][j] != 'R' && tabAux[i][j] != 'P')
                    tabAux[i][j] = '-';
            }
        }
        head = head->prox;
    }

    free(head);
    return tabAux;
}
