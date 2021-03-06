//ISABEL RAMOS CASTRO
//2018013160
#include "jogo.h"
#include "tabuleiro.h"
#include "historico.h"

pJogada iniciaJogo(char **tab, jogador x[], pJogada lista, int tamTabuleiro[2], char pc, int *stop) {
    pJogada listaJogadas = lista;
    int nTurnos = 0, a = 0, escolha = 0,tipoVencedor = 0;
    if (lista != NULL) nTurnos = 1; //caso o jogo seja o recuperado!

    while (1) {
        *stop = 0;
        printf("\n-----------------------------------------------\n");
        printTabuleiro(tamTabuleiro, tab);
        ////////////////////////////// JOGADOR A ////////////////////////////////////////////////////
        printf("Jogador %c e a sua vez! ", x[0].nome);
        printPedirEstados(listaJogadas); //pergunta sobre historico
        printJogadas(nTurnos, x[0]); //mostra jogadas para escolha
        escolheJogada(&x[0], nTurnos, tab, tamTabuleiro);

        if (x[0].jogada == 'F') { //se a jogada for F sai do jogo
            *stop = 1;
            break;
        }
        //faz o tratamento de cada jogada escolhida
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
        if (a > -1) //se tabuleiro encontrou algo completo, entao vai confirmar quem ganhou
            if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;

        ////////////////////////////// JOGADOR B ////////////////////////////////////////////////////
        if (pc == 'N') {
            printf("Jogador %c e a sua vez! ", x[1].nome);
            printPedirEstados(listaJogadas);
            printJogadas(nTurnos, x[1]);
            escolheJogada(&x[1], nTurnos, tab, tamTabuleiro);
            if (x[1].jogada == 'F') {
                *stop = 1;
                break;
            }
           listaJogadas = opcaoEscolhida(tab, &x[1], listaJogadas, tamTabuleiro, &escolha);
            if (escolha == 1) {
                tab = alteraNLinhas(tamTabuleiro, tab);
                escolha = 0;
            } else if (escolha == 2) {
                tab = alteraNColunas(tamTabuleiro, tab);
                escolha = 0;
            }
            printTabuleiro(tamTabuleiro, tab);
            a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
            if (a > -1)
                if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
            fflush(stdout);
        //////////////////////////////////// JOGADOR COMPUTADOR ////////////////////////////////////////////////////
        } else if (pc == 'S') {
            escolheJogadaPC(&x[1], nTurnos, tab, tamTabuleiro); //usa random numeros para converter as letras
            listaJogadas = opcaoEscolhidaPC(tab, &x[1], listaJogadas, tamTabuleiro, &escolha);

            if (escolha == 1) {
                tab = alteraNLinhas(tamTabuleiro, tab);
                escolha = 0;
            } else if (escolha == 2) {
                tab = alteraNColunas(tamTabuleiro, tab);
                escolha = 0;
            }
            printf("\n--------------\nJogada do pc!\n--------------\n");
            printTabuleiro(tamTabuleiro, tab);
            //verifica se h?? algum vencedor
            a = checkTabuleiro(tab, tamTabuleiro, &tipoVencedor);
            if (a > -1)
                if (procuraVencedor(listaJogadas, a, tipoVencedor) == 1) break;
            fflush(stdout);
        }
        ///////////////////////////// FIM DO TURNO/JOGADA ///////////////////////////////////
        nTurnos++;
    }
    printf("\n-------------------------------\nVoltando ao menu inicial.....\n-------------------------------\n");
    sleep(1);
    return listaJogadas;
}

int verificaJogada(char **tab, int lJogador, int cJogador) {
    //verifica o que tem no tabuleiro na posicao escolhida
    if (tab[lJogador][cJogador] == '-') return 1;
    else if (tab[lJogador][cJogador] == 'G') return 2;
    else if (tab[lJogador][cJogador] == 'Y') return 3;
    else if (tab[lJogador][cJogador] == 'R') return 4;
    else if (tab[lJogador][cJogador] == 'P') return 5;
    return 0;
}

pJogada jogadaA(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int v, flag = 0;
    int linha, coluna;
    do {
        flag = 0;
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        if (linha < tamTab[0] && coluna < tamTab[1]) {
            v = verificaJogada(tab, linha, coluna);
            if (v != 1) {
                printf("\nJogada indisponivel!\n");
                flag = 1;
            }
        }
    } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'G');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaB(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int linha = 0, coluna = 0, v, flag;
    do {
        flag = 0;
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        if (linha < tamTab[0] && coluna < tamTab[1]) {
            v = verificaJogada(tab, linha, coluna);
            if (v != 2) {
                printf("\nJogada indisponivel!\n");
                flag = 1;
            }
        }
    } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'Y');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaC(char **tab, int tamTab[2], jogador x, pJogada listaJogadas) {
    int linha = 0, coluna = 0, v, flag;
    do {
        flag = 0;
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x.nome);
        scanf("%d %d", &linha, &coluna);
        if (linha < tamTab[0] && coluna < tamTab[1]) {
            v = verificaJogada(tab, linha, coluna);
            if (v != 3) {
                printf("\nJogada indisponivel!\n");
                flag = 1;
            }
        }
    } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);

    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'R');
    listaJogadas = adicionaFimLista(listaJogadas, x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaD(char **tab, int tamTab[2], pJogador x, pJogada listaJogadas) {
    int linha = 0, coluna = 0, v, flag;
    do {
        flag = 0;
        printf("\nJogador %c escolha a linha e a coluna da sua jogada!\n>>", x->nome);
        scanf("%d %d", &linha, &coluna);
        if (linha < tamTab[0] && coluna < tamTab[1]) {
            v = verificaJogada(tab, linha, coluna);
            if (v != 1) {
                printf("\nJogada indisponivel!\n");
                flag = 1;
            }
        }
    } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);
    x->nPedras++;
    tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
    listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    return listaJogadas;
}

