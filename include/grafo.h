#ifndef GRAFO_H
#define GRAFO_H

#include "vertice.h"

/* Infinito definido como a metade do maior número inteiro de 32 bits com sinal
   (p/ algoritmo de Dijkstra) */
#define INF 0x3FFFFFFF

class Grafo {
private:
    /** Vértice inicial */
    int i_;
    /** Número de vértices */
    int n_;
    /** Lista de vértices */
    Vertice* vs_;

public:
    /**
     * Construtor do grafo.
     * @param i Vértice inicial (deve ser 0 ou 1).
     * Se i = 0, os vértices são numerados de 0 a n - 1.
     * Se i = 1, os vértices são numerados de 1 a n.
     * @param n Número de vértices
     */
    Grafo(int i, int n);

    /**
     * Copy constructor.
     * @param g O grafo a ser "copiado"
     */
    Grafo(const Grafo&);

    /**
     * "Sobrecarrega" o operador de igualdade (=).
     * @param g O grafo cujos atributos são copiados para outro grafo
     */
    Grafo& operator=(const Grafo&);

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
    void insAdj(int v, int a, int dist, bool bidir);

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
    int* componentes();

    /**
     * Executa o algoritmo do caminho mínimo (algoritmo de Dijkstra) no grafo.
     * @param v O vértice de partida
     * @param dist O vetor de distâncias
     * @param prev O vetor de vértices anteriores
     */
    void caminhoMinimo(int v, int** dist, int** prev);

    /**
     * Destrutor do grafo.
     */
    ~Grafo();
};

#endif /* GRAFO_H */
