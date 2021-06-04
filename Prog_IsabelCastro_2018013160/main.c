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

    int COL = 0, LIN = 0;
    int escolha = 0;


    char **tabuleiro=NULL;
    pJogada listaJogadas=NULL;
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

                printf("----------------------\nJogo vai começar!\n----------------------\n");
                printf("\n----------------------\nA criar tabuleiro...\n----------------------\n");
                sleep(1);
                tabuleiro = inicializaTabuleiro(&LIN, &COL);
                iniciaJogo(tabuleiro, jogadores,listaJogadas,&LIN,&COL);

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

