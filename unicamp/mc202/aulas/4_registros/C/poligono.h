typedef struct _ponto {
  float x, y; // coordenadas 2D
} Ponto;

typedef struct _poligono {
  Ponto *vertice; // lista de vértices
  int nvertices;  // número de vértices
} Poligono;

Poligono *CriaPoligono(int nvertices);
void      DestroiPoligono(Poligono **P);
float     AreaPoligono(Poligono *P);
float     PerimetroPoligono(Poligono *P);
float     DistanciaEuclideana(Ponto p, Ponto q);
