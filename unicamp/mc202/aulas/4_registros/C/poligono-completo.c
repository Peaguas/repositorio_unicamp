#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "poligono.h"

Poligono *CriaPoligono(int nvertices)
{
  Poligono *P = (Poligono *)calloc(1,sizeof(Poligono));

  P->vertice   = (Ponto *)calloc(nvertices,sizeof(Ponto));
  P->nvertices = nvertices;

  return(P);
}

void DestroiPoligono(Poligono **P)
{
  if ((*P) != NULL){
    free((*P)->vertice);
    free(*P);
    (*P) = NULL;
  }
}

/* Assumindo que os vértices do poligno são armazenados no sentido
   horário, ao percorrer os vértices somamos as áreas dos trapézios de
   altura (P->vertice[(i+1)%P->nvertices].x - P->vertice[i].x) e bases
   P->vertice[(i+1)%P->nvertices].y e P->vertice[i].y para obter a
   área do polígono. */

float     AreaPoligono(Poligono *P)
{
  float area=0.0;

  for (int i=0; i < P->nvertices; i++) {
    float altura = (P->vertice[(i+1)%P->nvertices].x - P->vertice[i].x);
    area += altura * (P->vertice[(i+1)%P->nvertices].y + P->vertice[i].y)/2.0;
  }
  return(area);
}

/* Assumindo que os vértices do poligno são armazenados no sentido
   horário, o perímero é a soma das distâncias entre os vértices
   subsequentes. */

float PerimetroPoligono(Poligono *P)
{
  float perim = 0.0;

  for (int i=0; i < P->nvertices; i++) {
    perim += DistanciaEuclideana(P->vertice[i],P->vertice[(i+1)%P->nvertices]);
  }

  return(perim);
}

float DistanciaEuclideana(Ponto p, Ponto q)
{
  return(sqrtf((q.y-p.y)*(q.y-p.y)+(q.x-p.x)*(q.x-p.x)));
}

int main()
{
  Poligono *P=NULL;
  int nvertices;
  
  printf("Entre com o número de vértices: ");
  scanf("%d",&nvertices);
  setbuf(stdin,NULL);

  P = CriaPoligono(nvertices);
  printf("Entre com os vértices x1 y1 x2 y2...xn yn no sentido horário: ");
  for (int i=0; i < nvertices; i++)
    scanf("%f %f",&P->vertice[i].x,&P->vertice[i].y);

  printf("Area: %.2f \n",AreaPoligono(P));    
  printf("Perímetro: %.2f \n",PerimetroPoligono(P));    

  DestroiPoligono(&P);

  return(0);
}