pJogada jogadaE(char **tab, int *escolha, pJogador x, pJogada listaJogadas, int tamTab[2]) {
    int linha = 0, temp[2];
    temp[0] = tamTab[0]; temp[1] = tamTab[1];
    do {
        printf("\nJogador %c pretende adicionar linhas(1) ou colunas(2)\n>>", x->nome);
        scanf("%d", &linha);
    } while (!(linha <= 2));

    *escolha = linha;
    (x->nAdicoes)++;

    if (linha == 1) temp[0]++; //aumenta o tamanho do tabuleiro para que fique guardado na lista
    else if (linha == 2) temp[1]++;
    listaJogadas = adicionaFimLista(listaJogadas, *x, -1, -1, temp);
    printTabuleiro(tamTab, tab);
    return listaJogadas;
}

pJogada adicionaFimLista(pJogada lista, jogador x, int l, int c, int tamTab[2]) {
    noJogada j;
    pJogada novaJogada, aux;
    j.x = x; j.linha = l; j.coluna = c; j.tamTab[1] = tamTab[1]; j.tamTab[0] = tamTab[0];

    //ALOCAR MEMORIA
    novaJogada = malloc(sizeof(noJogada));
    if (novaJogada == NULL) {
        fprintf(stderr, "ERRO A ALOCAR MEMORIA");
        return lista;
    }
    *novaJogada = j;
    //ADICIONAR DADOS
    if (lista == NULL) { //primeiro n??
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
        } else if (tipo == 3) { //procura ultima jogada na diagonal secund??ria
            if (atual->coluna == -(atual->linha) - 1 + atual->tamTab[1]) {
                printf("\n-------------------------------------\nJogador %c e o vencedor!\n", atual->x.nome);
                printf("Jogada vencedora na posicao: [%d][%d]\n-------------------------------------\n", atual->linha,
                       atual->coluna);
                return 1;
            }
        }
        atual = atual->prev;
    }
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

            if (x->jogada == 'F')
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
    int linha = 0, coluna = 0, v = 0, flag;
    int temp[2];
    temp[0] = tamTab[0];
    temp[1] = tamTab[1];
    if (x->jogada == 'A') {
        do {
            flag = 0;
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            if (linha < tamTab[0] && coluna < tamTab[1]) {
                v = verificaJogada(tab, linha, coluna);
                if (v != 1) {
                    flag = 1;
                }
            }
        } while(linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);

        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'G');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    } else if (x->jogada == 'B') {
        do {
            flag = 0;
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            if (linha < tamTab[0] && coluna < tamTab[1]) {
                v = verificaJogada(tab, linha, coluna);
                if (v != 2) {
                    flag = 1;
                }
            }
        } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'Y');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);

    } else if (x->jogada == 'C') {
        do {
            flag = 0;
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            if (linha < tamTab[0] && coluna < tamTab[1]) {
                v = verificaJogada(tab, linha, coluna);
                if (v != 3) {
                    flag = 1;
                }
            }
        } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'R');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);
    } else if (x->jogada == 'D') {
        do {
            flag = 0;
            linha = rand() % tamTab[0];
            coluna = rand() % tamTab[1];
            if (linha < tamTab[0] && coluna < tamTab[1]) {
                v = verificaJogada(tab, linha, coluna);
                if (v != 1) {
                    flag = 1;
                }
            }
        } while (linha >= tamTab[0] || coluna >= tamTab[1] || flag == 1);
        x->nPedras++;
        tab = preencheTabuleiro(tamTab, tab, linha, coluna, 'P');
        listaJogadas = adicionaFimLista(listaJogadas, *x, linha, coluna, tamTab);

    } else if (x->jogada == 'E') {
        linha = intUniformRnd(1, 2);
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

void freeListaJogadas(pJogada lista) {
    pJogada aux = NULL;
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

void initJogadores(jogador *j) {
   j[0].nome='A';
   j[1].nome='B';
    for(int i=0; i<2; i++) {
        j[i].jogada='-';
        j[i].nAdicoes=0;
        j[i].nPedras=0;
    }
}

void atualizaJogadores(jogador *j, pJogada lista) {
    pJogada aux=lista;
    if(aux==NULL)
        return;
    while(aux!=NULL){
        if(aux->prox==NULL){ //encontrou ultimo
            if(aux->x.nome=='A'){ //se ultimo jogador foi o A
                j[0].nome='A'; j[0].jogada=aux->x.jogada;
                j[0].nAdicoes=aux->x.nAdicoes; j[0].nPedras=aux->x.nPedras;
                j[1].nome='B'; j[1].jogada=aux->prev->x.jogada;
                j[1].nAdicoes=aux->prev->x.nAdicoes; j[1].nPedras=aux->prev->x.nPedras;
            }
            else if(aux->x.nome=='B'){
                j[0].nome='A'; j[0].jogada=aux->prev->x.jogada;
                j[0].nAdicoes=aux->prev->x.nAdicoes; j[0].nPedras=aux->prev->x.nPedras;
                j[1].nome='B'; j[1].jogada=aux->prev->x.jogada;
                j[1].nAdicoes=aux->prev->x.nAdicoes; j[1].nPedras=aux->prev->x.nPedras;
            }
        }
        aux=aux->prox;
    }
}
