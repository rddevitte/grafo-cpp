#include "../inc/grafo.h"
#include <iostream>
#include <locale>

void imprimeCaminho(int, int, int*, int*);

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

    std::cout << "\n";

    g.buscaLargura(0);
    g.buscaProfundidade(0);

    std::cout << "\n";

    c = g.componentes();

    std::cout << "Componentes:\n";

    for (x = 0; x < g.numVerts(); x++)
        std::cout << x << "\t" << c[x] << "\n";

    delete[] c;

    std::cout << "\n";

    dist = nullptr;
    prev = nullptr;
    g.caminhoMinimo(0, &dist, &prev);

    std::cout << "Caminhos:\n";

    imprimeCaminho(0, 7, dist, prev);

    delete[] dist;
    delete[] prev;

    std::cout << "\n";

    return 0;
}

void imprimeCaminho(int i, int n, int* dist, int* prev)
{
    int k;

    if (dist == nullptr || prev == nullptr) {
        std::cerr << "[" << __func__ << "()] Erro: dist ou prev é nulo\n";
        return;
    }

    std::cout << "V\tdist\tprev\n";

    for (k = i; k < n + i; k++)
        std::cout << k << "\t" << dist[k] << "\t" << prev[k] << "\n";

    return;
}
