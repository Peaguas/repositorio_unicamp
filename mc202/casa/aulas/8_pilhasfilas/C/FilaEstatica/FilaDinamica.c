#include "FilaDin.h"

No *CriaNo(int elem){
    No *no = (No *)calloc(1, sizeof(No));

    no->val = elem;
    no->prox = NULL;

    return no;
}

Fila *CriaFila(){
    Fila *Q = NULL;
}

Fila DestroiFila(Fila **Q){

    int elem;

    while(!FilaVazia(*Q)){
        RemoveFila(Q,&elem);
        free(*Q);
    }
}

bool FilaVazia(Fila *Q){
    if(Q==NULL){
        return true;
    } return false;
}

bool InsereFila(No **Q, int elem){
    Fila *X = *Q;

    if (FilaVazia(X)){
        *Q = CriaNo(elem);
    } else{
        while (X->prox =!NULL){
            X = X->prox;
        }
        X->prox = CriaNo(elem);
        
    }
    return true;
}

bool RemoveFila(Fila **Q, int *elem){
    if (FilaVazia(*Q)){
        printf("Aviso: fila está vazia!\n");
        return false;
    } else{
        No *no = *Q;
        *Q = (*Q)->prox;
        *elem = no->val;
        free(no);
        return true;
    }
}

bool ConsultaFila(Fila *Q, int elem , No **pos){
    if (FilaVazia(Q)) {
        printf("Aviso: Fila esta vaiza!\n");
        return false;
    }
    else{
        while((Q->val != elem)&&(Q != NULL)){
            Q=Q->prox;
        }
        if (Q==NULL){
            return false;
        }else{
            *pos = Q;
        }
         return true;
    }
}

void ImprimeFila (Fila *Q){
    for (; Q!=NULL; Q=Q->prox){
        printf("%d ", Q->val);
    }
    print("\n");
}