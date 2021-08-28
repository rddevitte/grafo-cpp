/**
 * @file grafo.h
 * @brief Definição da classe Grafo e seus métodos
 */
#ifndef GRAFO_H
#define GRAFO_H

#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

template <typename V, typename Dist>
class Grafo {
public:
    /** Construtor do grafo */
    Grafo()
    {
    }

    /** Destrutor do grafo */
    ~Grafo()
    {
    }

    /**
     * Insere um vértice adjacente 'a' a um vértice 'v' da lista com distância 'dist'.
     * @param v O vértice
     * @param a O vértice adjacente
     * @param dist Distância entre 'v' e 'a'
     * @param bidir Indica se o vértice é bidirecional
     */
    void insereAdjacente(const V& v, const V& a, Dist dist, bool bidir = true);

    /**
     * Retorna o número (quantidade) de vértices do grafo.
     * @return a quantidade de vértices do grafo
     */
    int numVertices() const;

    /**
     * Retorna a lista de vértices do grafo
     * @return um vetor contendo os vértices do grafo
     */
    std::vector<V> getVertices() const;

    /**
     * Retorna a lista de vértices adjacentes a um vértice 'v'.
     * @return um vetor contendo os vértices adjacentes a 'v'
     */
    std::vector<std::pair<V, Dist>> getAdjacentes(const V& v) const;

    /**
     * Percorre o grafo e verifica se existem componentes (um vértice ou um
     * grupo de vértices) não conectados ao resto do grafo.
     * @return Um 'map' com os grupos de vértices e a lista de vértices que pertencem a cada grupo
     */
    std::map<int, std::vector<V>> getComponentes() const;

    /**
     * Executa o algoritmo de busca em largura no grafo.
     * @param v O vértice inicial a ser visitado
     * @param visita Uma 'função objeto' que 'visita' cada nodo do grafo
     */
    void buscaLargura(const V& v, std::function<void(V&)> visita);

    /**
     * Executa o algoritmo de busca em profundidade no grafo.
     * @param v O vértice inicial a ser visitado
     * @param visita Uma 'função objeto' que 'visita' cada nodo do grafo
     */
    void buscaProfundidade(const V& v, std::function<void(V&)> visita);

    /**
     * Executa o algoritmo do caminho mínimo (algoritmo de Dijkstra) no grafo.
     * @param v O vértice de partida
     * @return Um par contendo dois vetores: um de distâncias de 'v' até cada vértice
     *         e outro de vért. anteriores
     */
    std::pair<std::map<V, Dist>, std::map<V, V>> caminhoMinimo(const V& v) const;

    /**
     * Compara a distância de dois vértices representados por pares,
     * onde o primeiro elemento de cada par é o vértice, e o segundo a sua distância.
     */
    struct comparador {
        bool operator()(const std::pair<V, Dist>& lhs, const std::pair<V, Dist>& rhs) const
        {
            return lhs.second < rhs.second;
        }
    };

private:
    /**
     * 'Map' de vértices, contendo o vértice e sua lista ('vector')
     * de adjacências, cada um com sua distância do vértice
     */
    std::map<V, std::vector<std::pair<V, Dist>>> vs_;
};

template <typename V, typename Dist>
void Grafo<V, Dist>::insereAdjacente(const V& v, const V& a, Dist dist, bool bidir)
{
    vs_[v].push_back({ a, dist });

    if (bidir)
        vs_[a].push_back({ v, dist });
}

template <typename V, typename Dist>
int Grafo<V, Dist>::numVertices() const
{
    return static_cast<int>(vs_.size());
}

template <typename V, typename Dist>
std::vector<V> Grafo<V, Dist>::getVertices() const
{
    std::vector<V> verts;

    std::transform(vs_.begin(), vs_.end(), std::back_inserter(verts),
        [](std::pair<V, std::vector<std::pair<V, Dist>>> vs) { return vs.first; });

    return verts;
}

template <typename V, typename Dist>
std::vector<std::pair<V, Dist>> Grafo<V, Dist>::getAdjacentes(const V& v) const
{
    std::vector<std::pair<V, Dist>> adj;

    if (vs_.find(v) != vs_.end())
        adj = vs_.at(v);

    return adj;
}

template <typename V, typename Dist>
std::map<int, std::vector<V>> Grafo<V, Dist>::getComponentes() const
{
    std::map<int, std::vector<V>> comp;

    if (vs_.empty()) {
        return comp;
    }

    std::map<V, int> c;

    for (const auto& v : vs_)
        c[v.first] = 0;

    std::stack<V> p;

    int cont = 0;

    for (const auto& v : vs_) {
        if (c.at(v.first) == 0) {
            cont++;
            p.push(v.first);

            while (!p.empty()) {
                V k = p.top();
                p.pop();

                if (c.at(k) == 0) {
                    c[k] = cont;

                    for (const auto& adj : vs_.at(k))
                        if (c.at(adj.first) == 0)
                            p.push(adj.first);
                }
            }
        }
    }

    for (const auto& v : c)
        comp[v.second].push_back(v.first);

    return comp;
}

template <typename V, typename Dist>
void Grafo<V, Dist>::buscaLargura(const V& v, std::function<void(V&)> visita)
{
    if (vs_.find(v) == vs_.end())
        return;

    std::map<V, bool> visitado;

    std::queue<V> f;

    f.push(v);

    while (!f.empty()) {
        V k = f.front();
        f.pop();

        if (visitado.find(k) == visitado.end()) {
            visita(k);

            visitado[k] = true;

            for (const auto& adj : vs_.at(k))
                if (visitado.find(adj.first) == visitado.end())
                    f.push(adj.first);
        }
    }
}

template <typename V, typename Dist>
void Grafo<V, Dist>::buscaProfundidade(const V& v, std::function<void(V&)> visita)
{
    if (vs_.find(v) == vs_.end()) {
        return;
    }

    std::map<V, bool> visitado;

    std::stack<V> p;

    p.push(v);

    while (!p.empty()) {
        V k = p.top();
        p.pop();

        if (visitado.find(k) == visitado.end()) {
            visita(k);

            visitado[k] = true;

            for (const auto& adj : vs_.at(k))
                if (visitado.find(adj.first) == visitado.end())
                    p.push(adj.first);
        }
    }
}

template <typename V, typename Dist>
std::pair<std::map<V, Dist>, std::map<V, V>> Grafo<V, Dist>::caminhoMinimo(const V& v) const
{
    std::map<V, Dist> dist;
    std::map<V, V> prev;

    if (vs_.size() < 2) {
        return { dist, prev };
    }

    for (const auto& vert : vs_) {
        dist[vert.first] = std::numeric_limits<Dist>::max(); // "infinito"
        prev[vert.first] = vert.first;
    }

    dist[v] = static_cast<Dist>(0);

    std::priority_queue<std::pair<V, Dist>, std::vector<std::pair<V, Dist>>, Grafo::comparador> pq;

    pq.push({ v, static_cast<Dist>(0) });

    while (!pq.empty()) {
        V p = pq.top().first;
        pq.pop();

        for (const auto& adj : vs_.at(p)) {
            V q = adj.first;
            Dist peso = adj.second;

            if (dist.at(q) > dist.at(p) + peso) {
                dist[q] = dist.at(p) + peso;
                pq.push({ q, dist.at(q) });
                prev[q] = p;
            }
        }
    }

    return { dist, prev };
}

#endif /* GRAFO_H */
