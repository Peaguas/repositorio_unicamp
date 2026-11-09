#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "poligono.h"



Poligono *CriaPoligono(int nvertices)
{
  Poligono *P = (Poligono *)calloc(1, sizeof(Poligono));

  P->vertice = (Ponto *)calloc(nvertices, sizeof(Ponto));
  P->nvertices = nvertices;

  return P;
}

void DestroiPoligono(Poligono **P)
{
  if((*P) != NULL){
    for (int i=0; i<(*P)->nvertices; i++){
      //libera cada ponto do poligono
    } 
    free((*P)->vertice);
    (*P)->vertice = NULL;
    (*P)->nvertices = 0;
    free((*P));
    (*P) = NULL;
  }
}

float AreaPoligono(Poligono *P)
{
  float area = 0.0; 
  float altura, bM, bm, dA;

  for (int i=0; i<P->nvertices; i++) {
    bM = P->vertice[(i+1)%P->nvertices].y;
    bm = P->vertice[i].y;
    altura = P->vertice[(i+1)%P->nvertices].x-P->vertice[i].x;
    dA = (bM + bm)*(altura)/2;
    area += dA;
  }

  return area;
}

float PerimetroPoligono(Poligono *P)
{
  float perimetro = 0;
  for (int i = 0; i<P->nvertices; i++){
    perimetro += DistanciaEuclideana(P->vertice[i], P->vertice[(i+1)%P->nvertices]);
  }

  return perimetro;
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
