#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "arvore.h"

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc (sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

ArvAVL consulta_ArvAVL(ArvAVL *raiz, char *pal){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcoll(pal, atual->info.pal)==0){
            return atual;
        }
        if(strcoll(pal, atual->info.pal)>0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoDireita(ArvAVL *A){
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoEsquerda(ArvAVL *A){
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoDuplaDireita(ArvAVL *A){
    RotacaoEsquerda(&(*A)->esq);
    RotacaoDireita(A);
}

void RotacaoDuplaEsquerda(ArvAVL *A){
    RotacaoDireita(&(*A)->dir);
    RotacaoEsquerda(A);
}

int insere_ArvAVL(ArvAVL *raiz, Ind valor){
    int r;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    
    valor.linha = atual->info.linha;
    
    if(strcoll(valor.pal, atual->info.pal)<0){
        r = insere_ArvAVL(&(atual->esq), valor);
        if(r == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcoll(valor.pal, (*raiz)->esq->info.pal)<0){
                    RotacaoDireita(raiz);
                }
                else{
                    RotacaoDuplaDireita(raiz);
                }
            }
        }
    }else{
        if(strcoll(valor.pal, atual->info.pal)>0){
            r = insere_ArvAVL(&(atual->dir), valor); 
            if(r == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcoll((*raiz)->dir->info.pal,valor.pal) < 0){
                        RotacaoEsquerda(raiz);
                    }
                    else{
                        RotacaoDuplaEsquerda(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return r;
}

int iguais_ArvAVL(ArvAVL *r1, ArvAVL *r2){
    struct NO *elem;
    if (*r1 == NULL && *r2 == NULL)
        return 1;
    else{
        if (*r1 == NULL || *r2 == NULL) 
            return 0;       
        if (strcoll((*r1)->info.pal, (*r2)->info.pal) == 0){
            return ((iguais_ArvAVL(&(*r1)->esq,&(*r2)->esq)) &&
            (iguais_ArvAVL(&(*r1)->dir,&(*r2)->dir)));
        }
        else return 0;
    }
}

void imprimeRaiz(ArvAVL *r1){
    printf("%s (altura: %d)",(*r1)->info.pal, (*r1)->altura);
}
