#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include "tabuleiro.h"
#include "jogo.h"
#include "utils.h"
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
    int tamTabuleiro[2], escolha = 0;
    char pc, fichJog[25], recJogo;
    char **tabuleiro = NULL;
    pJogada listaJogadas = NULL;
    jogador jogadores[2] = {
            {'A', '-', 0, 0},
            {'B', '-', 0, 0}};

    do {
        menuPrincipal();
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                if (access(JOGREC, F_OK) == 0)
                    printf("Existe um jogo para recuperar!\n");
                do {
                    printf("------------------------------------\nPretende recuperar o jogo?\nSim(S) / Nao(N)\n------------------------------------\n>> ");
                    scanf(" %c", &recJogo);
                } while (recJogo != 'N' && recJogo != 'S');

                if (recJogo == 'S') {
                    return 1;

                } else if (recJogo == 'N') {
                    do {

                        printf("------------------------------------\nPretende jogar contra o computador?\nSim(S) / Nao(N)\n------------------------------------\n>> ");
                        scanf(" %c", &pc);
                    } while (pc != 'N' && pc != 'S');
                    printf("\n----------------------\nJogo vai começar!\n----------------------\n");
                    printf("\n----------------------\nA criar tabuleiro...\n----------------------\n");
                    sleep(1);
                    tabuleiro = inicializaTabuleiro(&tamTabuleiro[0], &tamTabuleiro[1]);
                    listaJogadas = iniciaJogo(tabuleiro, jogadores, listaJogadas, tamTabuleiro, pc);
                    //printJogador(jogadores[0]); //A ESTRUTURA ESTA A SER BEM ALTERADA!
                    int total = 0;
                    total= nNosLista(listaJogadas);
                    preencheFichBinario(listaJogadas, (int) pc, total);
                    pJogada aux = NULL;
                    aux=preencheListaRec(aux, (int *) &pc, &total);
                    printListaJogadas(listaJogadas);

                    pJogada a = NULL;

                    //leDadosV2(a, &total);


                    do {
                        printf("-----------------------------------------------------------\nIndique o nome do ficheiro(xxx.txt) para gravar as jogadas\n-----------------------------------------------------------\n>> ");
                        fscanf(stdin, "%s", fichJog);
                    } while (!strstr(fichJog, ".txt"));
                    if (gravaRelJogadas(listaJogadas, pc, fichJog))
                        puts("\nRelatorio guardado!\n");
                    escolha = 3;
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
                //printf("\nPretende jogar de novo?\n");
                //scanf("%d",&escolha);
                //break;
                break;


        }

    } while (escolha != 3);

    free(tabuleiro[0]);
    free(tabuleiro);
    free(listaJogadas);
// libera a memória da matriz

    return 0;
}

