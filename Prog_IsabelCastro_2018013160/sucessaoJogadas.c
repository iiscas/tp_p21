#include "sucessaoJogadas.h"

void printJogadas(int count, jogador x) {
    if (count == 0) {
        printf("\n---------------------------------\nSó pode jogar uma peça verde! (A)\n---------------------------------\n");

    } else if (count >= 1) {
        printf("\n----------------------\nJa pode fazer as seguintes jogadas\n----------------------\n"
               "(A)- Colocar uma peça Verde numa célula vazia\n"
               "(B)- Trocar uma peça Verde que esteja colocada no tabuleiro por uma peça Amarela\n"
               "(C)- Trocar uma peça Amarela que esteja colocada no tabuleiro por uma peça Vermelha\n");
        printf("(D)- Colocar uma pedra numa célula vazia.(Usado %d vezes)\n", x.nPedras);
        printf("(E)- Adicionar uma linha ou uma coluna ao final do tabuleiro.(Usado %d vezes)\n", x.nAdicoes);
    }
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
        printf("Tamanho do tabuleiro na jogada: [%d][%d]\n", aux->tamTab[0], aux->tamTab[1]);
        printf("--------------------\n");
        aux = aux->prox;
        i++;
    }
}

void printEstados(pJogada p, int n, int tamTab[2]) {
    int tam = nNosLista(p);
    pJogada temp = p;

    // ver se n de sucessoes é menor que o tamanho da lista
    if (tam < n) return;

    temp = p;
    // tirar o (tam-n+1)x no desde o inicio
    if (n == 1) {
        temp = temp->prev;

    } else {
        for (int i = 0; i < tam - n + 1; i++)
            temp = temp->prox;
    }
    //imprimeReverso(p);
    printTabuleiroEstados(tamTab,temp, p, n);
}

void printListaJogadasReverso(pJogada x) {
    if (x == NULL)
        return;

    pJogada atual = x;
    while (atual->prox != NULL) { // vai procurar o ultimo no
        atual = atual->prox; //continua ate ter chegar la
    }
    while (atual != NULL) { // inicia no ultimo no e ate ao primeiro
        printf("\n--------------------\nJogador %c \nPosicao da jogada no tabuleiro: %d %d\n", atual->x.nome,
               atual->linha, atual->coluna);
        printf("--------------------\n");

    }
}

int nNosLista(pJogada p) {
    int count = 0;
    pJogada atual = p;

    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void printTabuleiroEstados(int tamTab[2],pJogada tabAtual, pJogada head, int n) {
    char **tabAux = NULL;
    tabAux = inicializaTabuleiroEstados(&tamTab[0], &tamTab[1]);
    int a;

    a = nNosLista(head) - n;
    if (head == NULL)
        return;

    //preencher com jogadas antes do pedido
    while (head != tabAtual) {
        if (head->x.jogada == 'A') {
            tabAux[head->linha][head->coluna] = 'G';
        } else if (head->x.jogada == 'B') {
            tabAux[head->linha][head->coluna] = 'Y';
        } else if (head->x.jogada == 'C') {
            tabAux[head->linha][head->coluna] = 'R';
        } else if (head->x.jogada == 'D') {
            tabAux[head->linha][head->coluna] = 'P';
        }

        head = head->prox;
    }
    printTabuleiro(tamTab, tabAux);
    //preencher com jogadas pedidas
    while (tabAtual) {
        printf("\t -----------------------------------\n\t\t\t\t  Jogada %d\t\t\t\t\t\n\t -----------------------------------\n",
               a + 1);
        if (tabAtual->x.jogada == 'A') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'G';
        } else if (tabAtual->x.jogada == 'B') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'Y';
        } else if (tabAtual->x.jogada == 'C') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'R';
        } else if (tabAtual->x.jogada == 'D') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'P';
        }
        for (int i = 0; i < tamTab[0]; i++) {
            for (int j = 0; j < tamTab[1]; j++) {
                if (tabAux[i][j] < 65)
                    tabAux[i][j] = '-';
            }
        }
        printTabuleiro(tamTab, tabAux);
        a++;
        tabAtual = tabAtual->prox;
    }
    free(tabAtual);
}




