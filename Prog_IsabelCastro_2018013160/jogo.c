#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "readability-non-const-parameter"
#pragma ide diagnostic ignored "cert-err34-c"

#include "jogo.h"
#include "tabuleiro.h"
#include "historico.h"
pJogada iniciaJogo(char **tab, jogador x[], pJogada lista, int tamTabuleiro[2], char pc) {
    pJogada listaJogadas = lista;
    int nTurnos = 0, a = 0, escolha = 0;
    int tipoVencedor = 0;
    if (lista != NULL) {
        nTurnos = 1; //caso o jogo seja o recuperado!
    }
    while (1) {
        printTabuleiro(tamTabuleiro, tab);
        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printPedirEstados(listaJogadas, nTurnos, tamTabuleiro);
        printJogadas(nTurnos, x[0]);
        escolheJogada(&x[0], nTurnos, tab, tamTabuleiro);
        //jogada ja escolhida
        if(x[0].jogada=='F')
            break;
        listaJogadas = opcaoEscolhida(tab, &x[0], listaJogadas, tamTabuleiro, &escolha);
        if (escolha == 1) {
            tab = alteraNLinhas(tamTabuleiro, tab);
            escolha = 0;
        } else if (escolha == 2) {
            tab = alteraNColunas(tamTabuleiro, tab);
            escolha = 0;
        }
        printTabuleiro(tamTabuleiro, tab);
        //verifica se ha algum vencedor
        a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
        fflush(stdout);
        if (a > -1) //se tabuleiro encontrou algo completo
            if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
        //fflush(stdout);
        printListaJogadas(listaJogadas);
        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        if (pc == 'N') {
            printf("Jogador %c e a sua vez! ", x[1].nome);
            printPedirEstados(listaJogadas, nTurnos, tamTabuleiro);
            printJogadas(nTurnos, x[1]);
            escolheJogada(&x[1], nTurnos, tab, tamTabuleiro);
            if(x[0].jogada=='F')
                break;
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
            //////////Jogadas PC ///////////////
        } else if (pc == 'S') {

            escolheJogadaPC(&x[1], nTurnos, tab, tamTabuleiro);
            listaJogadas = opcaoEscolhidaPC(tab, &x[1], listaJogadas, tamTabuleiro, &escolha);
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
            if (a > -1)
                if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
            fflush(stdout);
        }
       // printListaJogadas(listaJogadas);

        ///////////////////////////// FIM DO TURNO/JOGADA ///////////////////////////////////
        nTurnos++;
    }
    if(listaJogadas!=NULL)
        printListaJogadas(listaJogadas);
    printf("\n\nVoltando ao menu inicial.....\n\n");
    sleep(1);
    return listaJogadas;
}

