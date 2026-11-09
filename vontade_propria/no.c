#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _no{
    int elem;
    struct _no *prox;
} No;

No *CriaNo(int elem){
    No *no = (No *)calloc(1, sizeof(No));

    no->elem = elem;
    no->prox = NULL;

    return no;
}

int ListaVazia(No *lista){
    if (lista == NULL){
        return 1;
    } 
    return 0;
}

void InsereInicio(No **primeiro_no, int elem){
    No *p = CriaNo(elem);

    p->prox = (*primeiro_no);
    *primeiro_no = p;
    
}

void ImprimeLista(No *lista){
    No *pos = lista;
    printf("inicio -> ");
    if (ListaVazia(lista)){
        printf("Lista Vazia");
    } else {
        while(pos != NULL){
            printf("[%d|-] -> ", pos->elem);
            pos = pos->prox;
        }
    }
    printf("NULL\n");
}

void BuscaElemento(No *inicio, int elem, No **ant, No **atual){
    if (inicio==NULL){
        printf("Lista vazia");
    }
    int cont = 0;
    *ant = NULL;
    *atual = inicio;
    while ((*atual)->elem != elem && (*atual)!=NULL){
        (*ant) = (*atual);
        (*atual) = (*atual)->prox;
        cont++;
    }
    printf("elem está no nó: %d\n", cont);

}

void DestroiLista(No **inicio){
    No *atual = *inicio;
    No *prox;

    while (prox != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

int main(){
    No *lista = NULL;
    No *ant; No *atual;

    InsereInicio(&lista, 3);
    InsereInicio(&lista, 2);
    InsereInicio(&lista, 1);
    ImprimeLista(lista);
    BuscaElemento(lista, 2, &ant, &atual);



    DestroiLista(&lista);
}