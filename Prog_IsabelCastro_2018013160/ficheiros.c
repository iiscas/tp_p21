#include "ficheiros.h"

int gravaRelJogadas(pJogada head, char pc, char *fichJog) {
    FILE *f = NULL;
    pJogada aux = head;
    int i = 0;
    f = fopen(fichJog, "wt");
    if (f == NULL) {
        printf("\nOcorreu um erro ao abrir o ficheiro de texto!\n");
        return 0;
    }
    if (aux == NULL) return 0;
    else {
        fprintf(f, "--------------------\nLista de jogadas\n--------------------\n");
        fprintf(f, "- Numero de jogadas: %d\n----------------------------------------\n", nNosLista(head));
        if (pc == 'S')
            fprintf(f, "- Jogou contra o computador!\n----------------------------------------\n");
        while (aux != NULL) {
            fprintf(f, "--%d--\n", i + 1);
            fprintf(f, "Jogador %c\n", aux->x.nome);
            fprintf(f, "Ultima jogada %c\n", aux->x.jogada);
            fprintf(f, "N. pedras usadas %d\n", aux->x.nPedras);
            fprintf(f, "N. de adicoes feitas %d\n", aux->x.nAdicoes);
            fprintf(f, "Posicao da jogada no tabuleiro: %d %d\n", aux->linha, aux->coluna);
            fprintf(f, "Tamanho do tabuleiro na jogada: [%d][%d]\n", aux->tamTab[0], aux->tamTab[1]);
            fprintf(f, "----------------------------------------\n");
            aux = aux->prox;
            i++;
        }
    }
    fclose(f);
    return 1;
}

void preencheFichBinario(pJogada lista, int pc, int numJogadas) {
    FILE *f;
    pJogada aux = lista;
    //pJogada x = NULL;

    if (aux == NULL) {
        puts("ERRO AO ALOCAR MEMORIA!");
        return;
    }

    f = fopen(JOGREC, "wb");
    if (f == NULL) {
        printf("\nERRO AO ABRIR FICHEIRO!");
        return;
    }
    if (aux != NULL) {
        fwrite(&numJogadas, sizeof(int), 1, f);
        fwrite(&pc, sizeof(int), 1, f); //escrever 1 se jogou com pc ou 0 senao
    }
    for (int i = 0; i < numJogadas; i++) {
        fwrite(aux, sizeof(noJogada), 1, f);
        //printf("LISTA A SER GUARDADA--JOG NOME: %c\n",x->x.nome);
        aux = aux->prox;
    }

    free(aux);
    fclose(f);
}

pJogada preencheListaRec(pJogada lista, int *pc, int *numJogadas) {
    FILE *f = NULL;
    pJogada listaN = NULL;
    noJogada x;
    //num jogadas
    //pc
    //estrutura

    // Abrir o ficheiro binário
    f = fopen(JOGREC, "rb");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return lista;
    }

    fread(numJogadas, sizeof(int), 1, f);
    printf("Num de jogadas %d\n", *numJogadas);
    fread(pc, sizeof(int), 1, f);
    printf("PC: %c\n", *pc);

    // Ler os dados do ficheiro
        for (int i = 0; i < *numJogadas; i++) {
            fread(&x, sizeof(noJogada), 1, f);
                listaN= adicionaFimLista(listaN,x.x,x.linha,x.coluna,x.tamTab);
            printJogador(listaN->x);
            listaN=listaN->prox;
        }

    lista=listaN;
    fclose(f);
    free(listaN);

    return lista;
}


