#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
#pragma ide diagnostic ignored "cert-err34-c"

#include "jogo.h"
#include "historico.h"

void iniciaJogo(char **tab, jogador x[], pJogada listaJogadas, int tamTabuleiro[2], char pc) {
    int nTurnos = 0, a = 0, escolha = 0;
    //int tamTabuleiro[2] = {*lin, *col};
    int tipoVencedor = 0;

    while (1) {
        printTabuleiro(tamTabuleiro, tab);
        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printPedirEstados(listaJogadas, nTurnos, tamTabuleiro);
        printJogadas(nTurnos, x[0]);
        escolheJogada(&x[0], nTurnos);

        //jogada ja escolhida
        listaJogadas = opcaoEscolhida(tab, &x[0], listaJogadas, tamTabuleiro, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(tamTabuleiro, tab);
            escolha = 0;
        } else if (escolha == 2) {
            //printf("111  --TAMANHO DO TABULEIRO: %d %d \n",tamTabuleiro[0],tamTabuleiro[1]);
            tab = alteraNColunas(tamTabuleiro, tab);
            //printf("TAMANHO DO TABULEIRO: %d %d \n",tamTabuleiro[0],tamTabuleiro[1]);//altera colunas
            escolha = 0;
        }
        printTabuleiro(tamTabuleiro, tab);

        //verifica se ha algum vencedor
        a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
        fflush(stdout);
        if (a > -1) //se tabuleiro encontrou algo completo
            if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
        //fflush(stdout);

        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        if (pc == 'N') {
            printf("Jogador %c e a sua vez! ", x[1].nome);
            printPedirEstados(listaJogadas, nTurnos,
                              tamTabuleiro);// ARRANJAR FORMA DE IDENTIFICAR QUANDO AUMENTA AS LINHAS
            printJogadas(nTurnos, x[1]);
            escolheJogada(&x[1], nTurnos);

            //jogada já escolhida
            listaJogadas = opcaoEscolhida(tab, &x[1], listaJogadas, tamTabuleiro, &escolha);
            if (escolha == 1) {
                tab = alteraNLinhas(tamTabuleiro, tab);
                escolha = 0;
            } else if (escolha == 2) {
                tab = alteraNColunas(tamTabuleiro, tab); //altera colunas
                escolha = 0;
            }
            printTabuleiro(tamTabuleiro, tab);
            //verifica se há algum vencedor
            a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
            //fflush(stdout);
            if (a > -1)
                if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
            fflush(stdout);
        } else if (pc == 'S') {

            escolheJogadaPC(&x[1], nTurnos);
            listaJogadas = opcaoEscolhidaPC(tab, &x[1], listaJogadas, tamTabuleiro, &escolha);
            printTabuleiro(tamTabuleiro, tab);
            //verifica se há algum vencedor
            a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
            //fflush(stdout);
            if (a > -1)
                if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
            fflush(stdout);
        }
        //////////Jogadas PC ///////////////



        ///////////////////////////// FIM DO TURNO/JOGADA ///////////////////////////////////
        nTurnos++;
    }
    printListaJogadas(listaJogadas);
    printf("\n\nVoltando ao menu inicial.....\n\n");
    sleep(1);
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

pJogada jogadaD(char **tab, int tamTab[2], pJogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x->nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v == 0) printf("\nPosicao ja ocupada!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) || v == 0);
    x->nPedras++;
    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
    listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaE(char **tab, int *escolha, pJogador x, pJogada listaJogadas, int tamTab[2]) {
    int v;
    int linha = 0, temp[2];
    temp[0] = tamTab[0];
    temp[1] = tamTab[1];

    do {
        printf("\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", x->nome);
        scanf("%d", &linha);
    } while (!(linha <= 2));
    *escolha = linha;
    (x->nAdicoes)++;
    if (linha == 1)
        temp[0]++;
    else if (linha == 2)
        temp[1]++;
    listaJogadas = adicionaFimLista(listaJogadas, *x, -1, -1, temp);
    printTabuleiro(tamTab, tab);
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

int checkTabuleiro(char **tab, int tamTab[2], int *tipo) {
    int count = 1, linha = 0, coluna = 0;
    int count1 = 1, count2 = 1, count3 = 1;
    int diag1 = 0, diag2 = 0, matchD = 0;

    //check se há match nas linhas
    for (int i = 0; i < tamTab[0]; i++) {
        for (int j = 0; j < tamTab[1]; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-') {
                //printf("AQUI\n");
                count++;
                linha = i;
            }
        }
    }
    // check se há match nas colunas
    for (int i = 0; i < tamTab[1]; i++) {
        for (int j = 0; j < tamTab[0] - 1; j++) {
            if (tab[j][i] == tab[j + 1][i] && tab[j][i] != '-') {
                //printf("AQUI\n");
                count1++;
                coluna = i;
            }
        }
    }
    if (tamTab[0] == tamTab[1]) { //so procura nas diagonais se for quadrado
        //check se há match na diagonal principal (00,11,22,33,44)
        for (int i = 0; i < tamTab[0] - 1; i++) {
            if (tab[i][i] == tab[i + 1][i + 1] & tab[i][i] != '-') {
                count2++;
                diag1 = i;
                matchD = 1;
            }
        }
        if (matchD != 1) {
            //check se há match na diagonal secundaria se nao houver na principal (00,11,22,33,44)
            int col = tamTab[1] - 1;
            for (int i = 0; i < tamTab[0] - 1; i++, col--) {
                if (tab[i][col] == tab[i + 1][col - 1] && tab[i][col] != '-' && col != 0) {
                    count3++;
                    diag2 = col;
                }
            }
        }
    }

    if (count1 == tamTab[0]) {
        printf("\n-------------------\nColuna %d completa!\n-------------------\n", coluna);
        *tipo = 1;
        return coluna;
    } else if (count == tamTab[1]) {
        printf("\n-------------------\nLinha %d completa!\n-------------------\n", linha);
        *tipo = 0;
        return linha;
    } else if (count2 == tamTab[0]) {
        printf("\n-------------------\nDiagonal principal completa!\n-------------------\n");
        *tipo = 2;
        return diag1;
    } else if (count3 == tamTab[1]) {
        printf("\n-------------------\nDiagonal secundaria completa!\n-------------------\n");
        *tipo = 3;
        return diag2;
    } else return -1;
}

pJogada opcaoEscolhida(char **tab, pJogador x, pJogada listaJogadas, int tamTab[2], int *escolha) {
    if (x->jogada == 'A') {
        listaJogadas = jogadaA(tab, tamTab, *x, listaJogadas);
    } else if (x->jogada == 'B') {
        listaJogadas = jogadaB(tab, tamTab, *x, listaJogadas);
    } else if (x->jogada == 'C') {
        listaJogadas = jogadaC(tab, tamTab, *x, listaJogadas);
    } else if (x->jogada == 'D') {
        listaJogadas = jogadaD(tab, tamTab, x, listaJogadas);
    } else if (x->jogada == 'E') {
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
                printf("\n-------------------------------------\nJogador %c e o vencedor!\n", atual->x.nome);
                printf("Jogada vencedora na posicao: [%d][%d]\n-------------------------------------\n", atual->linha,
                       atual->coluna);
                return 1;
            }
        } else if (tipo == 1) { //procura ultima jogada na coluna x
            if (atual->coluna == x) {
                printf("\n-------------------------------------\nJogador %c e o vencedor!\n", atual->x.nome);
                printf("Jogada vencedora na posicao: [%d][%d]\n-------------------------------------\n", atual->linha,
                       atual->coluna);
                return 1;
            }
        } else if (tipo == 2) { //procura ultima jogada na diagonal principal
            if (atual->coluna == atual->linha) {
                printf("\n-------------------------------------\nJogador %c e o vencedor!\n", atual->x.nome);
                printf("Jogada vencedora na posicao: [%d][%d]\n-------------------------------------\n", atual->linha,
                       atual->coluna);
                return 1;
            }
        } else if (tipo == 3) { //procura ultima jogada na diagonal secundária
            if (atual->coluna == -(atual->linha) - 1 + atual->tamTab[1]) {
                printf("\n-------------------------------------\nJogador %c e o vencedor!\n", atual->x.nome);
                printf("Jogada vencedora na posicao: [%d][%d]\n-------------------------------------\n", atual->linha,
                       atual->coluna);
                return 1;
            }
        }
        atual = atual->prev;
    }
    free(atual);
    return 0;
}

