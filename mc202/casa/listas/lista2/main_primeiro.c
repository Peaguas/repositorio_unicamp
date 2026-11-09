/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 02: Vetores, matrizes e alocacao dinamica de memoria

   Nome: Pedro Henrique de Araujo Matos
   RA: 306540

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_INICIAL 2

/* Vetor que cresce sozinho conforme elementos sao inseridos.

   Invariante: 0 <= n <= capacidade, e as posicoes v[0..n-1] contem os
   elementos validos. As posicoes v[n..capacidade-1] estao alocadas
   mas ainda nao sao usadas.                                         */

typedef struct _vetor_dinamico {
  int *v;           /* vetor de elementos alocado dinamicamente */
  int  n;           /* numero de elementos armazenados */
  int  capacidade;  /* numero de posicoes alocadas */
} VetorDinamico;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Cria um vetor dinamico vazio com a capacidade dada */

VetorDinamico *CriaVetorDinamico(int capacidade)
{
  VetorDinamico *V;

  V = (VetorDinamico *) malloc(sizeof(VetorDinamico));
  if (V == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }

  V->v = (int *) malloc(capacidade * sizeof(int));
  if (V->v == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }

  V->n = 0;
  V->capacidade = capacidade;

  return V;
}

/* Libera o vetor e a estrutura, e faz o apontador do chamador virar NULL */

void DestroiVetorDinamico(VetorDinamico **V)
{
  if (V != NULL && *V != NULL) {
    free((*V)->v);
    free(*V);
    *V = NULL;
  }
}

/* Imprime os elementos usados e, entre parenteses, n e a capacidade */

void ImprimeVetorDinamico(VetorDinamico *V)
{
  int i;

  printf("[");
  for (i = 0; i < V->n; i++) {
    printf("%d", V->v[i]);
    if (i < V->n - 1)
      printf(" ");
  }
  printf("] (n=%d cap=%d)\n", V->n, V->capacidade);
}

/* Aloca uma matriz n x n de inteiros como um vetor de apontadores
   para linhas, e a preenche com os valores de origem (linha a linha) */

int **CriaMatriz(int n, int *origem)
{
  int **M, i, j;

  M = (int **) malloc(n * sizeof(int *));
  if (M == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }

  for (i = 0; i < n; i++) {
    M[i] = (int *) malloc(n * sizeof(int));
    if (M[i] == NULL) {
      fprintf(stderr, "Erro: memoria insuficiente.\n");
      exit(1);
    }
    for (j = 0; j < n; j++)
      M[i][j] = origem[i * n + j];
  }

  return M;
}

/* Libera as n linhas e depois o vetor de apontadores */

void DestroiMatriz(int ***M, int n)
{
  int i;

  if (M != NULL && *M != NULL) {
    for (i = 0; i < n; i++)
      free((*M)[i]);
    free(*M);
    *M = NULL;
  }
}

void ImprimeMatriz(int **M, int n)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%4d", M[i][j]);
    printf("\n");
  }
}

/* ==================================================================
   EXERCICIO 1 - REDIMENSIONA (1,5 pontos)
   ==================================================================

   Muda a capacidade do vetor V para nova_cap, preservando os
   elementos ja armazenados. Suponha nova_cap >= V->n.

   Use realloc, que copia o conteudo antigo para a nova area quando
   precisa mudar o vetor de lugar. O padrao seguro e guardar o
   resultado em uma variavel auxiliar antes de atribuir a V->v:

       int *novo = (int *) realloc(V->v, nova_cap * sizeof(int));
       if (novo == NULL) { ... erro ... }
       V->v = novo;

   Se voce fizer V->v = realloc(V->v, ...) diretamente e o realloc
   falhar, o apontador antigo e perdido e a memoria vaza.

   Nao esqueca de atualizar V->capacidade.                           */

void Redimensiona(VetorDinamico *V, int nova_cap)
{
    
    int *novo = (int *) realloc(V->v, nova_cap * sizeof(int));
    if (novo == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        exit(1);}

    V->v = novo;
    V->capacidade = nova_cap;
  /* TODO 1 */
}

/* ==================================================================
   EXERCICIO 2 - INSERE NO FIM (1,5 pontos)
   ==================================================================

   Insere elem logo depois do ultimo elemento do vetor.

   Se o vetor estiver cheio (n == capacidade), DOBRE a capacidade
   antes de inserir, usando a funcao Redimensiona.                   */

