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
    int tamTabuleiro[2] = {*lin, *col};

    do {
        printTabuleiro(tamTabuleiro, tab);

        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printPedirEstados(listaJogadas, nTurnos, tamTabuleiro);
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
        listaJogadas = opcaoEscolhida(tab, x[0], listaJogadas, tamTabuleiro, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(tamTabuleiro, tab);
        } else if (escolha == 2) {
            tab = alteraNColunas(tamTabuleiro, tab); //altera colunas
        }
        a = CheckLinhas(tab, tamTabuleiro);
        printTabuleiro(tamTabuleiro, tab);
        if (a != -1) {
            if(procuraVencedor(listaJogadas, a, 0)==1)
                fimJogo=1;
        }
        fflush(stdout);
        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[1].nome);
        printPedirEstados(listaJogadas, nTurnos, tamTabuleiro);// ARRANJAR FORMA DE IDENTIFICAR QUANDO AUMENTA AS LINHAS
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
        listaJogadas = opcaoEscolhida(tab, x[1], listaJogadas, tamTabuleiro, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(tamTabuleiro, tab);
        } else if (escolha == 2) {
            tab = alteraNColunas(tamTabuleiro, tab); //altera colunas
        }

        a = CheckLinhas(tab, tamTabuleiro);
        if (a != -1) {
            if(procuraVencedor(listaJogadas, a, 0)==1)
                fimJogo=1;
        }
        fflush(stdout);
        ///////////////////////////// FIM DO TURNO/JOGADA ///////////////////////////////////
        printListaJogadas(listaJogadas);
        nTurnos++;
    } while (fimJogo!=1);
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

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0 || v == 2) printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) || v == 0 || v == 2);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'G');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaB(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v != 2) printf("\nNao ha pecas verdes!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) || v != 2);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'Y');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaC(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;
    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v != 3) printf("\nNao ha pecas amarelas!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) || v != 3);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'R');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaD(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0) printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) || v == 0);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaE(char **tab, int *escolha, jogador x, pJogada listaJogadas, int tamTab[2]) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", x.nome);
        scanf("%d", &linha);
    } while (!(linha <= 2 && x.nAdicoes < 2));
    *escolha = linha;
    listaJogadas = adicionaFimLista(listaJogadas, x, -1, -1, tamTab);
    printTabuleiro(tamTab,tab);
    return listaJogadas;
}


////////////////////// LISTA LIGADA ///////////////////////////////
pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c, int tamTab[2]) {

    noJogada j;
    pJogada novaJogada, aux;
    j.x = x;
    j.linha = l;
    j.coluna = c;
    j.tamTab[1] = tamTab[1];
    j.tamTab[0] = tamTab[0];

    //ALOCAR MEMORIA
    novaJogada = malloc(sizeof(noJogada));

    if (novaJogada == NULL) {
        fprintf(stderr, "ERRO A ALOCAR MEMORIA");
        return lista;
    }
    *novaJogada = j;

    //ADICIONAR DADOS
    if (lista == NULL) { //primeiro nó
        lista = novaJogada;
        novaJogada->prox = NULL;
        novaJogada->prev = NULL;

    } else {

        aux = lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novaJogada;
        novaJogada->prox = NULL;
        novaJogada->prev = aux;
    }
    return lista;
}

void printJogador(jogador x) {
    printf("Jogador %c\n", x.nome);
    printf("Ultima jogada %c\n", x.jogada);
    printf("N. pedras usadas %d\n", x.nPedras);
    printf("N. de adicoes feitas %d\n", x.nAdicoes);
}

void printPedirEstados(pJogada x, int nTurnos, int tamTab[2]) {
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
            printEstados(x, k, tamTab);
        } else {
            printf("\n-----------------------\nNao ha jogadas ainda!\nJogo vai continuar...\n-----------------------\n");
            return;
        }
    } else return;
}

int CheckLinhas(char **tab, int tamTab[2]) {
    int count = 1, linha = 0;
    for (int i = 0; i < tamTab[0]; i++) {
        for (int j = 0; j < tamTab[1]; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-') {
                count++;
                linha = i;
            }

        }

    }
    if (count == tamTab[1]) {
        printf("HA MATCH NA LINHA %d \n", linha);
        return linha;
    } else
        return -1;
}

int checkColunas(char **tab, int tamTab[2]) {
    int count = 1, coluna = 0;
    for (int i = 0; i < tamTab[1]; i++) {
        for (int j = 0; j < tamTab[0]; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-') {
                count++;
                coluna = i;
            }

        }

    }
    if (count == tamTab[1])
        printf("HA MATCH NA COLUNA %d \n", coluna);
    return coluna;
}

pJogada opcaoEscolhida(char **tab, jogador x, pJogada listaJogadas, int tamTab[2], int *escolha) {
    if (x.jogada == 'A') {
        listaJogadas = jogadaA(tab, tamTab, x, listaJogadas);
    } else if (x.jogada == 'B') {
        listaJogadas = jogadaB(tab, tamTab, x, listaJogadas);
    } else if (x.jogada == 'C') {
        listaJogadas = jogadaC(tab, tamTab, x, listaJogadas);
    } else if (x.jogada == 'D' && x.nPedras == 0) {
        listaJogadas = jogadaD(tab, tamTab, x, listaJogadas);
    } else if (x.jogada == 'E' && x.nAdicoes <= 2) {
        listaJogadas = jogadaE(tab, escolha, x, listaJogadas, tamTab);
    }
    return listaJogadas;
}

int procuraVencedor(pJogada listaJogadas, int x, int tipo) {

    if (listaJogadas == NULL)
        return -1;

    pJogada atual = listaJogadas;
    while (atual->prox != NULL) { // vai procurar o ultimo no
        atual = atual->prox; //continua ate ter chegar la
    }

    while (atual != NULL) { // inicia no ultimo no e ate ao primeiro
        if (tipo == 0) { //procura ultima jogada na linha x
            if (atual->linha == x) {
                printf("\nUltima jogada do jogador %c\n na linha/coluna:%d %d \n", atual->x.nome, atual->linha,
                       atual->coluna);
                return 1;
            }
        }
        atual = atual->prev;
    }
    free(atual);
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