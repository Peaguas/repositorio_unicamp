#include "ListaSimples.h"
 
bool ListaSimplesVazia(ListaSimples *inicio)
{
  if (inicio == NULL) 
    return(true);
  else
    return(false);
}

void ImprimeListaSimples(ListaSimples *inicio)
{
  
  while (!ListaSimplesVazia(inicio)){
    printf("%d -->",inicio->elem);
    inicio = inicio->prox; 
  }
}

bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant)
{
  *ant = NULL; *pos = inicio;

  while (!ListaVazia(*pos)){
    if(((*pos)->elem) == elem){
      return true;
    }
    *ant = (*pos);
    *pos = (*pos)->prox;
  }
  return false;
}

bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant){

  *ant = NULL; *pos = inicio;

  if (ListaSimplesVazia(*pos))
    return(false);

  while (!ListaSimplesVazia((*pos)->prox)){
    *ant   = (*pos);
    *pos   = (*pos)->prox;    
  }

  return(true);
}

NoListaSimples *CriaNoSimples(int elem)
{
  NoListaSimples *no = (NoListaSimples *)calloc(1,sizeof(NoListaSimples));
  
  no->elem = elem;
  no->prox = NULL;
  
  return(no);
}

void InsereInicioListaSimples(ListaSimples **inicio, int elem)
{
  /* preencher */

  NoListaSimples *no = CriaNoSimples(elem); 

  no->prox = *inicio;
  *inicio = no;

}

void InsereFimListaSimples(ListaSimples **inicio, int elem)
{
    /* preencher */
    // *inicio -> [10] -> [20] -> [30] -> NULL
    // *ant     *prox
    NoListaSimples *no = CriaNoSimples(elem);
    NoListaSimples *ant, *pos;

    if (BuscaUltimoElementoListaSimples(*inicio, &pos, &ant)){
      pos->prox = no;
    } else{
      *inicio = no;
    }
}

bool InsereElementoAntesDaChaveListaSimples(ListaSimples **inicio, int elem, int chave)
{
  NoListaSimples *ant, *pos;

  if (BuscaElementoListaSimples(*inicio, elem, &pos, &ant)){
    if (ant == NULL){
      InsereInicioListaSimples(*inicio, elem);
    } else {
      InsereInicioListaSimples(&pos, elem);
      ant->prox = pos;
    }
    return true;
  }
  return false;
    /* preencher */
}

bool  RemoveInicioListaSimples(ListaSimples **inicio, int *elem)
{
  
      /* preencher */
}

bool RemoveElementoListaSimples(ListaSimples **inicio, int elem)
{
      /* preencher */
}

bool  RemoveFimListaSimples(ListaSimples **inicio, int *elem)
{
      /* preencher */
}

void DestroiListaSimples(ListaSimples **inicio)
{
  int elem;

  while(!ListaSimplesVazia(*inicio))
    RemoveInicioListaSimples(inicio,&elem);

}