void InsereFim(VetorDinamico *V, int elem)
{
    if (V->n >= V->capacidade) {
        Redimensiona(V, V->capacidade*2);
    }
    V->v[V->n] = elem; /*insere elem na posicao n do vetor v*/
    V->n++; /*aumenta o contador de elementos*/
    
  /* TODO 2 */
}

/* ==================================================================
   EXERCICIO 3 - REMOVE POR INDICE (1,5 pontos)
   ==================================================================

   Remove o elemento da posicao i, devolvendo o valor removido em
   *elem. Devolve 1 se a remocao ocorreu e 0 se o indice for
   invalido (i < 0 ou i >= n), caso em que *elem nao e alterado.

   Os elementos seguintes devem ser deslocados uma posicao para a
   esquerda, de modo que o vetor continue sem buracos.

   Para nao desperdicar memoria, se depois da remocao sobrar menos de
   um quarto da capacidade em uso (n <= capacidade/4) e a capacidade
   ainda for maior que CAPACIDADE_INICIAL, reduza a capacidade PELA
   METADE usando Redimensiona.                                       */

int RemoveIndice(VetorDinamico *V, int i, int *elem)
{
    int j;

    if (i<0 || i>=V->n) {
        return 0; /*lida com indices invalidos*/
    }

    *elem = V->v[i]; /*recebe item a ser retirado*/
    for (j=0; j < V->n; j++) {
        V->v[j] = V->v[j+1]; /*passa lista pra esquerda*/
    }
    V->n--; /*diminui contagem*/

    if (V->n <= V->capacidade/4) {
        Redimensiona(V, V->capacidade/2); /*redimensiona*/
    }




  /* TODO 3 */

    return 1;
}

/* ==================================================================
   EXERCICIO 4 - SOMA DAS DIAGONAIS (1,5 pontos)
   ==================================================================

   Percorre a matriz quadrada M de ordem n e devolve, por referencia,
   a soma da diagonal principal em *principal e a soma da diagonal
   secundaria em *secundaria.

   Na diagonal principal estao os elementos M[i][j] com i == j.
   Na diagonal secundaria estao os elementos com i + j == n - 1.

   Faca isso com UM UNICO laco de i = 0 ate n-1: nao e preciso
   percorrer a matriz inteira.                                       */

void SomaDiagonais(int **M, int n, int *principal, int *secundaria)
{
    int i;

    for (i=0; i<n; i++) {
        *principal += M[i][i]; /*indices iguais*/
        *secundaria += M[i][n-i-1]; /*indices opostos*/
    }
  /* TODO 4 */
}

/* ==================================================================
   PROGRAMA PRINCIPAL - JA IMPLEMENTADO, NAO PRECISA ALTERAR
   ================================================================== */

int main(void)
{
  VetorDinamico *V;
  int entrada[6] = {5, 8, 13, 2, 9, 21};
  int mat[16] = { 3,  1,  4,  1,
                  5,  9,  2,  6,
                  5,  3,  5,  8,
                  9,  7,  9,  3};
  int **M;
  int i, elem, principal, secundaria;

  printf("=== Exercicio 2: InsereFim ===\n");
  V = CriaVetorDinamico(CAPACIDADE_INICIAL);
  printf("inicial:    ");
  ImprimeVetorDinamico(V);
  for (i = 0; i < 6; i++) {
    InsereFim(V, entrada[i]);
    printf("insere %2d:  ", entrada[i]);
    ImprimeVetorDinamico(V);
  }

  printf("\n=== Exercicio 3: RemoveIndice ===\n");
  for (i = 0; i < 4; i++) {
    if (RemoveIndice(V, 0, &elem))
      printf("removeu %2d: ", elem);
    else
      printf("indice invalido: ");
    ImprimeVetorDinamico(V);
  }
  printf("remove indice 99: %s\n",
         RemoveIndice(V, 99, &elem) ? "removeu (ERRADO)" : "recusou (ok)");

  DestroiVetorDinamico(&V);

  printf("\n=== Exercicio 4: SomaDiagonais ===\n");
  M = CriaMatriz(4, mat);
  ImprimeMatriz(M, 4);
  SomaDiagonais(M, 4, &principal, &secundaria);
  printf("diagonal principal  = %d\n", principal);
  printf("diagonal secundaria = %d\n", secundaria);
  DestroiMatriz(&M, 4);

  return 0;
}