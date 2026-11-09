/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 01: Variaveis, apontadores, funcoes, desvio e repeticao

   Nome: Pedro Henrique de Araujo Matos
   RA: 306540

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define MAX_BITS 33   /* 32 bits + o '\0' final */

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

/* ==================================================================
   EXERCICIO 1 - MINIMO E MAXIMO (1,5 pontos)
   ==================================================================

   Percorre os n primeiros elementos de v e devolve, POR REFERENCIA,
   o menor valor em *min e o maior valor em *max.

   Esta e a forma padrao em C de uma funcao "devolver" mais de um
   valor: o chamador passa o endereco das suas variaveis e a funcao
   escreve nelas.

   Exemplo: para v = [4 9 1 7], *min deve virar 1 e *max deve virar 9.
   Suponha n >= 1.                                                   */

void MinMax(int* v, int n, int* min, int* max)
{
    *min  = *max = v[0];
    for (int i=0; i<n; i++){
        if (v[i] > *max){
            *max = v[i];
        } else if(v[i] < *min){
            *min = v[i];
        }
    }
  /* TODO 1: comece com *min = *max = v[0] e percorra o resto do
     vetor atualizando *min e *max. Lembre-se de usar * para
     escrever no valor apontado. */
}

/* ==================================================================
   EXERCICIO 2 - MAXIMO DIVISOR COMUM (1,5 pontos)
   ==================================================================

   Devolve o maximo divisor comum de a e b pelo algoritmo de
   Euclides, usando um laco (sem recursao):

       enquanto b != 0:
           resto <- a % b
           a     <- b
           b     <- resto
       devolve a

   Suponha a >= 0, b >= 0 e a + b > 0.                               */

int MDC(int a, int b)
{
    int resto;

    while (b!=0){
        resto = a%b;
        a=b;
        b=resto;
    }

  /* TODO 2: implemente o laco descrito acima. */

  return a; /* substitua pelo mdc */
}

/* ==================================================================
   EXERCICIO 3 - TESTE DE PRIMALIDADE (1,5 pontos)
   ==================================================================

   Devolve 1 se n for primo e 0 caso contrario.

   Lembre-se: 0 e 1 nao sao primos; 2 e primo. Basta testar divisores
   d de 2 ate a raiz de n, o que pode ser escrito sem usar sqrt como
   "enquanto d * d <= n".                                            */

int EhPrimo(int n)
{
    int d = 2;
    if (n<2) {
        return 0;
    } else {
        while(d*d<=n) {
            if (n%d == 0){
                return 0;
            } d++;
        } return 1;
    }
  /* TODO 3: trate os casos n < 2 e depois teste os divisores. */

  return 0; /* substitua por 1 ou 0 */
}

/* ==================================================================
   EXERCICIO 4 - DECIMAL PARA BINARIO (1,5 pontos)
   ==================================================================

   Escreve em bin a representacao binaria de n, sem zeros a esquerda,
   terminada por '\0'. O vetor bin ja foi alocado pelo chamador com
   MAX_BITS posicoes.

   Exemplos:  n = 0  ->  "0"
              n = 1  ->  "1"
              n = 10 ->  "1010"
              n = 25 ->  "11001"

   DICA: dividir n por 2 sucessivamente produz os bits da direita
   para a esquerda. Uma saida simples e preencher bin de tras para
   frente: descubra antes quantos bits serao necessarios, coloque o
   '\0' na posicao certa e va preenchendo do fim para o comeco.      */

void DecimalParaBinario(int n, char *bin)
{
    
    if (n==0){
        bin[0] = 0 + '0';
        bin[1] = '\0';
        return;
    }
    
    char nib[MAX_BITS];
    int i = 0;
    
    while (n>=1){
        int resto = n%2;
        n = n/2;
        nib[i] = resto + '0';
        i++;
    }

    for (int j = 0; j<i; j++){
        bin[j] = nib[i-j-1];
    }

    bin[i] = '\0';
  /* TODO 4: trate o caso n == 0 separadamente e depois preencha
     bin de tras para frente. */

   /* substitua pela conversao */
}

/* ==================================================================
   PROGRAMA PRINCIPAL - JA IMPLEMENTADO, NAO PRECISA ALTERAR
   ================================================================== */

int main(void)
{
  int v[TAM] = {42, 7, 91, 4, 56, 12, 88, 31, 4, 63};
  int min, max, i;
  int pares[5][2] = {{48, 18}, {17, 5}, {100, 75}, {7, 0}, {270, 192}};
  int primos[8] = {0, 1, 2, 9, 17, 25, 97, 100};
  int decimais[6] = {0, 1, 2, 10, 25, 255};
  char bin[MAX_BITS];

  printf("=== Exercicio 1: MinMax ===\n");
  printf("vetor: ");
  ImprimeVetor(v, TAM);
  MinMax(v, TAM, &min, &max);
  printf("min=%d max=%d\n", min, max);

  printf("\n=== Exercicio 2: MDC ===\n");
  for (i = 0; i < 5; i++)
    printf("mdc(%d,%d) = %d\n", pares[i][0], pares[i][1],
           MDC(pares[i][0], pares[i][1]));

  printf("\n=== Exercicio 3: EhPrimo ===\n");
  for (i = 0; i < 8; i++)
    printf("%d: %s\n", primos[i], EhPrimo(primos[i]) ? "primo" : "nao primo");

  printf("\n=== Exercicio 4: DecimalParaBinario ===\n");
  for (i = 0; i < 6; i++) {
    DecimalParaBinario(decimais[i], bin);
    printf("%3d -> %s\n", decimais[i], bin);
  }

  return 0;
}