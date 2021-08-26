#include "grafo.h"
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <utility>

Grafo::Grafo()
{
}

Grafo::~Grafo()
{
}

int Grafo::numVerts() const
{
    return static_cast<int>(vs_.size());
}

void Grafo::insAdj(int v, int a, int dist, bool bidir)
{
    vs_[v].push_back({ a, dist });

    if (bidir)
        vs_[a].push_back({ v, dist });

    return;
}

void Grafo::imprime() const
{
    std::cout << "Número de vértices: " << numVerts() << "\n";

    for (const auto& v : vs_) {
        std::cout << "Adjacentes a " << v.first << ":";

        if (v.second.empty())
            std::cout << " nenhum";
        else {
            for (const auto& adj : v.second) {
                std::cout << " " << adj.first
                          << "(" << adj.second << ")";
            }
        }

        std::cout << "\n";
    }
}

void Grafo::buscaProfundidade(int v)
{
    if (vs_.empty()) {
        std::cerr << "[" << __func__
                  << "()] Erro: grafo vazio (nenhum vértice)\n";
        return;
    }

    if (vs_.find(v) == vs_.end()) {
        std::cerr << "[" << __func__
                  << "()] Erro: vért. ini. " << v << " inválido\n";
        return;
    }

    std::map<int, bool> visitado;

    for (const auto& vert : vs_)
        visitado[vert.first] = false;

    std::stack<int> p;

    p.push(v);

    std::cout << "Ordem de visitação em DFS:";

    while (!p.empty()) {
        int k = p.top();
        p.pop();

        if (!visitado[k]) {
            std::cout << " " << k;

            visitado[k] = true;

            for (const auto& adj : vs_[k]) {
                if (!visitado[adj.first])
                    p.push(adj.first);
            }
        }
    }

    std::cout << "\n";
}

void Grafo::buscaLargura(int v)
{
    if (vs_.empty()) {
        std::cerr << "[" << __func__
                  << "()] Erro: grafo vazio (nenhum vértice)\n";
        return;
    }

    if (vs_.find(v) == vs_.end()) {
        std::cerr << "[" << __func__
                  << "()] Erro: vért. ini. " << v << " inválido\n";
        return;
    }

    std::map<int, bool> visitado;

    for (const auto& vert : vs_)
        visitado[vert.first] = false;

    std::queue<int> f;

    f.push(v);

    std::cout << "Ordem de visitação em BFS:";

    while (!f.empty()) {
        int k = f.front();
        f.pop();

        if (!visitado[k]) {
            std::cout << " " << k;

            visitado[k] = true;

            for (const auto& adj : vs_[k]) {
                if (!visitado[adj.first])
                    f.push(adj.first);
            }
        }
    }

    std::cout << "\n";
}

std::map<int, int> Grafo::componentes()
{
    std::map<int, int> c;

    if (vs_.empty()) {
        std::cerr << "[" << __func__
                  << "()] Erro: grafo vazio (nenhum vértice)\n";
        return c;
    }

    for (const auto& v : vs_)
        c[v.first] = 0;

    std::stack<int> p;

    int cont = 0;

    for (const auto& v : vs_) {
        if (c[v.first] == 0) {
            cont++;
            p.push(v.first);

            while (!p.empty()) {
                int k = p.top();
                p.pop();

                if (c[k] == 0) {
                    c[k] = cont;

                    for (const auto& adj : vs_[k]) {
                        if (c[adj.first] == 0)
                            p.push(adj.first);
                    }
                }
            }
        }
    }

    return c;
}

std::pair<std::map<int, int>, std::map<int, int>> Grafo::caminhoMinimo(int v)
{
    std::map<int, int> dist, prev;

    if (vs_.size() < 2) {
        std::cerr << "[" << __func__
                  << "()] Erro: quantidade de vértices insuficiente (mín. 2)\n";
        return { dist, prev };
    }

    for (const auto& vert : vs_) {
        dist[vert.first] = std::numeric_limits<int>::max(); // "infinito"
        prev[vert.first] = -1;
    }

    dist[v] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compara> pq;

    pq.push({ 0, v });

    while (!pq.empty()) {
        int p = pq.top().second;
        pq.pop();

        for (const auto& adj : vs_[p]) {
            int q = adj.first, peso = adj.second;

            if (dist[q] > dist[p] + peso) {
                dist[q] = dist[p] + peso;
                pq.push({ dist[q], q });
                prev[q] = p;
            }
        }
    }

    return { dist, prev };
}
