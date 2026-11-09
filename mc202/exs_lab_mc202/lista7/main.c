/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 08: Operacoes avancadas com listas, pilhas e filas

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

/* ==================================================================
   ESTRUTURAS DE DADOS
   ================================================================== */

/* Lista simplesmente encadeada */

typedef struct no_lista_simples {
  int elem;
  struct no_lista_simples *prox;
} ListaSimples, NoListaSimples;

/* Pilha em vetor */

typedef struct _pilha {
  int  qtde;
  int  tam_max;
  int *val;
} Pilha;

/* Fila circular em vetor */

typedef struct _fila {
  int  ini, fim;
  int  qtde;
  int  tam_max;
  int *val;
} Fila;

/* ==================================================================
   FUNCOES UTILITARIAS PARA LISTAS - JA IMPLEMENTADAS
   ================================================================== */

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

void InsereOrdenado(ListaSimples **inicio, int elem)
{
  NoListaSimples *novo, *p, *ant;

  novo = CriaNoSimples(elem);

  ant = NULL;
  p   = *inicio;
  while (p != NULL && p->elem <= elem) {
    ant = p;
    p   = p->prox;
  }

  novo->prox = p;
  if (ant == NULL)
    *inicio = novo;
  else
    ant->prox = novo;
}

/* ==================================================================
   FUNCOES UTILITARIAS PARA PILHAS - JA IMPLEMENTADAS
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

void ImprimePilha(Pilha *P)
{
  int i;

  printf("base |");
  for (i = 0; i < P->qtde; i++)
    printf(" %d |", P->val[i]);
  printf(" topo\n");
}

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
   FUNCOES UTILITARIAS PARA FILAS - JA IMPLEMENTADAS
   ================================================================== */

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

