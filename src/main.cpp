#include <iostream>
#include <locale>
#include "../inc/grafo.h"

using namespace std;

void imprimeCaminho(int, int, int *, int *);

int main(void)
{
	Grafo g(0, 7);
	int x, *c;
	int *dist, *prev;

	setlocale(LC_ALL, "");

	g.insAdj(0, 1, 12, true);
	g.insAdj(0, 2, 30, true);
	g.insAdj(1, 2, 35, true);
	g.insAdj(1, 3, 25, true);
	g.insAdj(1, 4, 20, true);
	g.insAdj(2, 3, 17, true);
	g.insAdj(2, 5, 15, true);
	g.insAdj(3, 4, 7, true);
	g.insAdj(3, 5, 15, true);
	g.insAdj(4, 5, 10, true);
	g.insAdj(4, 6, 12, true);
	g.insAdj(5, 6, 5, true);

	g.imprime();

	cout << "\n";

	g.buscaLargura(0);
	g.buscaProfundidade(0);

	cout << "\n";

	c = g.componentes();

	cout << "Componentes:\n";

	for (x = 0; x < g.numVerts(); x++)
		cout << x << "\t" << c[x] << "\n";

	delete[] c;

	cout << "\n";

	dist = NULL;
	prev = NULL;
	g.caminhoMinimo(0, &dist, &prev);

	cout << "Caminhos:\n";

	imprimeCaminho(0, 7, dist, prev);

	delete[] dist;
	delete[] prev;

	cout << "\n";

	return 0;
}

void imprimeCaminho(int i, int n, int *dist, int *prev)
{
	int k;

	if (dist == NULL || prev == NULL)
	{
		cerr << "[" << __func__ << "()] Erro: dist ou prev é nulo\n";
		return;
	}

	cout << "V\tdist\tprev\n";

	for (k = i; k < n + i; k++)
		cout << k << "\t" << dist[k] << "\t" << prev[k] << "\n";

	return;
}
