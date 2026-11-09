/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 03: Cadeias de caracteres, registros e tipos abstratos

   Nome: Pedro Henrique de Araujo Matos
   RA: 306540

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX   64   /* capacidade dos vetores de caracteres */
#define TAM_NOME  32
#define TAM_FONE  16
#define MAX_CONTATOS 10

/* Um registro (struct) agrupa campos de tipos diferentes sob um unico
   nome. Aqui, um contato tem nome e telefone.                       */

typedef struct _contato {
  char nome[TAM_NOME];
  char telefone[TAM_FONE];
} Contato;

/* A agenda e o tipo abstrato de dados (TAD) deste laboratorio: por
   fora, quem usa so chama InsereContatoOrdenado e BuscaContato; por
   dentro, ela e um vetor de registros mantido em ordem alfabetica.  */

typedef struct _agenda {
  Contato contato[MAX_CONTATOS];
  int     n;                      /* numero de contatos guardados */
} Agenda;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

/* Imprime a cadeia entre aspas, seguida do seu comprimento */

void ImprimeCadeia(char *s)
{
  printf("\"%s\" (%d caracteres)\n", s, (int) strlen(s));
}

/* Cria uma agenda vazia */

Agenda *CriaAgenda(void)
{
  Agenda *A;

  A = (Agenda *) malloc(sizeof(Agenda));
  if (A == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  A->n = 0;

  return A;
}

void DestroiAgenda(Agenda **A)
{
  if (A != NULL && *A != NULL) {
    free(*A);
    *A = NULL;
  }
}

void ImprimeAgenda(Agenda *A)
{
  int i;

  for (i = 0; i < A->n; i++)
    printf("  %-10s %s\n", A->contato[i].nome, A->contato[i].telefone);
  if (A->n == 0)
    printf("  (agenda vazia)\n");
}

/* Busca sequencial pelo nome. Devolve o indice do contato na agenda,
   ou -1 se o nome nao estiver la.

   strcmp(a,b) devolve 0 quando as cadeias sao iguais, um valor
   negativo quando a vem antes de b em ordem alfabetica, e positivo
   quando a vem depois.                                              */

int BuscaContato(Agenda *A, char *nome)
{
  int i;

  for (i = 0; i < A->n; i++)
    if (strcmp(A->contato[i].nome, nome) == 0)
      return i;

  return -1;
}

/* ==================================================================
   EXERCICIO 1 - COMPRIMENTO DE UMA CADEIA (1,0 ponto)
   ==================================================================

   Devolve o numero de caracteres de s, sem contar o '\0' final.
   Implemente sem usar strlen.

   Lembre-se: em C uma cadeia de caracteres e um vetor de char
   terminado pelo caractere '\0'. E ele que marca o fim, e nao o
   tamanho do vetor.                                                 */

int MeuStrlen(char *s)
{
    int i = 0;

    while (s[i]!='\0'){
        i++;
    }
    return i;
}

/* ==================================================================
   EXERCICIO 2 - REMOVE SUBCADEIA (1,5 pontos)
   ==================================================================

   Remove tam caracteres de s a partir da posicao inicio, deslocando
   para a esquerda tudo o que vem depois. Devolve 1 se a remocao
   ocorreu e 0 se os parametros forem invalidos, isto e, se
   inicio < 0, ou tam < 0, ou inicio + tam > comprimento de s.

   Exemplo: s = "ESTRUTURA", RemoveSubcadeia(s, 1, 3) remove "STR" e
            deixa s = "EUTURA".

   ATENCAO: o '\0' precisa terminar na posicao certa no final.       */

int RemoveSubcadeia(char *s, int inicio, int tam)
{
  int lens = MeuStrlen(s);
  if (inicio < 0 || tam < 0 || inicio + tam > lens){
    return 0;
  }

  int i = inicio;

  while (s[i + tam]!='\0'){
    s[i] = s[i+tam];
    i++;
  }
  s[i]='\0';

  return 1;
}

/* ==================================================================
   EXERCICIO 3 - INSERE SUBCADEIA (1,5 pontos)
   ==================================================================

   Insere a cadeia t em s, a partir da posicao pos, deslocando para a
   direita tudo o que estava de pos em diante. Devolve 1 se a insercao
   ocorreu e 0 se pos for invalida (pos < 0 ou pos > comprimento de s)
   ou se o resultado nao couber em TAM_MAX posicoes (contando o '\0').

   Exemplo: s = "EUTURA", InsereSubcadeia(s, 3, "XY") deixa
            s = "EUTXYURA".

   ATENCAO: o deslocamento para a direita tem de ser feito DE TRAS
   PARA FRENTE. Se voce copiar da esquerda para a direita, cada
   caractere sobrescreve o proximo antes de ele ser copiado.         */

int InsereSubcadeia(char *s, int pos, char *t)
{
  int lens = MeuStrlen(s);
  int lent = MeuStrlen(t);

  if (pos < 0 || pos > lens || lens + lent + 1 > TAM_MAX){
    return 0;
  }

  int i;
  for (i = lens; i >= pos; i--){
      s[i + lent] = s[i];   // desloca i lent casas para a direita, abrindo espaço para a inserção, incluindo o '\0' original 
  }
  for (i = 0; i < lent; i++){
      s[pos + i] = t[i];    // copia t[i] para o espaco aberto, a partir de pos
  }

  return 1;  
}

/* ==================================================================
   EXERCICIO 4 - INSERE CONTATO EM ORDEM ALFABETICA (2,0 pontos)
   ==================================================================

   Insere um contato na agenda mantendo o vetor A->contato em ordem
   alfabetica crescente de nome. Devolve 1 se inseriu e 0 se a agenda
   estiver cheia (n == MAX_CONTATOS) ou se ja existir um contato com
   esse nome.

   Passos sugeridos:
     1. se a agenda estiver cheia, devolva 0;
     2. se BuscaContato encontrar o nome, devolva 0;
     3. ache a posicao i onde o novo contato deve ficar (a primeira
        posicao cujo nome e MAIOR que o nome novo, segundo strcmp);
     4. desloque os contatos de i em diante uma posicao para a
        direita, DE TRAS PARA FRENTE;
     5. copie nome e telefone para A->contato[i] com strcpy e
        incremente A->n.

   Registros podem ser copiados inteiros com atribuicao:
        A->contato[j] = A->contato[j-1];
   mas os campos nome e telefone, por serem vetores de char, precisam
   de strcpy para receber uma cadeia nova.                           */

int InsereContatoOrdenado(Agenda *A, char *nome, char *telefone)
{
  if (A->n == MAX_CONTATOS){
    return 0; //Agenda cheia, devolve 0
  }

  if (BuscaContato(A, nome) != -1){
    return 0; //Contato ja na agenda, devolve 0
  }

  int i = 0;
  while(i < A->n && strcmp(A->contato[i].nome, nome)<0){
    i++;
  }

  int j;
  for (j = A->n; j > i; j--){
    A->contato[j] = A->contato[j-1];
  } 

  A->n++;

  strcpy(A->contato[i].nome, nome);
  strcpy(A->contato[i].telefone, telefone);

  return 1;
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
  char cmd[8], s[TAM_MAX], t[TAM_MAX], nome[TAM_NOME], tel[TAM_FONE];
  Agenda *A;
  int ini, tam, pos, ok;

  A = CriaAgenda();
  s[0] = '\0';

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'C':                                  /* define a cadeia */
      scanf("%s", s);
      printf("C: \"%s\"\n", s);
      break;

    case 'L':                                  /* comprimento */
      printf("L: %d\n", MeuStrlen(s));
      break;

    case 'R':                                  /* remove subcadeia */
      scanf("%d %d", &ini, &tam);
      ok = RemoveSubcadeia(s, ini, tam);
      printf("R(%d,%d): %s \"%s\"\n", ini, tam, ok ? "ok" : "recusado", s);
      break;

    case 'I':                                  /* insere subcadeia */
      scanf("%d %s", &pos, t);
      ok = InsereSubcadeia(s, pos, t);
      printf("I(%d,%s): %s \"%s\"\n", pos, t, ok ? "ok" : "recusado", s);
      break;

    case 'A':                                  /* insere contato */
      scanf("%s %s", nome, tel);
      ok = InsereContatoOrdenado(A, nome, tel);
      printf("A %s: %s\n", nome, ok ? "ok" : "recusado");
      break;

    case 'B':                                  /* busca contato */
      scanf("%s", nome);
      printf("B %s: %d\n", nome, BuscaContato(A, nome));
      break;

    case 'P':                                  /* imprime a agenda */
      printf("P:\n");
      ImprimeAgenda(A);
      break;
    }
  }

  DestroiAgenda(&A);

  return 0;
}