void escolheJogada(pJogador x, int nTurnos) {
    if (nTurnos == 0) {
        do {
            printf("\n>>");
            scanf(" %c", &x->jogada);
        } while (!((int) x->jogada == 65));
    } else if (nTurnos > 0) {
        do {
            printf("\n>>");
            scanf(" %c", &x->jogada);
            //printf("\n JOGADA ESCOLHIDA %c",x->jogada);
            //DAR RESET AO QUE FOI GUARDADO PARA VOLTAR A TESTAR...
            //BUG NÃO TESTA O QUE FOI ESCOLHIDO DE NOVO
        } while (!((int) x->jogada >= 65 && (int) x->jogada <= 69));
    }
}

void escolheJogadaPC(pJogador x, int nTurnos) {

    if (nTurnos == 0) {
        x->jogada = 'A';
    } else {
        //x->jogada = intUniformRnd(65, 69);
        x->jogada = 'A';

    }
}

pJogada opcaoEscolhidaPC(char **tab, pJogador x, pJogada listaJogadas, int *tamTab, int *escolha) {
    int linha = 0, coluna = 0, v = 0;
    if (x->jogada == 'A') {
        do {
            linha = rand()%tamTab[0];
            printf("VALOR DA LINHA %d\n",linha);
            coluna = rand()%tamTab[1];
            printf("VALOR DA COLUNA %d\n",coluna);
            v = verificaJogada(tab, linha, coluna);
            if (v == 0 || v == 2) printf("\nPosicao ja ocupada!\n");
        } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v==2);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'G');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    }
    /*} else if (x->jogada == 'B') {
        listaJogadas = jogadaB(tab, tamTab, *x, listaJogadas);
    } else if (x->jogada == 'C') {
        listaJogadas = jogadaC(tab, tamTab, *x, listaJogadas);
    } else if (x->jogada == 'D') {
        listaJogadas = jogadaD(tab, tamTab, x, listaJogadas);
    } else if (x->jogada == 'E') {
        listaJogadas = jogadaE(tab, escolha, x, listaJogadas, tamTab);
    }*/
    return listaJogadas;
}

#pragma clang diagnostic pop