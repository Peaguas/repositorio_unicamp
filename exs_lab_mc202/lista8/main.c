/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 08: Arvore binaria

   Nome:
   RA:

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#define TAM_FILA 64

/* Arvore binaria de caracteres. A arvore vazia e o apontador NULL. */

typedef struct _arvore_binaria {
  char info;
  struct _arvore_binaria *esq, *dir;
} ArvoreBinaria, NoArvoreBinaria;

/* Fila de apontadores para no, usada no percurso em largura */

typedef struct _fila_nos {
  ArvoreBinaria **val;
  int ini, fim, qtde, tam_max;
} FilaNos;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

NoArvoreBinaria *CriaNo(ArvoreBinaria *esq, ArvoreBinaria *dir, char info)
{
  NoArvoreBinaria *p;

  p = (NoArvoreBinaria *) malloc(sizeof(NoArvoreBinaria));
  if (p == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  p->info = info;
  p->esq  = esq;
  p->dir  = dir;

  return p;
}

/* Constroi a arvore a partir dos percursos em ordem SIMETRICA (sim)
   e em POS-ORDEM (pos), ambos com n nos.

   Ideia: o ultimo no do percurso em pos-ordem e a raiz. Procurando a
   raiz no percurso simetrico, tudo o que esta a esquerda dela forma
   a subarvore esquerda e tudo o que esta a direita forma a
   subarvore direita. Isso da os tamanhos ne e nd das duas
   subarvores, e o processo se repete recursivamente.               */

ArvoreBinaria *ConstroiSimPos(char *sim, char *pos, int n)
{
  ArvoreBinaria *esq, *dir;
  char raiz;
  int ne, nd;

  if (n <= 0)
    return NULL;

  raiz = pos[n - 1];

  ne = 0;
  while (sim[ne] != raiz)      /* ne = quantos nos ficam a esquerda */
    ne++;
  nd = n - ne - 1;

  esq = ConstroiSimPos(sim, pos, ne);
  dir = ConstroiSimPos(sim + ne + 1, pos + ne, nd);

  return CriaNo(esq, dir, raiz);
}

/* Imprime a arvore girada 90 graus no sentido anti-horario: a raiz
   fica a esquerda e a subarvore direita aparece ACIMA da esquerda.
   Chame com h = 0 e altura = Altura(T).                            */

void ImprimeArvoreBinaria(ArvoreBinaria *T, int h, int altura)
{
  int i;

  if (T != NULL) {
    ImprimeArvoreBinaria(T->dir, h + 1, altura);
    for (i = 0; i < h; i++)
      printf("   ");
    printf("%c", T->info);
    for (i = 0; i < altura - h; i++)
      printf("---");
    printf("\n");
    ImprimeArvoreBinaria(T->esq, h + 1, altura);
  }
}

/* Os tres percursos em profundidade. Eles diferem APENAS pela
   posicao da visita ao no em relacao as chamadas recursivas.       */

void VisitaPreOrdem(ArvoreBinaria *T)
{
  if (T != NULL) {
    printf("%c ", T->info);        /* visita antes das subarvores */
    VisitaPreOrdem(T->esq);
    VisitaPreOrdem(T->dir);
  }
}

void VisitaOrdemSimetrica(ArvoreBinaria *T)
{
  if (T != NULL) {
    VisitaOrdemSimetrica(T->esq);
    printf("%c ", T->info);        /* visita entre as subarvores */
    VisitaOrdemSimetrica(T->dir);
  }
}

void VisitaPosOrdem(ArvoreBinaria *T)
{
  if (T != NULL) {
    VisitaPosOrdem(T->esq);
    VisitaPosOrdem(T->dir);
    printf("%c ", T->info);        /* visita depois das subarvores */
  }
}

/* Numero de nos: mesmo esqueleto recursivo, somando 1 por no */

int NumeroDeNos(ArvoreBinaria *T)
{
  if (T == NULL)
    return 0;

  return 1 + NumeroDeNos(T->esq) + NumeroDeNos(T->dir);
}

void DestroiArvore(ArvoreBinaria **T)
{
  if (*T != NULL) {
    DestroiArvore(&(*T)->esq);
    DestroiArvore(&(*T)->dir);
    free(*T);
    *T = NULL;
  }
}

/* Fila de nos (a mesma fila circular do laboratorio 07) */

FilaNos *CriaFilaNos(int tam_max)
{
  FilaNos *F;

  F = (FilaNos *) malloc(sizeof(FilaNos));
  if (F == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  F->val = (ArvoreBinaria **) malloc(tam_max * sizeof(ArvoreBinaria *));
  if (F->val == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  F->ini = F->fim = F->qtde = 0;
  F->tam_max = tam_max;

  return F;
}

void DestroiFilaNos(FilaNos **F)
{
  if (F != NULL && *F != NULL) {
    free((*F)->val);
    free(*F);
    *F = NULL;
  }
}

int FilaNosVazia(FilaNos *F)
{
  return F->qtde == 0;
}

int InsereFilaNos(FilaNos *F, ArvoreBinaria *no)
{
  if (F->qtde == F->tam_max)
    return 0;

  F->val[F->fim] = no;
  F->fim = (F->fim + 1) % F->tam_max;
  F->qtde++;

  return 1;
}

int RemoveFilaNos(FilaNos *F, ArvoreBinaria **no)
{
  if (F->qtde == 0)
    return 0;

  *no = F->val[F->ini];
  F->ini = (F->ini + 1) % F->tam_max;
  F->qtde--;

  return 1;
}

/* ==================================================================
   EXERCICIO 1 - ALTURA (1,5 pontos)
   ==================================================================

   Devolve a altura da arvore T, definida como o numero de nos do
   caminho mais longo da raiz ate uma folha.

   Por essa definicao, a arvore VAZIA tem altura 0 e uma arvore com
   um unico no tem altura 1.

   A recursao segue o mesmo esqueleto de NumeroDeNos:
     - a altura da arvore vazia e 0;
     - a altura de uma arvore nao vazia e 1 mais a MAIOR entre as
       alturas das suas duas subarvores.

   Use a macro MAX(x,y), ja definida no comeco do arquivo.          */

int Altura(ArvoreBinaria *T)
{
  if (T == NULL){
    return 0;
  } 
  
  return 1 + MAX(Altura(T->esq), Altura(T->dir)); 
}

/* ==================================================================
   EXERCICIO 2 - NUMERO DE FOLHAS (1,0 ponto)
   ==================================================================

   Devolve quantas folhas a arvore T tem. Uma folha e um no SEM
   nenhum filho, isto e, com esq == NULL e dir == NULL.

   Cuidado com o caso da arvore vazia: ela nao tem folha nenhuma,
   entao a resposta e 0 (e nao 1).                                  */

int NumeroDeFolhas(ArvoreBinaria *T)
{
  if (T == NULL) {
    return 0;
  }

  if ((T->esq == NULL) && (T->dir == NULL)){
    return 1;
  }

  return NumeroDeFolhas(T->esq) + NumeroDeFolhas(T->dir);

}

/* ==================================================================
   EXERCICIO 3 - ESPELHAMENTO (1,5 pontos)
   ==================================================================

   Transforma a arvore na sua imagem espelhada, trocando a subarvore
   esquerda pela direita em TODOS os nos.

   Faca a troca na propria arvore, sem criar nos novos: basta trocar
   os apontadores esq e dir de cada no e chamar a funcao
   recursivamente para as duas subarvores.                          */

void Espelha(ArvoreBinaria *T)
{
    NoArvoreBinaria *aux;

    if (T != NULL){
        aux = T->esq; T->esq = T->dir; T->dir = aux;
        if (T->esq != NULL)
            Espelha(T->esq);
        if (T->dir != NULL)
            Espelha(T->dir);
    }  
}

/* ==================================================================
   EXERCICIO 4 - PERCURSO EM LARGURA (2,0 pontos)
   ==================================================================

   Imprime os nos da arvore nivel por nivel, da esquerda para a
   direita, no formato "A B C " (um espaco depois de cada no).

   Diferente dos percursos em profundidade, este NAO e naturalmente
   recursivo: ele usa uma fila.

       se a arvore for vazia, nao ha nada a fazer;
       insira a raiz na fila F;
       enquanto a fila nao estiver vazia:
           remova um no da fila;
           imprima a informacao dele;
           insira na fila os filhos que existirem (esquerdo primeiro).

   A fila F chega pronta e vazia. Use InsereFilaNos, RemoveFilaNos e
   FilaNosVazia.                                                     */

void VisitaLargura(ArvoreBinaria *T, FilaNos *F)
{ 
    NoArvoreBinaria *no;

    if (T!=NULL){
        InsereFilaNos(F, T);
        while (!FilaNosVazia(F)){
            RemoveFilaNos(F, &no);
            printf("%c ", no->info);

            if (no->esq != NULL) 
                InsereFilaNos(F, no->esq);
            
            if (no->dir != NULL)
                InsereFilaNos(F, no->dir);
        }
    }
}

/* ==================================================================
   PROGRAMA PRINCIPAL - JA IMPLEMENTADO, NAO PRECISA ALTERAR

   Le comandos da entrada padrao ate o fim do arquivo e imprime o
   resultado de cada um na saida padrao. E este formato que o Susy
   usa para corrigir: cada caso de teste e um arquivo de entrada com
   a saida esperada correspondente.
   ================================================================== */

int main(void)
{
  ArvoreBinaria *T = NULL;
  FilaNos *F;
  char cmd[8], sim[TAM_FILA], pos[TAM_FILA];

  F = CriaFilaNos(TAM_FILA);

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'C':                                  /* constroi dos percursos */
      scanf("%s %s", sim, pos);
      DestroiArvore(&T);
      T = ConstroiSimPos(sim, pos, (int) strlen(sim));
      printf("C %s %s\n", sim, pos);
      break;

    case 'D':                                  /* desenha */
      printf("D:\n");
      ImprimeArvoreBinaria(T, 0, Altura(T));
      break;

    case 'A':
      printf("A: %d\n", Altura(T));
      break;

    case 'N':
      printf("N: %d\n", NumeroDeNos(T));
      break;

    case 'L':
      printf("L: %d\n", NumeroDeFolhas(T));
      break;

    case 'R':
      printf("R: ");
      VisitaPreOrdem(T);
      printf("\n");
      break;

    case 'S':
      printf("S: ");
      VisitaOrdemSimetrica(T);
      printf("\n");
      break;

    case 'O':
      printf("O: ");
      VisitaPosOrdem(T);
      printf("\n");
      break;

    case 'W':
      printf("W: ");
      VisitaLargura(T, F);
      printf("\n");
      break;

    case 'E':                                  /* espelha */
      Espelha(T);
      printf("E: ");
      VisitaOrdemSimetrica(T);
      printf("\n");
      break;
    }
  }

  DestroiArvore(&T);
  DestroiFilaNos(&F);

  return 0;
}
