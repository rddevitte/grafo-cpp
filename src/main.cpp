/**
 * @file main.cpp
 * @brief Expõe exemplo de utilização da classe Grafo
 */
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <utility>

#include "grafo.h"

template <typename V, typename Dist>
void imprimeGrafo(const Grafo<V, Dist> &g);

template <typename V>
void imprimeVertice(V &v);

template <typename V>
void imprimeComponentes(const std::map<int, std::vector<V>> &comp);

template <typename V, typename Dist>
void imprimeCaminhosEDistancias(const std::pair<std::map<V, Dist>, std::map<V, V>> &dist_e_prev);

int main()
{
    std::setlocale(LC_ALL, "");

    Grafo<std::string, double> g;

    g.insereAdjacente("0", "1", 12.0);
    g.insereAdjacente("0", "2", 30.0);
    g.insereAdjacente("1", "2", 35.0);
    g.insereAdjacente("1", "3", 25.0);
    g.insereAdjacente("1", "4", 20.0);
    g.insereAdjacente("2", "3", 17.0);
    g.insereAdjacente("2", "5", 15.0);
    g.insereAdjacente("3", "4", 7.0);
    g.insereAdjacente("3", "5", 15.0);
    g.insereAdjacente("4", "5", 10.0);
    g.insereAdjacente("4", "6", 12.0);
    g.insereAdjacente("5", "6", 5.0);

    imprimeGrafo<std::string, double>(g);

    std::cout << "\nOrdem de visitação em BFS:";
    g.buscaLargura("0", imprimeVertice<std::string>);

    std::cout << "\nOrdem de visitação em DFS:";
    g.buscaProfundidade("0", imprimeVertice<std::string>);

    std::cout << "\n\nComponentes do grafo:\n";
    imprimeComponentes<std::string>(g.getComponentes());

    std::cout << "\nCaminhos (partindo do vértice 0):\n";
    imprimeCaminhosEDistancias<std::string, double>(g.caminhoMinimo("0"));
}

template <typename V, typename Dist>
void imprimeGrafo(const Grafo<V, Dist> &g)
{
    int num_verts = g.numVertices();

    std::cout << "Núm. vértices: " << num_verts << "\n";

    if (num_verts == 0)
        return;

    std::cout << "Adjacentes a\n";

    for (const auto &v : g.getVertices()) {
        std::cout << "  " << v << ":";

        std::vector<std::pair<V, Dist>> adj = g.getAdjacentes(v);

        if (adj.size() == 0)
            std::cout << " nenhum";
        else {
            for (const auto &a : adj)
                std::cout << " " << a.first << "(" << a.second << ")";
        }

        std::cout << "\n";
    }
}

template <typename V>
void imprimeVertice(V &v)
{
    std::cout << " " << v;
}

template <typename V>
void imprimeComponentes(const std::map<int, std::vector<V>> &comp)
{
    if (comp.empty()) {
        std::cout << "(nenhum)\n";
        return;
    }

    std::cout << "Comp.  Vértices\n";

    for (const auto &c : comp) {
        std::cout << std::setw(5) << c.first << "  ";

        for (const auto &v : c.second)
            std::cout << " " << v;

        std::cout << "\n";
    }
}

template <typename V, typename Dist>
void imprimeCaminhosEDistancias(const std::pair<std::map<V, Dist>, std::map<V, V>> &dist_e_prev)
{
    auto dist = dist_e_prev.first;
    auto prev = dist_e_prev.second;

    if (dist.size() != prev.size()) {
        std::cerr << "Erro: tamanhos dos 'maps' de distâncias e caminhos são diferentes!\n";
        return;
    }

    std::cout << " V  dist  prev\n";

    using iter_dist_map = typename std::map<V, Dist>::iterator;
    using iter_prev_map = typename std::map<V, V>::iterator;

    for (std::pair<iter_dist_map, iter_prev_map> i(dist.begin(), prev.begin());
         i.first != dist.end() && i.second != prev.end(); ++i.first, ++i.second) {
        std::cout << std::setw(2) << i.first->first << "  " << std::setw(4) << i.first->second
                  << "  " << std::setw(4) << i.second->second << "\n";
    }

    std::cout << "\n";
}
