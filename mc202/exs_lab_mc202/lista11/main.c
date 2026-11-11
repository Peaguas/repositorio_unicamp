/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 11: Heap binario

   Nome: Pedro Henrique de Araujo Matos
   RA: 306540

   Compile com:  make
   Execute com:  make teste
   ------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

/* Um heap binario e uma arvore binaria COMPLETA guardada em um
   vetor, sem apontadores: os filhos e o pai de cada posicao sao
   calculados aritmeticamente.                                      */

#define Pai(i)           (((i) - 1) / 2)
#define FilhoEsquerdo(i) (2 * (i) + 1)
#define FilhoDireito(i)  (2 * (i) + 2)

/* Heap de MAXIMO: a informacao de todo no e maior ou igual a dos
   seus filhos. Em particular, o maior elemento fica na raiz, na
   posicao 0 do vetor.                                              */

#define MAX_HEAP 64   /* capacidade do heap deste programa */

typedef struct _heap {
  int *info;              /* informacao e prioridade ao mesmo tempo */
  int  nelems;            /* numero de elementos no heap */
  int  maxsize;           /* tamanho do vetor */
} Heap;

/* ==================================================================
   FUNCOES UTILITARIAS - JA IMPLEMENTADAS, NAO PRECISA ALTERAR
   ================================================================== */

Heap *CriaHeap(int maxsize)
{
  Heap *H;

  H = (Heap *) malloc(sizeof(Heap));
  if (H == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  H->info = (int *) malloc(maxsize * sizeof(int));
  if (H->info == NULL) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(1);
  }
  H->nelems  = 0;
  H->maxsize = maxsize;

  return H;
}

void DestroiHeap(Heap **H)
{
  if (H != NULL && *H != NULL) {
    free((*H)->info);
    free(*H);
    *H = NULL;
  }
}

int HeapVazio(Heap *H)
{
  return H->nelems == 0;
}

int HeapCheio(Heap *H)
{
  return H->nelems == H->maxsize;
}

void Troca(int *x, int *y)
{
  int aux;

  aux = *x;
  *x  = *y;
  *y  = aux;
}

/* Imprime o vetor do heap, posicao por posicao */

void ImprimeVetorHeap(Heap *H)
{
  int i;

  printf("[");
  for (i = 0; i < H->nelems; i++) {
    printf("%d", H->info[i]);
    if (i < H->nelems - 1)
      printf(" ");
  }
  printf("]\n");
}

/* Imprime o heap como arvore girada 90 graus. Chame com indice = 0
   e nivel = 0. */

void ImprimeArvoreHeap(Heap *H, int indice, int nivel)
{
  int i;

  if (indice < H->nelems) {
    ImprimeArvoreHeap(H, FilhoDireito(indice), nivel + 1);
    for (i = 0; i < nivel; i++)
      printf("      ");
    printf("%d\n", H->info[indice]);
    ImprimeArvoreHeap(H, FilhoEsquerdo(indice), nivel + 1);
  }
}

/* Copia n valores do vetor v para dentro do heap SEM organiza-los:
   o resultado quase nunca e um heap valido, e serve justamente para
   o exercicio de construcao. */

void CarregaHeap(Heap *H, int *v, int n)
{
  int i;

  for (i = 0; i < n && i < H->maxsize; i++)
    H->info[i] = v[i];
  H->nelems = i;
}

/* ==================================================================
   EXERCICIO 1 - SOBE HEAP (1,5 pontos)
   ==================================================================

   O elemento da posicao i pode ser maior que o seu pai, o que viola
   a propriedade do heap de maximo. Esta funcao faz esse elemento
   SUBIR ate a posicao correta.

       enquanto i nao for a raiz E o pai for MENOR que info[i]:
           troque info[i] com info[Pai(i)]
           i <- Pai(i)

   Use a macro Pai(i) e a funcao Troca. Cuidado: a raiz e a posicao
   0, e Pai(0) vale 0 pela conta ((0-1)/2), entao o teste de parada
   precisa considerar i > 0.                                        */

void SobeHeap(Heap *H, int i)
{
  while(i!=0 && H->info[Pai(i)] < H->info[i]){
    Troca(&H->info[i], &H->info[Pai(i)]);
    i = Pai(i);
  }
}

/* ==================================================================
   EXERCICIO 2 - DESCE HEAP (1,5 pontos)
   ==================================================================

   O elemento da posicao i pode ser menor que algum dos seus filhos.
   Esta funcao faz esse elemento DESCER ate a posicao correta.

       repita:
           maior <- i
           se o filho esquerdo existe e info[esq] > info[maior]:
               maior <- esq
           se o filho direito existe e info[dir] > info[maior]:
               maior <- dir
           se maior == i: pare (o no ja esta no lugar)
           troque info[i] com info[maior] e continue de i <- maior

   "O filho existe" significa que o indice dele e MENOR que
   H->nelems. Esse teste e essencial: sem ele a funcao le posicoes
   do vetor que nao fazem mais parte do heap.

   Pode ser escrita com um laco ou recursivamente - as duas formas
   valem a nota cheia.                                              */

