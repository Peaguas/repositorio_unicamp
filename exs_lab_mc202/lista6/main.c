/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 07: Pilhas, filas e suas aplicacoes

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

#define TAM_PILHA 20
#define TAM_FILA   5

/* Pilha em vetor: os elementos ocupam val[0..qtde-1] e o topo e
   sempre val[qtde-1].                                               */

typedef struct _pilha {
  int  qtde;      /* numero de elementos na pilha */
  int  tam_max;   /* capacidade */
  int *val;       /* vetor dos valores */
} Pilha;

/* Fila circular em vetor:
     ini  = indice do primeiro elemento;
     fim  = indice da PROXIMA posicao livre;
     qtde = numero de elementos.

   Guardar qtde resolve a ambiguidade de ini == fim, que ocorre tanto
   na fila vazia quanto na fila cheia.                               */

typedef struct _fila {
  int  ini, fim;
  int  qtde;
  int  tam_max;
  int *val;
} Fila;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

Pilha *CriaPilha(int tam_max)
{
  Pilha *P;

  P = (Pilha *) malloc(sizeof(Pilha));
  if (P == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  P->val = (int *) malloc(tam_max * sizeof(int));
  if (P->val == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  P->qtde = 0;
  P->tam_max = tam_max;

  return P;
}

void DestroiPilha(Pilha **P)
{
  if (P != NULL && *P != NULL) {
    free((*P)->val);
    free(*P);
    *P = NULL;
  }
}

bool PilhaVazia(Pilha *P)
{
  return P->qtde == 0;
}

bool PilhaCheia(Pilha *P)
{
  return P->qtde == P->tam_max;
}

/* Imprime da base para o topo */

void ImprimePilha(Pilha *P)
{
  int i;

  printf("base |");
  for (i = 0; i < P->qtde; i++)
    printf(" %d |", P->val[i]);
  printf(" topo\n");
}

Fila *CriaFila(int tam_max)
{
  Fila *F;

  F = (Fila *) malloc(sizeof(Fila));
  if (F == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  F->val = (int *) malloc(tam_max * sizeof(int));
  if (F->val == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  F->ini = F->fim = F->qtde = 0;
  F->tam_max = tam_max;

  return F;
}

void DestroiFila(Fila **F)
{
  if (F != NULL && *F != NULL) {
    free((*F)->val);
    free(*F);
    *F = NULL;
  }
}

bool FilaVazia(Fila *F)
{
  return F->qtde == 0;
}

bool FilaCheia(Fila *F)
{
  return F->qtde == F->tam_max;
}

/* Imprime TODAS as posicoes do vetor, marcando com . as que nao
   contem elementos validos, e mostra ini, fim e qtde. */

void ImprimeFila(Fila *F)
{
  int i, j;

  printf("[");
  for (i = 0; i < F->tam_max; i++) {
    j = 0;                       /* i esta em uso? */
    if (F->qtde > 0) {
      if (F->ini < F->fim)
        j = (i >= F->ini && i < F->fim);
      else
        j = (i >= F->ini || i < F->fim);
    }
    if (j)
      printf("%3d", F->val[i]);
    else
      printf("  .");
  }
  printf(" ]  ini=%d fim=%d qtde=%d\n", F->ini, F->fim, F->qtde);
}

/* Le o proximo item da expressao pos-fixa a partir da posicao *i.

   Devolve 0 quando a expressao acabou, 1 quando leu um numero (que
   fica em *valor) e 2 quando leu um operador (cujo caractere fica em
   *valor). Os itens sao separados por espacos.                      */

int ProximoItem(char *expr, int *i, int *valor)
{
  while (expr[*i] == ' ')
    (*i)++;

  if (expr[*i] == '\0')
    return 0;

  if (expr[*i] >= '0' && expr[*i] <= '9') {
    *valor = 0;
    while (expr[*i] >= '0' && expr[*i] <= '9') {
      *valor = *valor * 10 + (expr[*i] - '0');
      (*i)++;
    }
    return 1;
  }

  *valor = expr[*i];
  (*i)++;

  return 2;
}

/* Diz se o caractere c e um dos delimitadores de abertura */

bool EhAbertura(char c)
{
  return c == '(' || c == '[' || c == '{';
}

/* Devolve o delimitador de abertura correspondente ao fechamento c,
   ou 0 se c nao for um fechamento */

char AberturaCorrespondente(char c)
{
  if (c == ')') return '(';
  if (c == ']') return '[';
  if (c == '}') return '{';

  return 0;
}

/* ==================================================================
    EMPILHA E DESEMPILHA 
   ==================================================================

   Empilha: insere elem no topo. Devolve false se a pilha estiver
   cheia (e nesse caso nao insere), e true caso contrario.

   Desempilha: remove o elemento do topo e o devolve em *elem.
   Devolve false se a pilha estiver vazia, e true caso contrario.

   Lembre-se: o topo e val[qtde-1] e a proxima posicao livre e
   val[qtde].                                                        */

bool Empilha(Pilha *P, int elem)
{
  if (PilhaCheia(P))
    return false;

  P->val[P->qtde] = elem;
  P->qtde++;

  return true;
}

bool Desempilha(Pilha *P, int *elem)
{
  if (PilhaVazia(P))
    return false;

  P->qtde--;
  *elem = P->val[P->qtde];

  return true;
}

/* ==================================================================
   EXERCICIO 1 - FILA CIRCULAR (3,0 pontos)
   ==================================================================

   InsereFila: insere elem no fim da fila. Devolve false se a fila
   estiver cheia.

   RemoveFila: remove o elemento do inicio da fila e o devolve em
   *elem. Devolve false se a fila estiver vazia. */

bool InsereFila(Fila *F, int elem)
{
  if (F->qtde == F->tam_max){
    return false;
  } else {
    F->val[F->fim] = elem;
    F->fim = (F->fim + 1) % F->tam_max;
    F->qtde++;
  }
  return true;
}

bool RemoveFila(Fila *F, int *elem)
{
  if (F->qtde == 0) {
    return false;
  } else {
    *elem = F->val[F->ini];
    F->ini = (F->ini + 1) % F->tam_max;
    F->qtde--;
  }
  return true;
}

/* ==================================================================
   EXERCICIO 2 - AVALIACAO DE EXPRESSAO POS-FIXA (3,0 pontos)
   ==================================================================

   Avalia a expressao pos-fixa expr usando a pilha P, que chega
   vazia. Devolve true e o resultado em *resultado se a expressao for
   valida; devolve false se ela for malformada.

   ATENCAO A ORDEM: em "7 2 -", o 2 sai primeiro da pilha e o 7 sai
   depois, mas a conta e 7 - 2 e nao 2 - 7.                          */

bool AvaliaPosFixa(char *expr, Pilha *P, int *resultado)
{
  int recebe;
  int num1, num2;
  int i = 0, op = 0, res = 0;
  int verifica = ProximoItem(expr, &i, &recebe);

  while (verifica != 0){
    Empilha(P, recebe);
    if (verifica == 2) {
        Desempilha(P, &op);
        Desempilha(P, &num2);
        Desempilha(P, &num1);
        if (op == '+'){
            res = num1 + num2;
            Empilha(P, res);
        } else if(op == '-'){
            res = num1 - num2;
            Empilha(P, res);
        } else if(op == '*'){
            res = num1 * num2;
            Empilha(P, res);
        } else if(op == '/'){
            res = num1 / num2;
            Empilha(P, res);
        }
    }
    verifica = ProximoItem(expr, &i, &recebe);
  }
  
  if (P->qtde>1 || !Desempilha(P, resultado)) {
    return false;
  } return true;

  
}

/* ==================================================================
   DELIMITADORES BALANCEADOS 
   ==================================================================

   Verifica se os delimitadores (), [] e {} de s estao balanceados,
   usando a pilha P, que chega vazia. Os demais caracteres devem ser
   ignorados.

   Algoritmo:
     - abertura: empilhe o caractere;
     - fechamento: desempilhe. Se a pilha estiver vazia, ou se o
       caractere desempilhado nao for a abertura correspondente, a
       expressao esta desbalanceada;
     - no fim, a expressao so esta balanceada se a pilha estiver
       vazia.   */

bool Balanceada(char *s, Pilha *P)
{
  int i, topo;

  for (i = 0; s[i] != '\0'; i++) {
    if (EhAbertura(s[i])) {
      if (!Empilha(P, s[i]))
        return false;
    } else if (AberturaCorrespondente(s[i]) != 0) {
      if (!Desempilha(P, &topo))
        return false;                          /* fechou sem abrir */
      if (topo != AberturaCorrespondente(s[i]))
        return false;                          /* fechou o tipo errado */
    }
  }

  return PilhaVazia(P);
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
  Pilha *P;
  Fila  *F;
  char cmd[8], linha[256];
  int elem, resultado, cap;

  P = CriaPilha(TAM_PILHA);
  F = CriaFila(TAM_FILA);

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'E':                                  /* empilha */
      scanf("%d", &elem);
      printf("E %d: %s\n", elem, Empilha(P, elem) ? "ok" : "pilha cheia");
      break;

    case 'D':                                  /* desempilha */
      if (Desempilha(P, &elem))
        printf("D: %d\n", elem);
      else
        printf("D: pilha vazia\n");
      break;

    case 'P':                                  /* imprime a pilha */
      printf("P: ");
      ImprimePilha(P);
      break;

    case 'M':                                  /* recria a fila com capacidade */
      scanf("%d", &cap);
      DestroiFila(&F);
      F = CriaFila(cap);
      printf("M %d: ", cap);
      ImprimeFila(F);
      break;

    case 'F':                                  /* insere na fila */
      scanf("%d", &elem);
      if (InsereFila(F, elem))
        printf("F %d:     ", elem);
      else
        printf("F %d cheia:", elem);
      ImprimeFila(F);
      break;

    case 'G':                                  /* remove da fila */
      if (RemoveFila(F, &elem))
        printf("G %d:     ", elem);
      else
        printf("G vazia:  ");
      ImprimeFila(F);
      break;

    case 'Q':                                  /* imprime a fila */
      printf("Q:        ");
      ImprimeFila(F);
      break;

    case 'X':                                  /* avalia expressao pos-fixa */
      scanf(" %[^\n]", linha);
      P->qtde = 0;
      if (AvaliaPosFixa(linha, P, &resultado))
        printf("X %s = %d\n", linha, resultado);
      else
        printf("X %s : malformada\n", linha);
      break;

    case 'B':                                  /* delimitadores balanceados */
      scanf("%s", linha);
      P->qtde = 0;
      if (linha[0] == '_')                     /* _ representa a cadeia vazia */
        linha[0] = '\0';
      printf("B %s: %s\n", linha[0] == '\0' ? "(vazia)" : linha,
             Balanceada(linha, P) ? "balanceada" : "desbalanceada");
      break;
    }
  }

  DestroiPilha(&P);
  DestroiFila(&F);

  return 0;
}
