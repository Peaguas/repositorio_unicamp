/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 00: Ambiente, compilacao e depuracao (atividade diagnostica)

   Nome: Pedro Henrique
   RA: 306540

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#define TAM 8

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Imprime os n primeiros elementos do vetor v, entre colchetes */

void ImprimeVetor(int *v, int n)
{
  int i;

  printf("[");
  for (i = 0; i < n; i++) {
    printf("%d", v[i]);
    if (i < n - 1)
      printf(" ");
  }
  printf("]\n");
}

/* Aloca um vetor de n inteiros e o preenche com os valores de origem */

int *CriaVetor(int *origem, int n)
{
  int *v, i;

  v = (int *) malloc(n * sizeof(int));
  if (v == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  for (i = 0; i < n; i++)
    v[i] = origem[i];

  return v;
}

/* Libera o vetor e faz o apontador do chamador virar NULL */

void DestroiVetor(int **v)
{
  if (v != NULL && *v != NULL) {
    free(*v);
    *v = NULL;
  }
}

/* ==================================================================
   EXERCICIO 1 - TROCA (2,0 pontos)
   ==================================================================

   Troca o conteudo das variaveis apontadas por a e por b.

   Exemplo: se x vale 10 e y vale 20, depois de Troca(&x,&y)
            x deve valer 20 e y deve valer 10.

   ATENCAO: a funcao recebe APONTADORES. Para acessar o valor
   apontado por a use *a.                                            */

void Troca(int *a, int *b)
{
    int x, y;
    x = *a;
    y = *b;
    *a = y;
    *b = x;

  /* TODO 1: implemente a troca usando uma variavel auxiliar. */
}

/* ==================================================================
   EXERCICIO 2 - MAIOR ELEMENTO (2,0 pontos)
   ==================================================================

   Devolve o maior valor entre os n primeiros elementos de v.
   Suponha n >= 1.                                                   */

int MaiorElemento(int *v, int n)
{
  int i, max = v[0];
  for (i=1; i<n; i++) {
    if (v[i]>=max){
      max=v[i];
    }
  }
  /* TODO 2: percorra o vetor guardando o maior valor visto ate agora. */
  
  return max; /* substitua pelo maior valor encontrado */
}

/* ==================================================================
   EXERCICIO 3 - INVERTE VETOR (2,0 pontos)
   ==================================================================

   Inverte a ordem dos n primeiros elementos de v, no proprio vetor
   (isto e, sem alocar um segundo vetor).

   Exemplo: [1 2 3 4 5] vira [5 4 3 2 1]

   DICA: use a funcao Troca do Exercicio 1.                          */

void InverteVetor(int *v, int n)
{
  int i;
  for (i=0; i<n/2; i++) {
    int *a, *b;
    a = &v[i];
    b = &v[n-i-1];
    Troca(a, b);
  }
  /* TODO 3: troque v[0] com v[n-1], v[1] com v[n-2], ... */
}

/* ==================================================================
   PROGRAMA PRINCIPAL - JA IMPLEMENTADO, NAO PRECISA ALTERAR
   ================================================================== */

int main(void)
{
  int origem[TAM] = {23, 7, 91, 4, 56, 12, 88, 31};
  int *v, x = 10, y = 20;

  printf("=== Exercicio 1: Troca ===\n");
  printf("antes:  x=%d y=%d\n", x, y);
  Troca(&x, &y);
  printf("depois: x=%d y=%d\n", x, y);

  v = CriaVetor(origem, TAM);

  printf("\n=== Exercicio 2: MaiorElemento ===\n");
  printf("vetor: ");
  ImprimeVetor(v, TAM);
  printf("maior: %d\n", MaiorElemento(v, TAM));

  printf("\n=== Exercicio 3: InverteVetor ===\n");
  InverteVetor(v, TAM);
  printf("invertido: ");
  ImprimeVetor(v, TAM);

  DestroiVetor(&v);

  return 0;
}