void ImprimeFila(Fila *F)
{
  int i, j;

  printf("[");
  for (i = 0; i < F->tam_max; i++) {
    j = 0;
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

bool InsereFila(Fila *F, int elem)
{
  if (FilaCheia(F))
    return false;

  F->val[F->fim] = elem;
  F->fim = (F->fim + 1) % F->tam_max;
  F->qtde++;

  return true;
}

bool RemoveFila(Fila *F, int *elem)
{
  if (FilaVazia(F))
    return false;

  *elem = F->val[F->ini];
  F->ini = (F->ini + 1) % F->tam_max;
  F->qtde--;

  return true;
}

/* ==================================================================
   EXERCICIO 1 - DIVIDEPOR (1,5 pontos)
   ==================================================================

   Divide uma lista em duas: uma com elementos <= k (menores) e outra
   com elementos > k (mayores). Os nós nao sao copiados, se reutilizam
   os existentes. A lista original fica vazia.

   Roteiro:
     1. Inicializar menores e mayores a NULL
     2. Recorrer original com um apontador p
     3. Para cada no:
        - Se p->elem <= k, agregar ao final de menores
        - Se p->elem > k, agregar ao final de mayores
     4. Ao final, original deve ser NULL

   Repare que a funcao recebe ListaSimples ** (o endereco do
   apontador do chamador).                                          */

void DividePor(ListaSimples **original, int k,
               ListaSimples **menores, ListaSimples **mayores)
{
    NoListaSimples *menores_prox = NULL;
    *menores = menores_prox;
    NoListaSimples *mayores_prox = NULL;
    *mayores = mayores_prox;
    NoListaSimples *p;
    NoListaSimples *me, *ma;

    while ((*original)!=NULL){
        p = (*original);
        
        if (p->elem<=k) {
            menores_prox = p;
            //me = &(p->prox);
            //p = NULL;
        } else {
            mayores_prox = p;
            //ma = &(p)->prox;
            //p = NULL;
        }
        *original = (*original)->prox;
        //p=p->prox;
    }
    
  /* TODO 1 */
}

/* ==================================================================
   EXERCICIO 2 - ELIMINARPARES (1,5 pontos)
   ==================================================================

   Elimina todos os pares consecutivos e identicos da pilha.

   Requisitos:
     1. Le elementos da pilha P (que chega com dados)
     2. Detecta pares consecutivos identicos
     3. Elimina ambos elementos do par
     4. Devolve true se se realizou ao menos uma eliminacao,
        false se nao houve mudancas

   Roteiro (usando 2 pilhas auxiliares):
     1. Criar uma pilha auxiliar aux
     2. Desempilar todos os elementos de P hacia aux
     3. Criar uma segunda pilha auxiliar resultado
     4. Para cada elemento de aux:
        - Se resultado esta vazia OU topo de resultado != elemento atual:
          Empilar em resultado
        - Se topo de resultado == elemento atual:
          Desempilar de resultado (nao empilar o atual)
     5. Copiar resultado de volta a P
     6. Devolver true se houve mudancas                              */

bool EliminarPares(Pilha *P)
{
  /* TODO 2 */

  return false;
}

/* ==================================================================
   EXERCICIO 3 - INVIERTEPILA (1,5 pontos)
   ==================================================================

   Inverte a orden dos elementos na pilha P sem alocar um vetor maior.

   O elemento que estava na base passa a ser o topo, e viceversa.

   Requisitos:
     1. A pilha P contem elementos em orden base -> topo
     2. Depois da execucao, a orden e invertida: topo -> base
     3. Nao se permite alocar um vetor de maior capacidade
     4. Se podem usar pilhas auxiliares do mesmo tamanho (ou menor)

   Roteiro (usando 2 pilhas auxiliares):
     1. Criar pilha auxiliar A com capacidade tam_max de P
     2. Criar pilha auxiliar B com capacidade tam_max de P
     3. Desempilar todos os elementos de P hacia A
     4. Desempilar todos os elementos de A hacia B
     5. Desempilar todos os elementos de B hacia P
     6. Limpar A e B                                                 */

void InviertePila(Pilha *P)
{
  /* TODO 3 */
}

/* ==================================================================
   EXERCICIO 4 - PROCESAFILA (1,5 pontos)
   ==================================================================

   Processa uma fila de numeros enteiros, filtrando so os elementos
   >= 10 e copiando-os a um vetor de saida.

   Requisitos:
     1. Le sequencialmente todos os elementos da fila F (que e FIFO)
     2. Para cada elemento:
        - Se e >= 10, o copia ao vetor salida
        - Se e < 10, o descarta
     3. A fila F fica vazia ao final
     4. Devolve a quantidade de elementos copiados a salida
     5. Se a quantidade de elementos validos excede tamanio_max,
        devolve -1 (erro)

   Roteiro:
     1. Inicializar contador = 0
     2. Enquanto a fila nao esteja vazia:
        - Desenfilar um elemento em elem
        - Se elem >= 10:
          - Se contador < tamanio_max, agregar a salida[contador]
          - Se contador >= tamanio_max, devolver -1 (overflow)
          - Incrementar contador
     3. Devolver contador (cantidad de elementos en salida)           */

int ProcesaFila(Fila *F, int *salida, int tamanio_max)
{
  /* TODO 4 */

  return 0;
}

/* ==================================================================
   PROGRAMA PRINCIPAL - JA IMPLEMENTADO, NAO PRECISA ALTERAR

   Le comandos da entrada padrao ate o fim do arquivo e imprime o
   resultado de cada um na saida padrao.
   ================================================================== */

int main(void)
{
  ListaSimples *A = NULL, *B = NULL, *C = NULL;
  Pilha *P;
  Fila *Q;
  char cmd[8];
  int x, k, cap, resultado, qtde;
  int salida[100];

  P = CriaPilha(20);
  Q = CriaFila(5);

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'I':                                  /* insere ordenado em A */
      scanf("%d", &x);
      InsereOrdenado(&A, x);
      printf("I %d: ", x);
      ImprimeLista(A);
      break;

    case 'D':                                  /* divide A */
      scanf("%d", &k);
      DividePor(&A, k, &B, &C);
      printf("D %d: \n", k);
      printf("  B: ");
      ImprimeLista(B);
      printf("  C: ");
      ImprimeLista(C);
      break;

    case 'E':                                  /* empilha em P */
      scanf("%d", &x);
      printf("E %d: %s\n", x, Empilha(P, x) ? "ok" : "pilha cheia");
      break;

    case 'L':                                  /* elimina pares de P */
      printf("L: %s\n", EliminarPares(P) ? "true" : "false");
      break;

    case 'V':                                  /* invierte P */
      InviertePila(P);
      printf("V:\n");
      break;

    case 'F':                                  /* insiere en Q */
      scanf("%d", &x);
      InsereFila(Q, x);
      printf("F %d:     ", x);
      ImprimeFila(Q);
      break;

    case 'X':                                  /* recria Q con capacidad */
      scanf("%d", &cap);
      DestroiFila(&Q);
      Q = CriaFila(cap);
      printf("X %d: ", cap);
      ImprimeFila(Q);
      break;

    case 'Z':                                  /* procesa Q */
      scanf("%d", &cap);
      qtde = ProcesaFila(Q, salida, cap);
      if (qtde == -1) {
        printf("Z %d: overflow\n", cap);
      } else {
        printf("Z %d: salida = [", cap);
        for (int i = 0; i < qtde; i++) {
          printf("%d", salida[i]);
          if (i < qtde - 1) printf(", ");
        }
        printf("], cantidad = %d\n", qtde);
      }
      break;

    case 'P':
      printf("P (A): ");
      ImprimeLista(A);
      break;

    case 'N':
      printf("N (B): ");
      ImprimeLista(B);
      break;

    case 'M':
      printf("M (C): ");
      ImprimeLista(C);
      break;

    case 'T':
      printf("T: ");
      ImprimePilha(P);
      break;

    case 'U':
      printf("U: ");
      ImprimeFila(Q);
      break;
    }
  }

  DestroiLista(&A);
  DestroiLista(&B);
  DestroiLista(&C);
  DestroiPilha(&P);
  DestroiFila(&Q);

  return 0;
}
