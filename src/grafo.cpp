#include <iostream>
#include "../inc/fila.h"
#include "../inc/grafo.h"
#include "../inc/lista.h"
#include "../inc/listaprior.h"
#include "../inc/pilha.h"

using namespace std;

/**
 * Construtor do grafo.
 * @param i Vértice inicial (deve ser 0 ou 1).
 * Se i = 0, os vértices são numerados de 0 a n - 1.
 * Se i = 1, os vértices são numerados de 1 a n.
 * @param n Número de vértices
 */
Grafo::Grafo(int i, int n)
{
	if (i < 0 || i > 1)
	{
		cerr << "i deve ser 0 ou 1, assumindo 0\n";
		this->i = 0;
	}
	else
		this->i = i;

	this->n = n;

	vs = new Vertice[n + 1];
}

/**
 * Destrutor do grafo.
 */
Grafo::~Grafo()
{
	delete[] vs;
}

/**
 * Retorna o número de vértices do grafo.
 * @return Número de vértices do grafo
 */
int Grafo::numVerts()
{
	return n;
}

/**
 * Insere um vértice adjacente 'a' a um vértice 'v' da lista
 * com distância 'dist'.
 * @param v O vértice
 * @param a O vértice adjacente
 * @param dist Distância entre 'v' e 'a'
 * @param bidir Indica se o vértice é bidirecional
 */
void Grafo::insAdj(int v, int a, int dist, bool bidir)
{
	if (v < 0 || v > n)
	{
		cerr << "[" << __func__
			 << "()] Erro: vértice " << v << " inválido\n";
		return;
	}

	if (a < 0 || a > n)
	{
		cerr << "[" << __func__
			 << "()] Erro: vértice adjacente " << a << " inválido\n";
		return;
	}

	vs[v].insAdj(a, dist);

	if (bidir)
		vs[a].insAdj(v, dist);

	return;
}

/**
 * Imprime os vértices do grafo, seus adjacentes e suas distâncias.
 */
void Grafo::imprime()
{
	Lista *aux;
	int v;

	cout << "Número de vértices: " << n << "\n";

	for (v = i; v < n + i; v++)
	{
		cout << "Adjacentes a " << v << ":";

		if (vs[v].adj == NULL)
			cout << " nenhum";
		else
		{
			aux = vs[v].adj;

			while (aux != NULL)
			{
				cout << " " << aux->v << "(" << aux->dist << ")";
				aux = aux->prox;
			}
		}

		cout << "\n";
	}
}

/**
 * Executa o algoritmo de busca em profundidade no grafo.
 * @param v O vértice inicial a ser visitado
 */
void Grafo::buscaProfundidade(int v)
{
	Pilha p;
	bool *visitado;
	int k;
	Lista *aux;

	if (v < i || v > (n - 1) + i)
	{
		cerr << "[" << __func__
			 << "()] Erro: vért. ini. " << v << " inválido\n";
		return;
	}

	visitado = new bool[n + 1];

	for (k = 0; k <= n; k++)
		visitado[k] = false;

	p.push(v);

	cout << "Ordem de visitação em DFS:";

	while (!p.vazia())
	{
		k = p.pop();

		if (!visitado[k])
		{
			cout << " " << k;
			visitado[k] = true;

			aux = vs[k].adj;

			while (aux != NULL)
			{
				if (!visitado[aux->v])
					p.push(aux->v);

				aux = aux->prox;
			}
		}
	}

	cout << "\n";

	delete[] visitado;

	return;
}

/**
 * Executa o algoritmo de busca em largura no grafo.
 * @param v O vértice inicial a ser visitado
 */
void Grafo::buscaLargura(int v)
{
	Fila f;
	bool *visitado;
	int k;
	Lista *aux;

	if (v < i || v > (n - 1) + i)
	{
		cerr << "[" << __func__
			 << "()] Erro: vért. ini. " << v << " inválido\n";
		return;
	}

	visitado = new bool[n + 1];

	for (k = 0; k <= n; k++)
		visitado[k] = false;

	f.insere(v);

	cout << "Ordem de visitação em BFS:";

	while (!f.vazia())
	{
		k = f.retira();

		if (!visitado[k])
		{
			cout << " " << k;
			visitado[k] = true;

			aux = vs[k].adj;

			while (aux != NULL)
			{
				if (!visitado[aux->v])
					f.insere(aux->v);

				aux = aux->prox;
			}
		}
	}

	cout << "\n";

	delete[] visitado;

	return;
}

/**
 * Percorre o grafo e verifica se existem componentes (um vértice ou um
 * grupo de vértices) não conectados ao resto do grafo.
 * @return Vetor com a lista de componentes (grupos)
 */
int *Grafo::componentes()
{
	Pilha p;
	int *c, v, k, cont;
	Lista *aux;

	c = new int[n + 1];

	for (v = 0; v <= n; v++)
		c[v] = 0;

	cont = 0;

	for (v = i; v < n + i; v++)
	{
		if (c[v] == 0)
		{
			cont++;
			p.push(v);

			while (!p.vazia())
			{
				k = p.pop();

				if (c[k] == 0)
				{
					c[k] = cont;

					aux = vs[k].adj;

					while (aux != NULL)
					{
						if (c[aux->v] == 0)
							p.push(aux->v);

						aux = aux->prox;
					}
				}
			}
		}
	}

	return c;
}

/**
 * Executa o algoritmo do caminho mínimo (algoritmo de Dijkstra) no grafo.
 * @param v O vértice de partida
 * @param dist O vetor de distâncias
 * @param prev O vetor de vértices anteriores
 */
void Grafo::caminhoMinimo(int v, int **dist, int **prev)
{
	ListaPrior lp(i, n);
	Lista *aux;
	int k, p, q, peso;

	if (v < i || v > (n - 1) + i)
	{
		cerr << "[" << __func__
			 << "()] Erro: vért. ini. " << v << " inválido\n";
		return;
	}

	if (*dist == NULL)
		*dist = new int[n + 1];

	if (*prev == NULL)
		*prev = new int[n + 1];

	for (k = 0; k <= n; k++)
	{
		(*dist)[k] = INF;
		(*prev)[k] = -1;
	}

	(*dist)[v] = 0;
	lp.decresceChave(v, 0); // vértice inicial

	while (!lp.vazia())
	{
		p = lp.extraiMin();

		aux = vs[p].adj;

		while (aux != NULL)
		{
			q = aux->v;
			peso = aux->dist;

			if ((*dist)[q] > (*dist)[p] + peso)
			{
				(*dist)[q] = (*dist)[p] + peso;
				lp.decresceChave(q, (*dist)[q]);
				(*prev)[q] = p;
			}

			aux = aux->prox;
		}
	}

	return;
}