int verificaJogada(char **tab, int lJogador, int cJogador) {
    //devolve 0 se não for possivel, 1 se for possivel
    if (tab[lJogador][cJogador] == '-') return 1;
    else if (tab[lJogador][cJogador] == 'G') return 2;
    else if (tab[lJogador][cJogador] == 'Y') return 3;
    else return 0;
}

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v;
    int linha = 0, coluna = 0;

    do {
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        v = verificaJogada(tab, linha, coluna);
        if (v != 1) printf("\nJogada indisponivel!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 2 || v == 3);

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
        if (v != 2) printf("\nJogada indisponivel!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 1 || v == 3);

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
        if (v != 3) printf("\nJogada indisponivel!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 1 || v == 2);

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
        if (v != 1) printf("\nJogada indisponivel!\n");
    } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 2 || v == 3);
    x->nPedras++;
    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
    listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaE(char **tab, int *escolha, pJogador x, pJogada listaJogadas, int tamTab[2]) {
    int linha = 0, temp[2];
    temp[0] = tamTab[0];
    temp[1] = tamTab[1];

    do {
        printf("\nTamanho do tabuleiro [%d][%d]\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", tamTab[0],
               tamTab[1], x->nome);
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
    //printf("linha %d coluna %d\n", tamTab[0], tamTab[1]);
    //check se há match nas linhas
    for (int i = 0; i < tamTab[0]; i++) {
        count = 1;
        for (int j = 0; j < tamTab[1]; j++) {
            if (tab[i][j] == tab[i][j + 1] && tab[i][j] != '-' && tab[i][j] != 'P') {
                //printf("count: %d\n", count);
                count++;
                //printf("count: %d\n", count);
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
                //printf("count1: %d\n", count1);
                count1++;
                //printf("count1: %d\n", count1);
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
                    printf("\n-------------------\nDiagonal principal completa!\n-------------------\n");
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
                        printf("\n-------------------\nDiagonal secundaria completa!\n-------------------\n");
                        *tipo = 3;
                        return diag2;
                    }
                }
            }
        }
    }
    return -1;
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
    jogador vencedor;
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

void escolheJogada(pJogador x, int nTurnos, char **tab, int tam[2]) {
    int flag1, flag, flag2;
    if (nTurnos == 0) {
        do {
            printf("\n>>");
            scanf(" %c", &x->jogada);
        } while (!((int) x->jogada == 65));
    } else if (nTurnos > 0) {
        do {
            flag1 = 1, flag = 1, flag2 = 1;
            printf("\n>>");
            scanf(" %c", &x->jogada);

            if(x->jogada=='F')
                return;
            if (x->jogada != 'D' && x->jogada != 'E') {
                if (countPecas(tab, x->jogada, tam) == 0) {
                    puts("Nao ha pecas da cor anterior");
                    flag2 = 0;
                }
            }
            if (x->nPedras == 1 && x->jogada == 'D') {
                flag1 = 0;
                printf("\n------------------------------\nJa nao pode adicionar pedras!\n------------------------------\n");
            }
            if (x->nAdicoes == 2 && x->jogada == 'E') {
                flag = 0;
                printf("\n-------------------------------------------\nJa nao pode adicionar mais linhas/colunas!\n-------------------------------------------\n");
            }
        } while (!((int) x->jogada >= 65 && (int) x->jogada <= 69) || flag2 == 0 || flag1 == 0 || flag == 0);
    }
}

void escolheJogadaPC(pJogador x, int nTurnos, char **tab, int tam[2]) {
    int flag1, flag, flag2;
    if (nTurnos == 0) {
        x->jogada = 'A';
    } else {
        do {
            flag1 = 1, flag = 1, flag2 = 1;
            x->jogada = intUniformRnd(65, 69);

            if (countPecas(tab, x->jogada, tam) == 0) flag2 = 0;
            if (x->nPedras == 1 && x->jogada == 'D') flag1 = 0;
            if (x->nAdicoes == 2 && x->jogada == 'E') flag = 0;
        } while (flag2 == 0 || flag1 == 0 || flag == 0);
    }
}

pJogada opcaoEscolhidaPC(char **tab, pJogador x, pJogada listaJogadas, int *tamTab, int *escolha) {
    int linha = 0, coluna = 0, v = 0;
    int temp[2];
    temp[0] = tamTab[0];
    temp[1] = tamTab[1];
    if (x->jogada == 'A') {
        do {
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            v = verificaJogada(tab, linha, coluna);
        } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 2 || v == 3);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'G');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    } else if (x->jogada == 'B') {
        do {
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            v = verificaJogada(tab, linha, coluna);
        } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 1 || v == 3);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'Y');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);

    } else if (x->jogada == 'C') {
        do {
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            v = verificaJogada(tab, linha, coluna);
        } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 1 || v == 2);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'R');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    } else if (x->jogada == 'D') {
        do {
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            v = verificaJogada(tab, linha, coluna);
        } while (!(linha <= tamTab[0] && coluna <= tamTab[1]) && v == 0 || v == 2 || v == 3);
        x->nPedras++;
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);

    } else if (x->jogada == 'E') {
        linha = intUniformRnd(1, 2);
        //printf("LINHA OU COLUNA? %d\n", linha);
        *escolha = linha;
        (x->nAdicoes)++;
        if (linha == 1)
            temp[0]++;
        else if (linha == 2)
            temp[1]++;
        listaJogadas = adicionaFimLista(listaJogadas, *x, -1, -1, temp);
    }
    return listaJogadas;
}

int countPecas(char **tab, char jogada, int tam[2]) {
    for (int i = 0; i < tam[0]; i++) {
        for (int j = 0; j < tam[1]; j++) {
            if (tab[i][j] == 'G' && jogada == 'B') return 1;
            else if (tab[i][j] == 'Y' && jogada == 'C') return 1;
            else if (tab[i][j] == '-' && jogada == 'A' || jogada == 'D') return 1;
        }
    }
    return 0;
}

#pragma clang diagnostic pop