//ISABEL RAMOS CASTRO
//2018013160
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include "tabuleiro.h"
#include "historico.h"
#include "ficheiros.h"

#define MENU "menu.txt"
#define REGRAS "regras.txt"

void menuPrincipal() {

    FILE *f;
    char c;
    if ((f = fopen("menu.txt", "r")) == NULL) {
        printf("ERRO AO ABRIR FICHEIRO %s.\n", MENU);
        return;
    }
    while ((c = fgetc(f)) != EOF)
        putchar(c);
    fclose(f);
}

int main() {
    initRandom();
    int tamTabuleiro[2], escolha = 0, stop;
    char pc, fichJog[25], recJogo;
    pJogada listaJogadas; jogador jogadores[2];
    do {
        stop=0;
        char **tabuleiro = NULL;
        listaJogadas = NULL;
        initJogadores(jogadores);
        menuPrincipal();
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                if (access(JOGREC, F_OK) == 0) {
                    printf("Existe um jogo para recuperar!\n");
                    do {
                        printf("------------------------------------"
                               "\nPretende recuperar o jogo?\nSim(S) / Nao(N)\n"
                               "------------------------------------\n>> ");
                        scanf(" %c", &recJogo);
                    } while (recJogo != 'N' && recJogo != 'S');
                }
                if (recJogo == 'S') {
                    int total = 0;
                    listaJogadas = preencheListaRec(listaJogadas, (int *) &pc, &total);
                    atualizaJogadores(jogadores,listaJogadas);

                    if (pc == 'S') puts("Vai jogar contra o pc!\n");
                    else puts("\nPrecisa de outro jogador!");

                    printf("\n----------------------\nJogo vai recomeçar!\n----------------------\n");
                    printf("\n-------------------------\nA recriar o tabuleiro...\n-------------------------\n");
                    sleep(1);
                    //JOGO E TABULEIRO A SEREM PREPARADOS COM DADOS ANTERIORES
                    tabuleiro = recuperaTabuleiro(listaJogadas, tamTabuleiro);
                    listaJogadas = iniciaJogo(tabuleiro, jogadores, listaJogadas, tamTabuleiro, pc, &stop);
                    //SE JOGO FOI INTERROMPIDO ENTAO GRAVAR JOGO //SENAO FOI PQ ALGUÉM GANHOU E NAO É PARA GRAVAR!
                    if (stop == 1) preencheFichBinario(listaJogadas, (int) pc, nNosLista(listaJogadas));

                    //GRAVAR RELATORIO DO JOGO
                    sleep(1);
                    do {
                        printf("-----------------------------------------------------------\n"
                               "Indique o nome do ficheiro(xxx.txt) para gravar as jogadas\n"
                               "-----------------------------------------------------------\n>> ");
                        fscanf(stdin, "%s", fichJog);
                    } while (!strstr(fichJog, ".txt"));

                    if (gravaRelJogadas(listaJogadas, pc, fichJog))
                        puts("\n--------------------\nRelatorio guardado!\n--------------------");
                    printListaJogadas(listaJogadas); //IMPRIME LISTA DE JOGADAS ANTES DE LIBERTAR MEMORIA
                    freeTabuleiro(tabuleiro, tamTabuleiro[0]);
                    freeListaJogadas(listaJogadas);
                //CASO NAO QUEIRA RECUPERAR O JOGO ANTERIOR
                } else {
                    do {
                        printf("------------------------------------\n"
                               "Pretende jogar contra o computador?\nSim(S) / Nao(N)\n"
                               "------------------------------------\n>> ");
                        scanf(" %c", &pc);
                    } while (pc != 'N' && pc != 'S');

                    printf("\n----------------------\nJogo vai começar!\n----------------------\n");
                    printf("\n----------------------\nA criar tabuleiro...\n----------------------\n");
                    sleep(1);
                    tabuleiro = inicializaTabuleiro(&tamTabuleiro[0], &tamTabuleiro[1]);
                    listaJogadas = iniciaJogo(tabuleiro, jogadores, listaJogadas, tamTabuleiro, pc, &stop);
                    //SAIU DO JOGO
                    //SE FOI INTERROMPIDO ENTAO GRAVAR JOGO //SENAO FOI PQ ALGUÉM GANHOU E NAO É PARA GRAVAR NO BINARIO!
                    if (stop == 1 ) preencheFichBinario(listaJogadas, (int) pc, nNosLista(listaJogadas));
                    //GRAVAR RELATORIO DO JOGO
                    sleep(1);
                    do {
                        printf("-----------------------------------------------------------"
                               "\nIndique o nome do ficheiro(xxx.txt) para gravar as jogadas\n"
                               "-----------------------------------------------------------\n>> ");
                        fscanf(stdin, "%s", fichJog);
                    } while (!strstr(fichJog, ".txt"));

                    if (gravaRelJogadas(listaJogadas, pc, fichJog))
                        puts("\n--------------------\nRelatorio guardado!\n--------------------");
                    printListaJogadas(listaJogadas);
                    freeTabuleiro(tabuleiro, tamTabuleiro[0]);
                    freeListaJogadas(listaJogadas);
                }
            break;
            //////////////////////////////////////////////////////////////////////////////////////////////
            case 2:; //IMPRIME AS REGRAS DO JOGO
                printf("\n");
                FILE *f;
                char c;
                if ((f = fopen("regras.txt", "r")) == NULL) {
                    printf("ERRO AO ABRIR FICHEIRO %s.\n", REGRAS);
                    return 0;
                }
                while ((c = fgetc(f)) != EOF)
                    putchar(c);
                fclose(f);
                printf("\n\n");
                sleep(1);
                break;
            default:
                if (escolha != 3)
                    printf("-----------------\nOpcao inválida!\n-----------------\n\n");
                break;
        }
    } while (escolha != 3);
    printf("\n--------------------------------------------------------\n"
           "\t\t\t\t\tAdeus...."
           "\n--------------------------------------------------------");
    return 0;
}

