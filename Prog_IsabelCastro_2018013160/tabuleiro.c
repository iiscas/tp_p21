//ISABEL RAMOS CASTRO
//2018013160
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
        for (int z = 0; z < tam[1] * 7; z++) {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

char **inicializaTabuleiro(int *lin, int *col) {
    *lin = intUniformRnd(3, 5);
    *col = *lin;
    char **tab;
// aloca um vetor de lin ponteiros para linhas
    tab = (char **) malloc(*lin * sizeof(char *));
    if (tab == NULL) {
        puts("Tabuleiro nao foi alocado!");
        return tab;
    }
// ajusta os ponteiros para linhas (i > 0)
    for (int i = 0; i < *lin; i++) {
        tab[i] = (char *) malloc(sizeof(char) * (*col));
        if (tab == NULL) {
            puts("Tabuleiro nao foi alocado!");
            return tab;
        }
    }
    //preenche com - o tabuleiro
    for (int i = 0; i < *lin; i++) {
        for (int j = 0; j < *col; j++) {
            tab[i][j] = '-';
        }
    }
    return tab;
}

char **inicializaTabuleiroEstados(int *lin, int *col) {
    char **tab;
    tab = (char **) malloc(*lin * sizeof(char *));
    if (tab == NULL) {
        puts("Tabuleiro nao foi alocado!");
        return tab;
    }
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
        for (int i = 0; i < tam[0]; i++) {
            for (int j = 0; j < tam[1]; j++) {
                if (tab[i][j] != 'G' && tab[i][j] != 'Y' && tab[i][j] != 'R' && tab[i][j] != 'P')
                    tab[i][j] = '-';
            }
        }
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

char **recuperaTabuleiro(pJogada listaJ, int tam[2]) {
    char **tabAux = NULL;
    pJogada head = listaJ;
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
        } else if (head->x.jogada =='E') {
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

    return tabAux;
}

int checkTabuleiro(char **tab, int tamTab[2], int *tipo) {
    int count = 1, linha = 0, coluna = 0;
    int count1 = 1, count2 = 1, count3 = 1;
    int diag1 = 0, diag2 = 0, matchD = 0;
    //check se há match nas linhas
    for (int i = 0; i < tamTab[0]; i++) {
        count = 1;
        for (int j = 0; j < tamTab[1]; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-' && tab[i][j] != 'P') {
                count++;
                linha = i;
                if (count == tamTab[1]) {
                    printf("\n-------------------\nLinha %d completa!\n-------------------\n", linha);
                    *tipo = 0;
                    return linha;
                }
            }
        }
    }
    // check se há match nas colunas
    for (int i = 0; i < tamTab[1]; i++) {
        count1 = 1;
        for (int j = 0; j < tamTab[0] - 1; j++) {
            if (tab[j][i] == tab[j + 1][i] && tab[j][i] != '-' && tab[i][j] != 'P') {
                count1++;
                coluna = i;
                if (count1 == tamTab[0]) {
                    printf("\n-------------------\nColuna %d completa!\n-------------------\n", coluna);
                    *tipo = 1;
                    return coluna;
                }
            }
        }

    }
    if (tamTab[0] == tamTab[1]) { //so procura nas diagonais se for quadrado
        //check se há match na diagonal principal (00,11,22,33,44)
        for (int i = 0; i < tamTab[0] - 1; i++) {
            if (tab[i][i] == tab[i + 1][i + 1] & tab[i][i] != '-' && tab[i][i] != 'P') {
                count2++;
                diag1 = i;
                matchD = 1;
                if (count2 == tamTab[0]) {
                    printf("\n-------------------\nDiagonal completa!\n-------------------\n");
                    *tipo = 2;
                    return diag1;
                }
            }
        }
        if (matchD != 1) {
            //check se há match na diagonal secundaria se nao houver na principal (00,11,22,33,44)
            int col = tamTab[1] - 1;
            for (int i = 0; i < tamTab[0] - 1; i++, col--) {
                if (tab[i][col] == tab[i + 1][col - 1] && tab[i][col] != '-' && col != 0 && tab[i][col] != 'P') {
                    count3++;
                    diag2 = col;

                    if (count3 == tamTab[1]) {
                        printf("\n-------------------\nDiagonal completa!\n-------------------\n");
                        *tipo = 3;
                        return diag2;
                    }
                }
            }
        }
    }
    return -1;
}

void freeTabuleiro(char **tab,int lin) {
    {
        for(int i = 0; i < lin; i++)
        {
            free(tab[i]);
        }
        free(tab);
    }
}
