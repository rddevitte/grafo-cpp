#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <utility>
#include <vector>

/* Compara a distância de dois vértices representados em pares.
   O primeiro elemento de cada par é o vértice, o segundo a sua distância. */
struct compara {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const
    {
        return lhs.second < rhs.second;
    }
};

class Grafo {
public:
    /**
     * Construtor do grafo.
     */
    Grafo();

    /**
     * Retorna o número de vértices do grafo.
     * @return Número de vértices do grafo
     */
    int numVerts() const;

    /**
     * Insere um vértice adjacente 'a' a um vértice 'v' da lista
     * com distância 'dist'.
     * @param v O vértice
     * @param a O vértice adjacente
     * @param dist Distância entre 'v' e 'a'
     * @param bidir Indica se o vértice é bidirecional
     */
    void insAdj(int v, int a, int dist, bool bidir = true);

    /**
     * Imprime os vértices do grafo, seus adjacentes e suas distâncias.
     */
    void imprime() const;

    /**
     * Executa o algoritmo de busca em profundidade no grafo.
     * @param v O vértice inicial a ser visitado
     */
    void buscaProfundidade(int v);

    /**
     * Executa o algoritmo de busca em largura no grafo.
     * @param v O vértice inicial a ser visitado
     */
    void buscaLargura(int v);

    /**
     * Percorre o grafo e verifica se existem componentes (um vértice ou um
     * grupo de vértices) não conectados ao resto do grafo.
     * @return Vetor com a lista de componentes (grupos)
     */
    std::map<int, int> componentes();

    /**
     * Executa o algoritmo do caminho mínimo (algoritmo de Dijkstra) no grafo.
     * @param v O vértice de partida
     * @return Um par contendo dois vetores: um de distâncias até 'v', outro de vért. anteriores
     */
    std::pair<std::map<int, int>, std::map<int, int>> caminhoMinimo(int v);

    /**
     * Destrutor do grafo.
     */
    ~Grafo();

private:
    /**
     * 'Map' de vértices, contendo o vértice e sua lista ('vector')
     * de adjacências, cada um com sua distância do vértice
     */
    std::map<int, std::vector<std::pair<int, int>>> vs_;
};

#endif /* GRAFO_H */
