//ISABEL RAMOS CASTRO
//2018013160
#include "historico.h"
#include "tabuleiro.h"

void printJogadas(int count, jogador x) {
    if (count == 0) {
        printf("\n---------------------------------\nSó pode jogar uma peça verde! (A)\n---------------------------------\n");
    } else if (count >= 1) {
        printf("\n-----------------------------------\nJa pode fazer as seguintes jogadas\n-----------------------------------\n"
               "(A)- Colocar uma peça Verde numa célula vazia\n"
               "(B)- Trocar uma peça Verde que esteja colocada no tabuleiro por uma peça Amarela\n"
               "(C)- Trocar uma peça Amarela que esteja colocada no tabuleiro por uma peça Vermelha\n");
        printf("(D)- Colocar uma pedra numa célula vazia.(Usado %d vezes)\n", x.nPedras);
        printf("(E)- Adicionar uma linha ou uma coluna ao final do tabuleiro.(Usado %d vezes)\n", x.nAdicoes);
        printf("(F)- Interromper o jogo e guardar para mais tarde!\n");
    }
}

void printListaJogadas(pJogada lista) {
    int i = 1;
    if (lista == NULL) return;
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

void printEstados(pJogada p, int n) {
    if (p == NULL) return;
    int tam = nNosLista(p);
    pJogada temp = NULL;
    // ver se n de sucessoes é menor que o tamanho da lista
    if (tam < n) return;
    temp = p;
    // tirar o (tam-n+1)x nó desde o inicio
    for (int i = 1; i < tam - n + 1; i++) //JA FUNCIONA??? VEER
        temp = temp->prox;
    printTabuleiroEstados(temp, p, n);
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

void printTabuleiroEstados(pJogada tabAtual, pJogada listaJ, int n) {
    if (listaJ == NULL) return;
    char **tabAux = NULL;
    pJogada head = listaJ;
    int a, tam[2];
    a = nNosLista(head) - n;
    tabAux = inicializaTabuleiroEstados(&head->tamTab[0], &head->tamTab[1]);
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
    printTabuleiro(head->tamTab, tabAux);
    //preencher com jogadas pedidas
    while (tabAtual) {
        printf("\t -----------------------------------\n\t\t\t\t  Jogada %d\t\t\t\t\t\n\t -----------------------------------\n",a + 1);
        if (tabAtual->x.jogada == 'A') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'G';
        } else if (tabAtual->x.jogada == 'B') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'Y';
        } else if (tabAtual->x.jogada == 'C') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'R';
        } else if (tabAtual->x.jogada == 'D') {
            tabAux[tabAtual->linha][tabAtual->coluna] = 'P';
        } else if (tabAtual->x.jogada == 'E') {
            if (tabAtual->prev->tamTab[0] != tabAtual->tamTab[0]) {
                tam[0] = tabAtual->prev->tamTab[0];
                tam[1] = tabAtual->prev->tamTab[1];
                tabAux = alteraNLinhas(tam, tabAux);
            }
            if (tabAtual->prev->tamTab[1] != tabAtual->tamTab[1]) {
                tam[0] = tabAtual->prev->tamTab[0];
                tam[1] = tabAtual->prev->tamTab[1];
                tabAux = alteraNColunas(tam, tabAux);
            }
        }
        for (int i = 0; i < tabAtual->tamTab[0]; i++) {
            for (int j = 0; j < tabAtual->tamTab[1]; j++) {
                if (tabAux[i][j] != 'G' && tabAux[i][j] != 'Y' && tabAux[i][j] != 'R' && tabAux[i][j] != 'P')
                    tabAux[i][j] = '-';
            }
        }
        printTabuleiro(tabAtual->tamTab, tabAux);
        a++;
        tabAtual = tabAtual->prox;
    }

    freeTabuleiro(tabAux,tam[0]);
}

void printPedirEstados(pJogada x) {
    int k = 0;
    char escolha;
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
            printEstados(x, k);
        } else {
            printf("\n-----------------------\nNao ha jogadas ainda!\nJogo vai continuar...\n-----------------------\n");
            return;
        }
    } else return;
}



