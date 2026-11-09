#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

typedef struct _vetor {
  float *val; // vetor de reais
  int nelems; // número de elementos
} Vetor;

Vetor CriaVetor1(int nelems)
{
  Vetor v;

  v.val = (float *)calloc(nelems,sizeof(float));
  v.nelems = nelems;

  return(v);
}

void DestroiVetor1(Vetor *v)
{
  if (v->val != NULL){
    for (int i=0; i<v->nelems; i++){
      v->val[i]=0;
    }
    free(v->val);
    v->val = NULL; v->nelems = 0;
  }
}

Vetor *CriaVetor2(int nelems)
{
  Vetor *u = (Vetor *)calloc(1,sizeof(Vetor));

  u->val = (float *)calloc(nelems,sizeof(float));
  u->nelems = nelems;

  return(u);
}

void DestroiVetor2(Vetor **u)
{
  if ((*u) != NULL){
    if ((*u)->val != NULL)
    for (int i = 0; i<(*u)->nelems; i++) {
      (*u)->val[i] = 0;
    }
      free((*u)->val);
      (*u)->val = NULL, (*u)->nelems = 0;
    free(*u);
    (*u) = NULL;
  }
}
    
/* Gera número real aleatório em [min,max] */

double NumeroAleatorio(float min, float max) {
  double d;
  d = ((double) rand()) / (double) RAND_MAX;
  return(min + d * (max - min));
}

/* Cria vetor com n números aleatórios em [min,max] */

Vetor VetorAleatorio1(int n, float min, float max)
{
  Vetor v = CriaVetor1(n);
  for (int i=0; i < n; i++)
    v.val[i] = (float) NumeroAleatorio(min,max);
  return(v);
}

/* Cria vetor com n números aleatórios em [min,max] */

Vetor *VetorAleatorio2(int n, float min, float max)
{
  Vetor *u = CriaVetor2(n);
  for (int i=0; i < n; i++)
    u->val[i] = (float) NumeroAleatorio(min,max);
  return(u);
}

/* Imprime vetor */

void ImprimeVetor(Vetor v)
{
  for(int i=0; i < v.nelems; i++)
    printf("%.2f ",v.val[i]);
  printf("\n");
}

int main()
{
  Vetor v, *u=NULL; // duas opções

  v.val = NULL; v.nelems = 0;
  
  srand(time(NULL));
  v = VetorAleatorio1(5,0,100);
  ImprimeVetor(v);
  
  u = VetorAleatorio2(5,0,100);
  ImprimeVetor(*u);
  
  DestroiVetor1(&v);
  DestroiVetor2(&u);

  return(0);
}
