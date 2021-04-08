#include <iostream>
#include "../inc/listaprior.h"

using namespace std;

NodoListaPrior::NodoListaPrior(int v, int dist)
{
	this->v = v;
	this->dist = dist;
	prox = NULL;
}

NodoListaPrior::~NodoListaPrior()
{
}

ListaPrior::ListaPrior(int i, int tam)
{
	if (i < 0 || i > 1)
	{
		cerr << "[" << __func__
			 << "()] i deve ser 0 ou 1, assumindo 0\n";
		this->i = 0;
	}
	else
	{
		this->i = i;
	}

	this->tam = tam;

	min = new NodoListaPrior(i, INF);

	NodoListaPrior *aux = min;

	for (int n = i + 1; n < tam + i; n++)
	{
		aux->prox = new NodoListaPrior(n, INF);
		aux = aux->prox;
	}
}

ListaPrior::ListaPrior(const ListaPrior& l)
{
	this->i = l.i;
	this->tam = l.tam;

	min = new NodoListaPrior(i, INF);

	NodoListaPrior *aux = min;

	for (int n = i + 1; n < tam + i; n++)
	{
		aux->prox = new NodoListaPrior(n, INF);
		aux = aux->prox;
	}
}

ListaPrior& ListaPrior::operator=(const ListaPrior& l)
{
	if (&l != this)
	{
		delete min;

		this->i = l.i;
		this->tam = l.tam;

		min = new NodoListaPrior(i, INF);

		NodoListaPrior *aux = min;

		for (int n = i + 1; n < tam + i; n++)
		{
			aux->prox = new NodoListaPrior(n, INF);
			aux = aux->prox;
		}
	}

	return *this;
}

bool ListaPrior::vazia() const
{
	if (tam == 0)
		return true;

	return false;
}

void ListaPrior::imprime() const
{
	NodoListaPrior *aux;

	if (tam == 0)
	{
		cerr << "[" << __func__ << "()] Erro: lista prior. vazia\n";
		return;
	}

	aux = min;

	cout << "Lista prior. de tam. " << tam << ":";

	while (aux != NULL)
	{
		cout << " " << aux->v << "(";

		if (aux->dist == INF)
			cout << "Inf";
		else
			cout << aux->dist;

		cout << ")";

		aux = aux->prox;
	}

	cout << "\n";

	return;
}

int ListaPrior::extraiMin()
{
	NodoListaPrior *aux;
	int m;

	if (min == NULL)
	{
		cerr << "[" << __func__ << "()] Erro: lista vazia\n";
		return -1;
	}

	m = min->v;

	aux = min;
	min = min->prox;
	delete aux;

	tam--;

	return m;
}

void ListaPrior::decresceChave(int v, int dist)
{
	NodoListaPrior *aux, *ant;

	if (v < i)
	{
		cerr << "[" << __func__
			 << "()] Erro: vértice " << v << " inválido\n";
		return;
	}

	/* Se chave alvo está no início da lista, apenas muda chave (dist) */
	if (v == min->v)
	{
		min->dist = dist;
	}
	/* Senão, percorre a lista e refaz os apontamentos */
	else
	{
		ant = min;
		aux = min->prox;

		while (aux != NULL && v != aux->v)
		{
			ant = aux;
			aux = aux->prox;
		}

		if (aux == NULL)
		{
			cerr << "[" << __func__
				 << "()] Vértice " << v << " não encontrado\n";
			return;
		}

		aux->dist = dist;

		/* Reapontamentos */

		/* Caso 1: nova chave do vértice alvo é menor ou igual
		   que a chave do vértice inicial (min) */
		if (aux->dist <= min->dist)
		{
			ant->prox = aux->prox;
			aux->prox = min;
			min = aux;
		}
		/* Caso 2: nova chave é igual ou maior que a anterior e
		   não há vértices à frente -> não necessita mover ponteiros */
		else if (aux->dist >= ant->dist)
		{
			/* Prossegue (sai do if()) */
		}
		/* Caso 3: nova chave é igual ou maior que a anterior e menor
		   ou igual ao vértice à frente -> mesmo do caso anterior */
		else if (aux->dist >= ant->dist && aux->dist <= aux->prox->dist)
		{
			/* Prossegue (sai do if()) */
		}
		/* Caso 4: nova chave é menor que a anterior
		   -> necessita movimentação */
		else
		{
			ant->prox = aux->prox;
			ant = min;

			while (ant->prox != NULL && ant->prox->dist <= aux->dist)
				ant = ant->prox;

			aux->prox = ant->prox;
			ant->prox = aux;
		}
	}

	return;
}

ListaPrior::~ListaPrior()
{
	while (min != NULL)
	{
		NodoListaPrior *aux = min;
		min = min->prox;
		delete aux;
		tam--;
	}
}
