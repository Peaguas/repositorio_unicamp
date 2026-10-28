#ifndef _FILA_H_DIN_
#define _FILA_H_DIN_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef bool 
typedef enum _bool {
  false, true
} bool;
#endif

typedef struct _no {
  int val;
  struct _no *prox;
} No, Fila;

/* Vamos implementar como fila circular */




No *CriaNo(int elem);
Fila *CriaFila();
void  DestroiFila(Fila **Q);
bool  FilaVazia(Fila *Q);
bool  FilaCheia(Fila *Q);
bool  InsereFila(Fila **Q, int elem);
bool  RemoveFila(Fila **Q, int *elem);
bool  ConsultaFila(Fila *Q, int elem, No **pos);
void  ImprimeFila(Fila *Q);

#endif
