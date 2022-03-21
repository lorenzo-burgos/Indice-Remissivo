#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "arvore.h"

#define MAX 500

const char* filename = "teste.txt";

void minusculo(char pal[]){
    for(int i = 0; pal[i]; i++){
        pal[i] = tolower(pal[i]);
    }
}

int main(int argc, char *argv[]){
    
    ArvAVL *avl;
    clock_t tempo;
    struct NO *res;
    Ind t;
    FILE *arq = fopen(filename, "r");
    FILE *arq2 = fopen("gravacao.txt", "wt");
    char *conteudo_linha = malloc(MAX);
    char *palavra = malloc(50);
    int linha = 1;
    int qtd = 0, dist = 0;
    
    setlocale (LC_COLLATE, ""); 
    
    avl = cria_ArvAVL();
    
    while(fscanf(arq, "%[^\n] ", conteudo_linha) != EOF){
        palavra = strtok(conteudo_linha," ,.;!?/");
        while(palavra != NULL){
            minusculo(palavra);
            strcpy(t.pal,palavra);
            t.linha = linha;
            insere_ArvAVL(avl,t);
            fprintf(arq2,"%s %d\n", t.pal, t.linha); 
            palavra = strtok(NULL," ,.;!?/");
            qtd++;
        }
        linha++;
    }
    fclose(arq);
    
    fprintf(arq2,"\nNumero total de palavras: %d",qtd);
    fprintf(arq2,"\nNumero de palavras distintas: %d",dist);
    fprintf(arq2,"\nTempo de construcao do indice usando arvore AVL: %lds\n", tempo);
    
    
    return 0;
}