void DesceHeap(Heap *H, int i)
{
  int maior = i;
  if (FilhoEsquerdo(i) < H->nelems && H->info[FilhoEsquerdo(i)] > H->info[maior]){
    maior = FilhoEsquerdo(i);
  } 
  
  if (FilhoDireito(i) < H->nelems && H->info[FilhoDireito(i)] > H->info[maior]){
    maior = FilhoDireito(i);
  }

  if (maior != i){
    Troca(&H->info[i], &H->info[maior]);
    DesceHeap(H, maior);
      
}
}

/* ==================================================================
   EXERCICIO 3 - INSERCAO E REMOCAO (1,5 pontos)
   ==================================================================

   InsereHeap coloca info no heap. O novo elemento entra na PRIMEIRA
   POSICAO LIVRE do vetor (a posicao nelems), que e a unica que
   mantem a arvore completa, e depois sobe ate o seu lugar. Se o
   heap estiver cheio, nao faz nada.

   RemoveHeap remove e devolve o MAIOR elemento, que esta na raiz:
     - guarde info[0] para devolver;
     - troque info[0] com o ULTIMO elemento (posicao nelems-1);
     - diminua nelems;
     - faca o novo elemento da raiz descer.

   Trocar em vez de simplesmente copiar tem uma vantagem: o elemento
   removido fica guardado na posicao nelems, logo depois do fim do
   heap. E exatamente isso que faz o HeapSort funcionar no proprio
   vetor, sem memoria extra.

   Se o heap estiver vazio, RemoveHeap deve devolver 0.             */

void InsereHeap(Heap *H, int info)
{
  H->info[H->nelems] = info;
  SobeHeap(H, H->nelems);
  H->nelems++;
}

int RemoveHeap(Heap *H)
{
  int sai = H->info[0];
  Troca(&H->info[0], &H->info[H->nelems-1]);
  H->nelems--;
  DesceHeap(H, 0);

  return sai;
}

/* ==================================================================
   EXERCICIO 4 - CONSTRUCAO E ORDENACAO (1,5 pontos)
   ==================================================================

   ConstroiHeap transforma um vetor qualquer em um heap valido, de
   BAIXO PARA CIMA: basta chamar DesceHeap para todos os indices de
   nelems/2 - 1 ate 0, nesta ordem decrescente.

   As posicoes de nelems/2 em diante sao folhas e ja sao heaps
   validos sozinhas, por isso o laco pode comecar em nelems/2 - 1.
   Este metodo custa O(n), enquanto inserir os n elementos um a um
   custaria O(n log n).

   HeapSort ordena o vetor do heap em ordem CRESCENTE:
     - guarde n = nelems;
     - construa o heap;
     - chame RemoveHeap n vezes;
     - devolva nelems para n.

   Funciona porque cada RemoveHeap leva o maior elemento restante
   para a posicao logo apos o fim do heap: depois de n remocoes, o
   vetor inteiro esta ordenado em ordem crescente.                  */

void ConstroiHeap(Heap *H)
{
  for(int i=H->nelems/2 - 1; i>=0; i--){
    DesceHeap(H, i);
  }
}

void HeapSort(Heap *H)
{
  int n = H->nelems;
  ConstroiHeap(H);
  for (int i=0; i<n; i++){
    RemoveHeap(H);
  }
  H->nelems = n;
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
  Heap *H;
  char cmd[8];
  int v[MAX_HEAP];
  int i, n, x;

  H = CriaHeap(MAX_HEAP);

  while (scanf("%1s", cmd) == 1) {
    switch (cmd[0]) {

    case 'I':                                  /* insere */
      scanf("%d", &x);
      InsereHeap(H, x);
      printf("I %d: ", x);
      ImprimeVetorHeap(H);
      break;

    case 'R':                                  /* remove a raiz */
      if (HeapVazio(H)) {
        printf("R: heap vazio\n");
      } else {
        x = RemoveHeap(H);
        printf("R %d: ", x);
        ImprimeVetorHeap(H);
      }
      break;

    case 'V':                                  /* carrega vetor sem organizar */
      scanf("%d", &n);
      for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
      CarregaHeap(H, v, n);
      printf("V: ");
      ImprimeVetorHeap(H);
      break;

    case 'C':                                  /* constroi de baixo para cima */
      ConstroiHeap(H);
      printf("C: ");
      ImprimeVetorHeap(H);
      break;

    case 'H':                                  /* heapsort */
      HeapSort(H);
      printf("H: ");
      ImprimeVetorHeap(H);
      break;

    case 'P':
      printf("P: ");
      ImprimeVetorHeap(H);
      break;

    case 'T':
      printf("T:\n");
      ImprimeArvoreHeap(H, 0, 0);
      break;
    }
  }

  DestroiHeap(&H);

  return 0;
}
