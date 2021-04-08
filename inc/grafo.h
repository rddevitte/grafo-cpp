#ifndef GRAFO_H
#define GRAFO_H

#include "vertice.h"

/* Infinito definido como a metade do maior número inteiro de 32 bits com sinal
   (p/ algoritmo de Dijkstra) */
#define INF 0x3FFFFFFF

class Grafo
{
private:
	/* Vértice inicial */
	int i;
	/* Número de vértices */
	int n;
	/* Lista de vértices */
	Vertice *vs;
public:
	Grafo(int i, int n);
	int  numVerts() const;
	void insAdj(int v, int a, int dist, bool bidir);
	void imprime() const;
	void buscaProfundidade(int v);
	void buscaLargura(int v);
	int *componentes();
	void caminhoMinimo(int v, int **dist, int **prev);
	~Grafo();
};

#endif /* GRAFO_H */
