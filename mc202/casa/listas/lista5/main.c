/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 06: Listas ligadas

   Nome:
   RA:

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#ifndef bool
typedef enum _bool {
  false, true
} bool;
#endif

/* Lista simplesmente encadeada: cada no guarda um elemento e o
   endereco do proximo no. O ultimo no aponta para NULL. A lista
   inteira e representada pelo endereco do seu primeiro no; a lista
   vazia e o apontador NULL.                                         */

typedef struct no_lista_simples {
  int elem;
  struct no_lista_simples *prox;
} ListaSimples, NoListaSimples;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Cria um no isolado, com prox = NULL */

NoListaSimples *CriaNoSimples(int elem)
{
  NoListaSimples *no;

  no = (NoListaSimples *) malloc(sizeof(NoListaSimples));
  if (no == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  no->elem = elem;
  no->prox = NULL;

  return no;
}

bool ListaVazia(ListaSimples *inicio)
{
  return inicio == NULL;
}

void ImprimeLista(ListaSimples *inicio)
{
  NoListaSimples *p;

  printf("inicio -> ");
  for (p = inicio; p != NULL; p = p->prox)
    printf("[%d|-]-> ", p->elem);
  printf("NULL\n");
}

/* Procura a primeira ocorrencia de elem na lista.

   Devolve true se encontrou, e nesse caso *pos recebe o endereco do
   no encontrado e *ant o endereco do no ANTERIOR a ele (ou NULL, se
   o encontrado for o primeiro da lista). Se nao encontrar, devolve
   false e *pos vira NULL.                                           */

bool BuscaElemento(ListaSimples *inicio, int elem,
                   NoListaSimples **pos, NoListaSimples **ant)
{
  *ant = NULL;
  *pos = inicio;

  while (*pos != NULL && (*pos)->elem != elem) {
    *ant = *pos;
    *pos = (*pos)->prox;
  }

  return *pos != NULL;
}

/* Libera todos os nos e faz o apontador do chamador virar NULL */

void DestroiLista(ListaSimples **inicio)
{
  NoListaSimples *p, *prox;

  p = *inicio;
  while (p != NULL) {
    prox = p->prox;
    free(p);
    p = prox;
  }
  *inicio = NULL;
}

/* ==================================================================
   EXERCICIO 1 - INSERCAO ORDENADA (1,5 pontos)
   ==================================================================

   Insere elem na lista mantendo os elementos em ordem CRESCENTE.
   Elementos repetidos sao permitidos: um elemento igual a outro ja
   existente deve ser inserido DEPOIS dele.

   Repare que a funcao recebe ListaSimples ** (o endereco do
   apontador do chamador), porque a insercao no comeco da lista muda
   o proprio apontador inicio.
*/


void InsereOrdenado(ListaSimples **inicio, int elem)
{
  
  /* TODO 1 */
}

/* ==================================================================
   EXERCICIO 2 - REMOCAO DE UM ELEMENTO (1,5 pontos)
   ==================================================================

   Remove a PRIMEIRA ocorrencia de elem da lista, liberando o no.
   Devolve true se removeu e false se o elemento nao estava la.

   Use a funcao BuscaElemento, que ja devolve o no encontrado e o seu
   antecessor.
*/

bool RemoveElemento(ListaSimples **inicio, int elem)
{
  /* TODO 2 */

  return false;
}

/* ==================================================================
   EXERCICIO 3 - INVERSAO DA LISTA (1,5 pontos)
   ==================================================================

   Inverte a ordem dos nos da lista, SEM alocar nos novos e SEM
   trocar os campos elem de lugar: o que muda sao os apontadores.
*/

void Inverte(ListaSimples **inicio)
{
  /* TODO 3 */
}

/* ==================================================================
   EXERCICIO 4 - INTERCALACAO DE DUAS LISTAS ORDENADAS (1,5 pontos)
   ==================================================================

   Recebe duas listas JA ORDENADAS em ordem crescente e devolve uma
   lista NOVA, tambem ordenada, contendo copias de todos os elementos
   das duas. As listas A e B nao podem ser modificadas.
*/

ListaSimples *Intercala(ListaSimples *A, ListaSimples *B)
{
  /* TODO 4 */

  return NULL;
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
  ListaSimples *A = NULL, *B = NULL, *C = NULL;
  char cmd[8];
  int x;

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'I':                                  /* insere ordenado em A */
      scanf("%d", &x);
      InsereOrdenado(&A, x);
      printf("I %d: ", x);
      ImprimeLista(A);
      break;

    case 'J':                                  /* insere ordenado em B */
      scanf("%d", &x);
      InsereOrdenado(&B, x);
      printf("J %d: ", x);
      ImprimeLista(B);
      break;

    case 'R':                                  /* remove de A */
      scanf("%d", &x);
      printf("R %d %-9s ", x,
             RemoveElemento(&A, x) ? "(ok):" : "(nao ha):");
      ImprimeLista(A);
      break;

    case 'V':                                  /* inverte A */
      Inverte(&A);
      printf("V: ");
      ImprimeLista(A);
      break;

    case 'T':                                  /* C = intercalacao de A e B */
      DestroiLista(&C);
      C = Intercala(A, B);
      printf("T: ");
      ImprimeLista(C);
      break;

    case 'P':
      printf("P (A): ");
      ImprimeLista(A);
      break;

    case 'Q':
      printf("Q (B): ");
      ImprimeLista(B);
      break;

    case 'N':
      printf("N (C): ");
      ImprimeLista(C);
      break;
    }
  }

  DestroiLista(&A);
  DestroiLista(&B);
  DestroiLista(&C);

  return 0;
}