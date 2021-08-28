/**
 * @file main.cpp
 * @brief Expõe exemplo de utilização da classe Grafo
 */
#include "grafo.h"
#include <iomanip>
#include <iostream>
#include <locale>
#include <utility>

template <typename V, typename Dist>
void imprimeGrafo(const Grafo<V, Dist>& g);

template <typename V>
void imprimeVertice(V& v);

template <typename V>
void imprimeComponentes(std::map<int, std::vector<V>> comp);

template <typename V, typename Dist>
void imprimeCaminhosEDistancias(std::pair<std::map<V, Dist>, std::map<V, V>> dist_e_prev);

int main(void)
{
    Grafo<int, int> g;

    std::setlocale(LC_ALL, "");

    g.insereAdjacente(0, 1, 12);
    g.insereAdjacente(0, 2, 30);
    g.insereAdjacente(1, 2, 35);
    g.insereAdjacente(1, 3, 25);
    g.insereAdjacente(1, 4, 20);
    g.insereAdjacente(2, 3, 17);
    g.insereAdjacente(2, 5, 15);
    g.insereAdjacente(3, 4, 7);
    g.insereAdjacente(3, 5, 15);
    g.insereAdjacente(4, 5, 10);
    g.insereAdjacente(4, 6, 12);
    g.insereAdjacente(5, 6, 5);

    imprimeGrafo<int, int>(g);

    std::cout << "\nOrdem de visitação em BFS:";
    g.buscaLargura(0, imprimeVertice<int>);

    std::cout << "\nOrdem de visitação em DFS:";
    g.buscaProfundidade(0, imprimeVertice<int>);

    std::cout << "\n\nComponentes do grafo:\n";
    imprimeComponentes<int>(g.getComponentes());

    std::cout << "\nCaminhos (partindo do vértice 0):\n";
    imprimeCaminhosEDistancias<int, int>(g.caminhoMinimo(0));

    return 0;
}

template <typename V, typename Dist>
void imprimeGrafo(const Grafo<V, Dist>& g)
{
    int num_verts = g.numVertices();

    std::cout << "Núm. vértices: " << num_verts << "\n";

    if (num_verts == 0)
        return;

    std::cout << "Adjacentes a\n";

    for (const auto& v : g.getVertices()) {
        std::cout << "  " << v << ":";

        std::vector<std::pair<V, Dist>> adj = g.getAdjacentes(v);

        if (adj.size() == 0)
            std::cout << " nenhum";
        else {
            for (const auto& a : adj)
                std::cout << " " << a.first << "(" << a.second << ")";
        }

        std::cout << "\n";
    }
}

template <typename V>
void imprimeVertice(V& v)
{
    std::cout << " " << v;
}

template <typename V>
void imprimeComponentes(std::map<int, std::vector<V>> comp)
{
    if (comp.empty()) {
        std::cout << "(nenhum)\n";
        return;
    }

    std::cout << "Comp.  Vértices\n";

    for (const auto& c : comp) {
        std::cout << std::setw(5) << c.first << "  ";

        for (const auto& v : c.second)
            std::cout << " " << v;

        std::cout << "\n";
    }
}

template <typename V, typename Dist>
void imprimeCaminhosEDistancias(std::pair<std::map<V, Dist>, std::map<V, V>> dist_e_prev)
{
    auto dist = dist_e_prev.first;
    auto prev = dist_e_prev.second;

    if (dist.size() != prev.size()) {
        std::cerr << "Erro: tamanhos dos 'maps' de distâncias e caminhos são diferentes!\n";
        return;
    }

    std::cout << " V  dist  prev\n";

    for (auto iter_dist = dist.begin(), iter_prev = prev.begin();
         iter_dist != dist.end() && iter_prev != prev.end(); ++iter_dist, ++iter_prev) {
        std::cout << std::setw(2) << iter_dist->first << "  "
                  << std::setw(4) << iter_dist->second << "  "
                  << std::setw(4) << iter_prev->second << "\n";
    }

    std::cout << "\n";
}
