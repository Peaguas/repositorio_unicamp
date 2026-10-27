#include "FilaDin.h"

/* Compilar com: gcc TestaFila.c Fila.c -o TestaFila */

int main() {
    Fila *Q = CriaFila();
    int elem,pos;

    (InsereFila(Q, 1));
    (InsereFila(Q, 2));
    (InsereFila(Q, 3));
    
      printf("Elemento %d foi removido\n",elem);
    printf("ini = %d fim = %d qtde = %d\n");

      printf("Elemento 1 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n");


      printf("Elemento 2 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);

      printf("Elemento 3 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if(RemoveFila(Q,&elem))
      printf("Elemento %d foi removido\n",elem);
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);

    
    if (InsereFila(Q, 4))
      printf("Elemento 4 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if (InsereFila(Q, 5))
      printf("Elemento 5 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if (InsereFila(Q, 6))
      printf("Elemento 6 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if(ConsultaFila(Q, 3, &pos))
      printf("Elemento 3 encontrado na posição %d\n",pos);
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if(RemoveFila(Q,&elem))
      printf("Elemento %d foi removido\n",elem);
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if(RemoveFila(Q,&elem))
      printf("Elemento %d foi removido\n",elem);
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);


    if (InsereFila(Q, 7))
      printf("Elemento 7 foi inserido\n");    
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);

    if(ConsultaFila(Q, 6, &pos))
      printf("Elemento 6 encontrado na posição %d\n",pos);
    printf("ini = %d fim = %d qtde = %d\n",Q->ini,Q->fim, Q->qtde);

    ImprimeFila(Q);
    
    DestroiFila(&Q);

    return 0;
}
