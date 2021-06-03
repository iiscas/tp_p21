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
        printf("--------------------\n");
        aux = aux->prox;
        i++;
    }
}

void printEstados(pJogada p, int n, int lin, int col) {
    int tam = nNosLista(p);
    pJogada temp = p;

    // ver se n de sucessoes é menor que o tamanho da lista
    if (tam < n) return;

    temp = p;
    // tirar o (tam-n+1)x no desde o inicio
    for (int i = 1; i < tam - n + 1; i++)
        temp = temp->prox;

    //imprimeReverso(temp);
    printTabuleiroEstados(lin, col, temp, p, n);
}

void imprimeReverso(pJogada x) {
    if (x == NULL)
        return;
    // imprime tudo
    imprimeReverso(x->prox);
    // imprime inicio
    printf("\nJogador %c \nPosicao da jogada no tabuleiro: %d %d\n", x->x.nome, x->linha, x->coluna);
    printf("--------------------\n");
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

void printTabuleiroEstados(int lin, int col, pJogada tabAtual, pJogada head, int n) {

    char **tabAux = NULL;
    tabAux = inicializaTabuleiroEstados(&lin, &col);

    int a;
    a = nNosLista(head) - n;
    if (head == NULL)
        return;

    //preencher com jogadas antes do pedido
    while (head != tabAtual) {
        if (head->x.jogada == 'A') {
            tabAux[head->linha][head->coluna] = 'G';
        }
        head = head->prox;
    }
    printTabuleiro(lin, col, tabAux);

    //preencher com jogadas pedidas
    while (tabAtual) {

        printf("\t -----------------------------------\n\t\t\t\t  Jogada %d\t\t\t\t\t\n\t -----------------------------------\n",
               a + 1);
        if (tabAtual->x.jogada == 'A') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'G';
        }
        for (int i = 0; i < lin; i++) {
            for (int j = 0; j < col; j++) {
                if (tabAux[i][j] != 'G')
                    tabAux[i][j] = '-';
            }
        }
        printTabuleiro(lin, col, tabAux);
        a++;
        tabAtual = tabAtual->prox;
    }
}

pJogada reverterListaJogadas(pJogada head) {
    pJogada nova = NULL;
    pJogada anterior = NULL;
    pJogada atual = head;
    pJogada prox = NULL;
    while (atual != NULL) {
        // Store next
        prox = atual->prox;

        // Reverse current node's pointer
        atual->prox = anterior;

        // Move pointers one position ahead.
        anterior = atual;
        atual = prox;
    }
    nova = anterior;

    /*printListaJogadas(nova);
    printf("\n AQUIII\n");
    printListaJogadas(head);
*/
    return nova;
}


