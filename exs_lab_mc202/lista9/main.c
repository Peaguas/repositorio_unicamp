/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 09: Arvore binaria de busca

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

/* Arvore binaria de busca: em todo no, os valores MENORES ficam na
   subarvore esquerda e os MAIORES OU IGUAIS ficam na subarvore
   direita. Ou seja, valores repetidos vao sempre para a direita.   */

typedef struct _no_abbusca {
  int info;
  struct _no_abbusca *esq, *dir;
} NoABBusca, ABBusca;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Cria um no folha. Em uma arvore binaria de busca, a insercao
   sempre acontece como folha.                                      */

NoABBusca *CriaNovoNo(int info)
{
  NoABBusca *p;

  p = (NoABBusca *) malloc(sizeof(NoABBusca));
  if (p == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  p->info = info;
  p->esq  = NULL;
  p->dir  = NULL;

  return p;
}

int Altura(ABBusca *ab)
{
  if (ab == NULL)
    return 0;

  return 1 + MAX(Altura(ab->esq), Altura(ab->dir));
}

int NumeroDeNos(ABBusca *ab)
{
  if (ab == NULL)
    return 0;

  return 1 + NumeroDeNos(ab->esq) + NumeroDeNos(ab->dir);
}

/* O percurso em ordem simetrica de uma arvore binaria de busca
   produz os valores em ordem crescente. */

void VisitaInOrdem(ABBusca *ab)
{
  if (ab != NULL) {
    VisitaInOrdem(ab->esq);
    printf("%d ", ab->info);
    VisitaInOrdem(ab->dir);
  }
}

/* Imprime a arvore girada 90 graus: a raiz fica a esquerda e a
   subarvore direita aparece ACIMA da esquerda. Chame com h = 0. */

void ImprimeABBusca(ABBusca *ab, int h)
{
  int i;

  if (ab != NULL) {
    ImprimeABBusca(ab->dir, h + 1);
    for (i = 0; i < h; i++)
      printf("     ");
    printf("%d\n", ab->info);
    ImprimeABBusca(ab->esq, h + 1);
  }
}

void DestroiABBusca(ABBusca **ab)
{
  if (*ab != NULL) {
    DestroiABBusca(&(*ab)->esq);
    DestroiABBusca(&(*ab)->dir);
    free(*ab);
    *ab = NULL;
  }
}

/* ==================================================================
   EXERCICIO 1 - INSERCAO (1,5 pontos)
   ==================================================================

   Insere valor na arvore, mantendo a propriedade de arvore binaria
   de busca. A insercao e sempre de um no folha.

   Como a funcao pode precisar alterar o apontador do chamador (por
   exemplo, ao inserir na arvore vazia), ela recebe ABBusca **.

   Versao recursiva, bem curta:
     - se *ab for NULL, chegamos ao lugar certo: *ab = CriaNovoNo(valor);
     - se valor < (*ab)->info, insira na subarvore ESQUERDA;
     - caso contrario (valor maior OU IGUAL), insira na DIREITA.

   Repare que &(*ab)->esq e o endereco do campo esq do no atual, que
   e exatamente o que a chamada recursiva precisa receber.          */

void InsereValor(ABBusca **ab, int valor)
{
  if (*ab == NULL) {
    *ab = CriaNovoNo(valor);
  }else{
    if (valor < (*ab)->info) {
      InsereValor(&(*ab)->esq, valor);
    } else {
      InsereValor(&(*ab)->dir, valor);
    }
  }
}

/* ==================================================================
   EXERCICIO 2 - BUSCA E MENOR VALOR (1,0 ponto)
   ==================================================================

   BuscaValor devolve 1 se valor estiver na arvore e 0 caso
   contrario. Escreva a versao ITERATIVA: comece na raiz e desca
   para a esquerda ou para a direita comparando com o valor
   procurado, ate encontrar ou chegar em NULL.

   MenorValor devolve o menor valor guardado na arvore ab, que se
   supoe NAO VAZIA. O menor valor esta no no mais a esquerda: basta
   descer por esq enquanto houver filho esquerdo.                   */

int BuscaValor(ABBusca *ab, int valor)
{
    while ((ab!=NULL)){
        if(valor < ab->info){
            ab = ab->esq;
        } else if(valor > ab->info){
            ab = ab->dir;
        } else {
            return 1;
        }   
    }
    return 0;
}

int MenorValor(ABBusca *ab)
{
  while (ab->esq != NULL){
    ab = ab->esq;
  }

  return ab->info;
}

/* ==================================================================
   EXERCICIO 3 - REMOCAO (2,0 pontos)
   ==================================================================

   Remove UMA ocorrencia de valor da arvore. Se o valor nao estiver
   la, a arvore fica inalterada.

   Primeiro localize o no, como na busca. Ao encontra-lo, ha tres
   casos:

     grau 0 (folha) e grau 1 (um so filho):
        *ab passa a apontar para o filho que existe (que e NULL no
        caso da folha) e o no e liberado. Os dois casos podem ser
        escritos juntos:

            se (*ab)->esq == NULL: aux = *ab; *ab = (*ab)->dir; free(aux);
            senao se (*ab)->dir == NULL: aux = *ab; *ab = (*ab)->esq; free(aux);

     grau 2 (dois filhos):
        substitua a informacao do no pelo MENOR VALOR da subarvore
        DIREITA (o menor sucessor) e depois remova esse valor da
        subarvore direita, chamando RemoveValor recursivamente.

   Usamos o menor sucessor, e nao o maior antecessor, porque a
   arvore resolve a igualdade inserindo a direita.                  */

void RemoveValor(ABBusca **ab, int valor)
{
  ABBusca *aux;
    while ((*ab)!=NULL && (*ab)->info!=valor){
        if(valor < (*ab)->info){
            (ab) = &(*ab)->esq;
        } else if(valor > (*ab)->info){
            (ab) = &(*ab)->dir;
        }
    }

  if((*ab) == NULL){
    return;
  }

  if ((*ab)->esq == NULL){
    aux = *ab;
    *ab = (*ab)->dir;
    free(aux);
  } else if((*ab)->dir == NULL){
    aux = *ab;
    *ab = (*ab)->esq;
    free(aux);
  } else {
    (*ab)->info = MenorValor((*ab)->dir);
    RemoveValor(&(*ab)->dir, (*ab)->info);
  }
}

/* ==================================================================
   EXERCICIO 4 - OS K MENORES VALORES (1,5 pontos)
   ==================================================================

   Imprime os *k menores valores da arvore, em ordem crescente,
   seguidos de um espaco cada.

   O percurso em ordem simetrica ja visita os valores em ordem
   crescente. A ideia e fazer esse percurso decrementando *k a cada
   valor impresso e PARANDO assim que *k chegar a zero, para nao
   percorrer a arvore inteira.

   Como o contador precisa ser compartilhado por todas as chamadas
   recursivas, ele e passado por referencia (int *k).

   Estrutura:
     - se ab == NULL ou *k <= 0, nao ha nada a fazer;
     - percorra a subarvore esquerda;
     - se ainda faltam valores (*k > 0), imprima o valor do no e
       decremente *k;
     - percorra a subarvore direita.                                */

void ImprimeKMenores(ABBusca *ab, int *k)
{
    if (ab == NULL || k<0){
        return;
    } 

    ImprimeKMenores(ab->esq, k);
    if (*k>0){
        printf("%d ", ab->info);
        (*k)--;
    }
    ImprimeKMenores(ab->dir, k);

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
  ABBusca *ab = NULL;
  char cmd[8];
  int x, k;

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'I':                                  /* insere */
      scanf("%d", &x);
      InsereValor(&ab, x);
      printf("I %d: ", x);
      VisitaInOrdem(ab);
      printf("\n");
      break;

    case 'R':                                  /* remove */
      scanf("%d", &x);
      RemoveValor(&ab, x);
      printf("R %d: ", x);
      VisitaInOrdem(ab);
      printf("\n");
      break;

    case 'B':                                  /* busca */
      scanf("%d", &x);
      printf("B %d: %s\n", x,
             BuscaValor(ab, x) ? "encontrado" : "nao esta na arvore");
      break;

    case 'A':
      printf("A: %d\n", Altura(ab));
      break;

    case 'N':
      printf("N: %d\n", NumeroDeNos(ab));
      break;

    case 'M':                                  /* menor valor */
      if (ab == NULL)
        printf("M: arvore vazia\n");
      else
        printf("M: %d\n", MenorValor(ab));
      break;

    case 'K':                                  /* k menores valores */
      scanf("%d", &k);
      printf("K %d: ", k);
      ImprimeKMenores(ab, &k);
      printf("\n");
      break;

    case 'S':
      printf("S: ");
      VisitaInOrdem(ab);
      printf("\n");
      break;

    case 'D':
      printf("D:\n");
      ImprimeABBusca(ab, 0);
      break;
    }
  }

  DestroiABBusca(&ab);

  return 0;
}
