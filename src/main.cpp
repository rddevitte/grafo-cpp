#include "grafo.h"
#include <iostream>
#include <locale>
#include <utility>

int main(void)
{
    Grafo g;

    setlocale(LC_ALL, "");

    g.insAdj(0, 1, 12);
    g.insAdj(0, 2, 30);
    g.insAdj(1, 2, 35);
    g.insAdj(1, 3, 25);
    g.insAdj(1, 4, 20);
    g.insAdj(2, 3, 17);
    g.insAdj(2, 5, 15);
    g.insAdj(3, 4, 7);
    g.insAdj(3, 5, 15);
    g.insAdj(4, 5, 10);
    g.insAdj(4, 6, 12);
    g.insAdj(5, 6, 5);

    g.imprime();

    std::cout << "\n";

    g.buscaLargura(0);
    g.buscaProfundidade(0);

    std::cout << "\n";

    auto c = g.componentes();

    std::cout << "Componentes do grafo:\n";

    for (const auto& comp : c) {
        std::cout << comp.first << "\t" << comp.second << "\n";
    }

    std::cout << "\n";

    auto dist_and_prev = g.caminhoMinimo(0);

    auto dist = dist_and_prev.first;
    auto prev = dist_and_prev.second;

    std::cout << "Caminhos (partindo do vértice 0):\n";

    std::cout << "V\tdist\tprev\n";

    for (auto iter_dist = dist.begin(), iter_prev = prev.begin();
         iter_dist != dist.end() && iter_prev != prev.end();
         ++iter_dist, ++iter_prev) {
        std::cout << iter_dist->first << "\t" << iter_dist->second << "\t"
                  << iter_prev->second << "\n";
    }

    std::cout << "\n";

    return 0;
}
