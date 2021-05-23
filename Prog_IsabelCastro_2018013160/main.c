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
    void initRandom();
    int COL=0, LIN=0;
    int escolha = 0,totalJogadores=0;
    menuPrincipal();
    char **tabuleiro;


     jogador jogadores[2] = {
            {'A', '-', 0,0},
            {'B', '-', 0,0}
    };



    int i, j;



    do {

        scanf("%d", &escolha);
        switch (escolha) {
            case 1:

                printf("----------------------\nJogo vai começar!\n----------------------");
                //printf("\nIntroduza o n. de linhas e colunas do tabuleiro\n>>");
                //scanf("%d %d", &LIN, &COL);

                puts("----------------------\nA criar tabuleiro...\n----------------------");
                sleep(1);
                tabuleiro = inicializaTabuleiro(&LIN,&COL);
                printTabuleiro(LIN, COL, tabuleiro);
                iniciaJogo(tabuleiro,jogadores,&LIN,&COL);
                //printf("Pretende adicionar quantas linhas ao tabuleiro?");
                //int newLinhas=0;
                //scanf("%d", &newLinhas);
                //tabuleiro= alteraNLinhas(newLinhas,LIN,COL,tabuleiro);
                //printTabuleiro(3, COL, tabuleiro); // por a fazer os valores por ponteiros para ser atualizado


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
                printf(">>");
                break;
            default:
                //printf(">>");
                break;


        }
    } while (escolha != 3);








// libera a memória da matriz
    free(tabuleiro[0]);
    free(tabuleiro);
    return 0;
}

