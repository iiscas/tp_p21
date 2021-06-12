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
    int tamTabuleiro[2], escolha = 0, stop = 0;
    char pc, fichJog[25], recJogo;
    char **tabuleiro = NULL;
    pJogada listaJogadas;

    pJogada aux = NULL;
    jogador jogadores[2] = {
            {'A', '-', 0, 0},
            {'B', '-', 0, 0}};

    do {
        listaJogadas = NULL;
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
                    //printListaJogadas(listaJogadas);
                    if (pc == 'S')
                        puts("Vai jogar contra o pc!\n");
                    else
                        puts("\nPrecisa de outro jogador!");

                    printf("\n----------------------\nJogo vai recomeçar!\n----------------------\n");
                    printf("\n-------------------------\nA recriar o tabuleiro...\n-------------------------\n");
                    sleep(1);
                    //JOGO E TABULEIRO A SEREM PREPARADOS
                    tabuleiro = recuperaTabuleiro(listaJogadas, tamTabuleiro);
                    listaJogadas = iniciaJogo(tabuleiro, jogadores, listaJogadas, tamTabuleiro, pc, &stop);

                    //SAIU DO JOGO
                    //SE FOI INTERROMPIDO ENTAO GRAVAR JOGO
                    if (stop == 1 && listaJogadas != NULL) {
                        preencheFichBinario(listaJogadas, (int) pc, nNosLista(listaJogadas));
                    }
                    //SENAO FOI PQ ALGUÉM GANHOU E NAO É PARA GRAVAR!
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
                    //escolha = 3;
                    break;
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
                    //SE FOI INTERROMPIDO ENTAO GRAVAR JOGO
                    if (stop == 1 && listaJogadas != NULL)
                        preencheFichBinario(listaJogadas, (int) pc, nNosLista(listaJogadas));
                    //SENAO FOI PQ ALGUÉM GANHOU E NAO É PARA GRAVAR NO BINARIO!
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
                    //escolha = 3;
                    if (listaJogadas != NULL)
                        preencheFichBinario(listaJogadas, (int) pc, nNosLista(listaJogadas));
                    break;
                }
            case 2:;
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
                    printf("-----------------\nJogada inválida!\n-----------------\n\n");
                break;


        }
    } while (escolha != 3);

    free(tabuleiro[0]);
    free(tabuleiro);
    free(listaJogadas);
    return 0;
}

