struct indice{
    char pal[30];
    int linha;
};
typedef struct indice Ind;

struct NO{
    Ind info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
ArvAVL consulta_ArvAVL(ArvAVL *raiz, char *pal);
int maior(int x, int y);
void RotacaoDireita(ArvAVL *A);
void RotacaoEsquerda(ArvAVL *A);
void RotacaoDuplaDireita(ArvAVL *A);
void RotacaoDuplaEsquerda(ArvAVL *A);
int insere_ArvAVL(ArvAVL *raiz, Ind valor);
int iguais_ArvAVL(ArvAVL *r1, ArvAVL *r2);
void imprimeRaiz(ArvAVL *r1);
void imprimeRotacoes();