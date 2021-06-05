#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include "tabuleiro.h"
#include "jogo.h"
#include "utils.h"

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
    int tamTabuleiro[2];
    int escolha = 0;
    char pc;

    char **tabuleiro = NULL;
    pJogada listaJogadas = NULL;
    //pJogador listaJogadores=NULL;
    jogador jogadores[2] = {
            {'A', '-', 0, 0},
            {'B', '-', 0, 0}
    };

    do {
        menuPrincipal();
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                do {
                    printf("------------------------------------\nPretende jogar contra o computador?\nSim(S) / Nao(N)\n------------------------------------\n>> ");
                    scanf(" %c", &pc);
                } while (pc!='N' && pc!='S');
                printf("\n----------------------\nJogo vai começar!\n----------------------\n");
                printf("\n----------------------\nA criar tabuleiro...\n----------------------\n");
                sleep(1);
                tabuleiro = inicializaTabuleiro(&tamTabuleiro[0],&tamTabuleiro[1]);
                iniciaJogo(tabuleiro, jogadores, listaJogadas,tamTabuleiro,pc);

                break;

            case 2:;

                FILE *f;
                char c;
                if ((f = fopen("regras.txt", "r")) == NULL) {
                    printf("ERRO AO ABRIR FICHEIRO %s.\n", REGRAS);
                    return 0;
                }
                while ((c = fgetc(f)) != EOF)
                    putchar(c);

                fclose(f);
                printf("\n");
                break;
            default:
                //printf("\nPretende jogar de novo?\n");
                //scanf("%d",&escolha);
                //break;
                break;


        }
    } while (escolha != 3);


// libera a memória da matriz
    free(tabuleiro[0]);
    free(tabuleiro);
    free(listaJogadas);
    return 0;
}

