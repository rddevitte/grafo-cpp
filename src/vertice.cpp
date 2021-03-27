#include <iostream>
#include "../inc/vertice.h"
#include "../inc/lista.h"

using namespace std;

Vertice::Vertice()
{
	adj = NULL;
}

void Vertice::insAdj(int a, int dist)
{
	Lista *aux;

	if (adj == NULL)
		adj = new Lista(a, dist);
	else
	{
		aux = adj;

		while (aux->prox != NULL && aux->v != a)
			aux = aux->prox;

		if (aux->v == a)
		{
			cerr << "[" << __func__
				 << "()] Erro: vértice " << a << " adjacente a "
				 << aux->v << " já existe\n";

			return;
		}

		aux->prox = new Lista(a, dist);
	}

	return;
}

Vertice::~Vertice()
{
	Lista *aux;

	while (adj != NULL)
	{
		aux = adj->prox;
		delete adj;
		adj = aux;
	}
}
