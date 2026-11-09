/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 04: Recursao - ordenacao, busca e backtracking

   Nome:
   RA:

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 64   /* capacidade dos vetores lidos da entrada */

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

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

/* Imprime o trecho v[esq..dir] entre colchetes, com indentacao
   proporcional a profundidade da recursao */

void ImprimeTrecho(int *v, int esq, int dir, int nivel)
{
  int i;

  for (i = 0; i < nivel; i++)
    printf("  ");
  printf("[");
  for (i = esq; i <= dir; i++) {
    printf("%d", v[i]);
    if (i < dir)
      printf(" ");
  }
  printf("]\n");
}

/* Imprime um subconjunto solucao do exercicio 4 */

void ImprimeSolucao(int *sol, int k)
{
  int i;

  printf("  { ");
  for (i = 0; i < k; i++)
    printf("%d ", sol[i]);
  printf("}\n");
}

/* Intercala os trechos JA ORDENADOS v[esq..meio] e v[meio+1..dir],
   deixando v[esq..dir] ordenado. O vetor aux e uma area de trabalho
   do mesmo tamanho de v, fornecida pelo chamador. */

void Intercala(int *v, int esq, int meio, int dir, int *aux)
{
  int i, j, k;

  for (i = esq; i <= dir; i++)      /* copia os dois trechos */
    aux[i] = v[i];

  i = esq;                          /* inicio do trecho esquerdo */
  j = meio + 1;                     /* inicio do trecho direito */

  for (k = esq; k <= dir; k++) {
    if (i > meio)                   /* esgotou o trecho esquerdo */
      v[k] = aux[j++];
    else if (j > dir)               /* esgotou o trecho direito */
      v[k] = aux[i++];
    else if (aux[i] <= aux[j])      /* <= mantem a ordenacao estavel */
      v[k] = aux[i++];
    else
      v[k] = aux[j++];
  }
}

/* ==================================================================
   EXERCICIO 1 - POTENCIA RAPIDA (1,0 ponto)
   ==================================================================

   Devolve base elevado a exp, com exp >= 0, usando recursao e
   APENAS uma chamada recursiva por nivel:

       base^0     = 1
       base^exp   = (base^(exp/2))^2            se exp for par
       base^exp   = base * (base^(exp-1))       se exp for impar

   Guarde o resultado da chamada recursiva em uma variavel antes de
   multiplica-lo por ele mesmo. Escrever

       return Potencia(base, exp/2) * Potencia(base, exp/2);

   funciona, mas faz duas chamadas iguais e joga fora a vantagem do
   metodo: o numero de chamadas passa de log(exp) para exp.          */

int Potencia(int base, int exp)
{
  /* TODO 1 */

  return 0;
}

/* ==================================================================
   EXERCICIO 2 - BUSCA BINARIA RECURSIVA (1,5 pontos)
   ==================================================================

   Procura chave no trecho ORDENADO v[esq..dir] e devolve o indice
   onde ela esta, ou -1 se ela nao estiver la.

   A PRIMEIRA linha da funcao deve ser exatamente:

       printf("  chamada: esq=%d dir=%d\n", esq, dir);

   para que a saida mostre a sequencia de chamadas, do jeito que voce
   desenhou na parte teorica.

   Depois disso:
     - se esq > dir, o trecho esta vazio: devolva -1;
     - calcule meio = (esq + dir) / 2;
     - se v[meio] == chave, devolva meio;
     - se v[meio] < chave, procure em v[meio+1..dir];
     - senao, procure em v[esq..meio-1].                             */

int BuscaBinariaRec(int *v, int esq, int dir, int chave)
{
  /* TODO 2 */

  printf("  chamada: esq=%d dir=%d\n", esq, dir);

  int meio = (esq+dir)/2;

  if (chave == v[meio]){
    return meio;
  } else if (v[meio]<chave){
    BuscaBinariaRec(v, meio+1, dir, chave);
  } else {
    BuscaBinariaRec(v, esq, meio-1, chave);
  }

  return -1;
}

/* ==================================================================
   EXERCICIO 3 - ORDENACAO POR INTERCALACAO (1,5 pontos)
   ==================================================================

   Ordena o trecho v[esq..dir] pelo metodo da intercalacao:

     1. se o trecho tem menos de dois elementos, ja esta ordenado e
        nao ha nada a fazer;
     2. divida o trecho ao meio (meio = (esq + dir) / 2);
     3. ordene recursivamente as duas metades;
     4. intercale as duas metades ordenadas com a funcao Intercala,
        que ja esta pronta.

   Depois do passo 4, e antes de devolver, chame

       ImprimeTrecho(v, esq, dir, nivel);

   para mostrar o trecho recem-intercalado. O parametro nivel serve
   so para a indentacao: passe nivel+1 nas chamadas recursivas.      */

void MergeSort(int *v, int esq, int dir, int *aux, int nivel)
{
  /* TODO 3 */
}

/* ==================================================================
   EXERCICIO 4 - SUBCONJUNTOS COM SOMA DADA (2,0 pontos)
   ==================================================================

   Encontra, por backtracking, todos os subconjuntos de v[i..n-1]
   cuja soma seja igual a alvo. Devolve quantos foram encontrados.

   O vetor sol guarda os elementos ja escolhidos e k diz quantos sao.
   Suponha que todos os elementos de v sao positivos.

   Estrutura da solucao:

     - se alvo == 0, achamos um subconjunto: chame
       ImprimeSolucao(sol, k) e devolva 1;
     - se i == n ou alvo < 0, este ramo nao leva a nada: devolva 0;
     - caso contrario, devolva a soma de dois casos:
         (a) ESCOLHER v[i]: coloque v[i] em sol[k] e chame a funcao
             para i+1, com alvo - v[i] e k+1 elementos escolhidos;
         (b) NAO escolher v[i]: chame a funcao para i+1, com o mesmo
             alvo e o mesmo k.

   Faca o caso (a) antes do (b) para que a ordem da saida seja a
   mesma do gabarito.                                                */

int SomaSubconjuntos(int *v, int n, int i, int alvo, int *sol, int k)
{
  /* TODO 4 */

  return 0;
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
  char cmd[8];
  int v[TAM_MAX], aux[TAM_MAX], sol[TAM_MAX];
  int n = 0, i, base, exp, chave, alvo;

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'P':                                  /* potencia */
      scanf("%d %d", &base, &exp);
      printf("P(%d,%d) = %d\n", base, exp, Potencia(base, exp));
      break;

    case 'S':                                  /* ordena por intercalacao */
      scanf("%d", &n);
      for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
      printf("S entrada:  ");
      ImprimeVetor(v, n);
      printf("intercalacoes:\n");
      MergeSort(v, 0, n - 1, aux, 1);
      printf("S ordenado: ");
      ImprimeVetor(v, n);
      break;

    case 'B':                                  /* busca binaria no vetor atual */
      scanf("%d", &chave);
      printf("B %d:\n", chave);
      printf("  resultado: indice %d\n", BuscaBinariaRec(v, 0, n - 1, chave));
      break;

    case 'K':                                  /* subconjuntos com soma alvo */
      scanf("%d %d", &alvo, &n);
      for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
      printf("K %d em ", alvo);
      ImprimeVetor(v, n);
      printf("  total: %d\n", SomaSubconjuntos(v, n, 0, alvo, sol, 0));
      break;
    }
  }

  return 0;
}
