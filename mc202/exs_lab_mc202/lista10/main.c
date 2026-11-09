/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 10: Arvore binaria de busca de altura balanceada (AVL)

   Nome:
   RA:

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

/* Arvore AVL: uma arvore binaria de busca em que, para todo no, as
   alturas das subarvores esquerda e direita diferem no maximo de 1.

   Guardamos a altura de cada no dentro do proprio no, para que o
   fator de balanceamento possa ser calculado em tempo constante.

   Fator de balanceamento de um no:

       fator = altura(subarvore direita) - altura(subarvore esquerda)

   Em uma AVL, todo no tem fator -1, 0 ou +1. E a mesma convencao do
   campo "bal" visto na aula teorica: -1 significa esquerda mais
   alta, 0 significa alturas iguais e +1 significa direita mais
   alta.                                                             */

typedef struct _no_avl {
  int info;
  int altura;                  /* altura da subarvore com raiz neste no */
  struct _no_avl *esq, *dir;
} NoAVL, AVL;

/* Prototipos das funcoes que voce vai implementar. Eles aparecem
   aqui porque algumas funcoes utilitarias abaixo ja as usam.       */

int AlturaNo(AVL *ab);
int Fator(AVL *ab);
AVL *RotacaoDireita(AVL *A);
AVL *RotacaoEsquerda(AVL *A);
AVL *Balanceia(AVL *ab);
void InsereValor(AVL **ab, int valor);

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Cria um no folha: uma folha e uma arvore de altura 1 */

NoAVL *CriaNovoNo(int info)
{
  NoAVL *p;

  p = (NoAVL *) malloc(sizeof(NoAVL));
  if (p == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  p->info   = info;
  p->altura = 1;
  p->esq    = NULL;
  p->dir    = NULL;

  return p;
}

void VisitaInOrdem(AVL *ab)
{
  if (ab != NULL) {
    VisitaInOrdem(ab->esq);
    printf("%d ", ab->info);
    VisitaInOrdem(ab->dir);
  }
}

int NumeroDeNos(AVL *ab)
{
  if (ab == NULL)
    return 0;

  return 1 + NumeroDeNos(ab->esq) + NumeroDeNos(ab->dir);
}

/* Imprime a arvore girada 90 graus, com o fator de balanceamento e a
   altura de cada no. A subarvore direita aparece ACIMA da esquerda. */

void ImprimeAVL(AVL *ab, int h)
{
  int i;

  if (ab != NULL) {
    ImprimeAVL(ab->dir, h + 1);
    for (i = 0; i < h; i++)
      printf("      ");
    printf("%d(f=%+d,h=%d)\n", ab->info, Fator(ab), ab->altura);
    ImprimeAVL(ab->esq, h + 1);
  }
}

void DestroiAVL(AVL **ab)
{
  if (*ab != NULL) {
    DestroiAVL(&(*ab)->esq);
    DestroiAVL(&(*ab)->dir);
    free(*ab);
    *ab = NULL;
  }
}

/* Recalcula o campo altura do no a partir das alturas dos filhos.
   Deve ser chamada sempre que os filhos de um no mudarem. */

void AtualizaAltura(AVL *ab)
{
  if (ab != NULL)
    ab->altura = 1 + MAX(AlturaNo(ab->esq), AlturaNo(ab->dir));
}

/* ==================================================================
   EXERCICIO 1 - ALTURA E FATOR DE BALANCEAMENTO (1,0 ponto)
   ==================================================================
*/

int AlturaNo(AVL *ab)
{
  if (ab==NULL)
    return 0;

  return ab->altura;
}

int Fator(AVL *ab)
{
  if (ab==NULL)
    return 0;

  return AlturaNo(ab->dir) - AlturaNo(ab->esq);
}

/* ==================================================================
   EXERCICIO 2 - ROTACOES SIMPLES (2,0 pontos)
   ==================================================================
*/

AVL *RotacaoDireita(AVL *A)
{
  AVL *aux;
  aux = A->esq->dir;
  A->esq->dir = A;
  A->esq = aux;
  A = A->esq;

  return A;
}

AVL *RotacaoEsquerda(AVL *A)
{
  AVL *aux;
  aux = A->dir->esq;
  A->dir->esq = A;
  A->dir = aux;
  A = A->dir;

  return A;
}

/* ==================================================================
   EXERCICIO 3 - BALANCEAMENTO (1,5 pontos)
   ==================================================================
*/

AVL *Balanceia(AVL *ab)
{
  if (Fator(ab) < -1){
    if (Fator(ab->esq) <= 0){
      ab->esq = RotacaoDireita(ab->esq);
    } else{
      ab->esq = RotacaoEsquerda(ab->esq);
      ab = RotacaoDireita(ab);
    }
  } else if(Fator(ab) > 1);{
    if (Fator(ab->dir) >= 0){
      ab = RotacaoEsquerda(ab);
    } else{
      ab->dir = RotacaoDireita(ab->dir);
      ab = RotacaoEsquerda(ab);
    }
  }

  return ab;
}

/* ==================================================================
   EXERCICIO 4 - INSERCAO COM REBALANCEAMENTO (1,5 pontos)
   ==================================================================
*/

void InsereValor(AVL **ab, int valor)
{
  if (*ab == NULL) {
    *ab = CriaNovoNo(valor);
  }else{
    if (valor < (*ab)->info){
      InsereValor(&(*ab)->esq, valor);
    } else{
      InsereValor(&(*ab)->dir, valor);
    }
  }
  AtualizaAltura(*ab);
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
  AVL *ab = NULL;
  char cmd[8];
  int x;

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'I':                                  /* insere */
      scanf("%d", &x);
      InsereValor(&ab, x);
      printf("I %d: ", x);
      VisitaInOrdem(ab);
      printf("\n");
      break;

    case 'D':                                  /* desenha com fator e altura */
      printf("D:\n");
      ImprimeAVL(ab, 0);
      break;

    case 'A':
      printf("A: %d\n", AlturaNo(ab));
      break;

    case 'F':
      printf("F: %+d\n", Fator(ab));
      break;

    case 'N':
      printf("N: %d\n", NumeroDeNos(ab));
      break;

    case 'S':
      printf("S: ");
      VisitaInOrdem(ab);
      printf("\n");
      break;
    }
  }

  DestroiAVL(&ab);

  return 0;
}
