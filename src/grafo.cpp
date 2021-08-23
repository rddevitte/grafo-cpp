#include "grafo.h"
#include "fila.h"
#include "lista.h"
#include "listaprior.h"
#include "pilha.h"
#include <iostream>

Grafo::Grafo(int i, int n)
    : n_(n)
{
    if (i < 0 || i > 1) {
        std::cerr << "i deve ser 0 ou 1, assumindo 0\n";
        i_ = 0;
    } else
        i_ = i;

    vs_ = new Vertice[n_ + 1];
}

Grafo::Grafo(const Grafo& g)
{
    i_ = g.i_;
    n_ = g.n_;

    vs_ = new Vertice[n_ + 1];

    for (int x = 0; x < n_; x++)
        this->vs_[x] = g.vs_[x];
}

Grafo& Grafo::operator=(const Grafo& g)
{
    if (&g != this) {
        delete[] vs_;

        i_ = g.i_;
        n_ = g.n_;

        vs_ = new Vertice[n_ + 1];

        for (int x = 0; x < n_; x++)
            vs_[x] = g.vs_[x];
    }

    return *this;
}

Grafo::~Grafo()
{
    delete[] vs_;
}

int Grafo::numVerts() const
{
    return n_;
}

void Grafo::insAdj(int v, int a, int dist, bool bidir)
{
    if (v < 0 || v > n_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vértice " << v << " inválido\n";
        return;
    }

    if (a < 0 || a > n_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vértice adjacente " << a << " inválido\n";
        return;
    }

    vs_[v].insAdj(a, dist);

    if (bidir)
        vs_[a].insAdj(v, dist);

    return;
}

void Grafo::imprime() const
{
    Lista* aux;
    int v;

    std::cout << "Número de vértices: " << n_ << "\n";

    for (v = i_; v < n_ + i_; v++) {
        std::cout << "Adjacentes a " << v << ":";

        if (vs_[v].adj_ == nullptr)
            std::cout << " nenhum";
        else {
            aux = vs_[v].adj_;

            while (aux != nullptr) {
                std::cout << " " << aux->v_ << "(" << aux->dist_ << ")";
                aux = aux->prox_;
            }
        }

        std::cout << "\n";
    }
}

void Grafo::buscaProfundidade(int v)
{
    Pilha p;
    bool* visitado;
    int k;
    Lista* aux;

    if (v < i_ || v > (n_ - 1) + i_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vért. ini. " << v << " inválido\n";
        return;
    }

    visitado = new bool[n_ + 1];

    for (k = 0; k <= n_; k++)
        visitado[k] = false;

    p.push(v);

    std::cout << "Ordem de visitação em DFS:";

    while (!p.vazia()) {
        k = p.pop();

        if (!visitado[k]) {
            std::cout << " " << k;
            visitado[k] = true;

            aux = vs_[k].adj_;

            while (aux != nullptr) {
                if (!visitado[aux->v_])
                    p.push(aux->v_);

                aux = aux->prox_;
            }
        }
    }

    std::cout << "\n";

    delete[] visitado;

    return;
}

void Grafo::buscaLargura(int v)
{
    Fila f;
    bool* visitado;
    int k;
    Lista* aux;

    if (v < i_ || v > (n_ - 1) + i_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vért. ini. " << v << " inválido\n";
        return;
    }

    visitado = new bool[n_ + 1];

    for (k = 0; k <= n_; k++)
        visitado[k] = false;

    f.insere(v);

    std::cout << "Ordem de visitação em BFS:";

    while (!f.vazia()) {
        k = f.retira();

        if (!visitado[k]) {
            std::cout << " " << k;
            visitado[k] = true;

            aux = vs_[k].adj_;

            while (aux != nullptr) {
                if (!visitado[aux->v_])
                    f.insere(aux->v_);

                aux = aux->prox_;
            }
        }
    }

    std::cout << "\n";

    delete[] visitado;

    return;
}

int* Grafo::componentes()
{
    Pilha p;
    int *c, v, k, cont;
    Lista* aux;

    c = new int[n_ + 1];

    for (v = 0; v <= n_; v++)
        c[v] = 0;

    cont = 0;

    for (v = i_; v < n_ + i_; v++) {
        if (c[v] == 0) {
            cont++;
            p.push(v);

            while (!p.vazia()) {
                k = p.pop();

                if (c[k] == 0) {
                    c[k] = cont;

                    aux = vs_[k].adj_;

                    while (aux != nullptr) {
                        if (c[aux->v_] == 0)
                            p.push(aux->v_);

                        aux = aux->prox_;
                    }
                }
            }
        }
    }

    return c;
}

void Grafo::caminhoMinimo(int v, int** dist, int** prev)
{
    ListaPrior lp(i_, n_);
    Lista* aux;
    int k, q, peso;

    if (v < i_ || v > (n_ - 1) + i_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vért. ini. " << v << " inválido\n";
        return;
    }

    if (*dist == nullptr)
        *dist = new int[n_ + 1];

    if (*prev == nullptr)
        *prev = new int[n_ + 1];

    for (k = 0; k <= n_; k++) {
        (*dist)[k] = INF;
        (*prev)[k] = -1;
    }

    (*dist)[v] = 0;
    lp.decresceChave(v, 0); // vértice inicial

    while (!lp.vazia()) {
        int p = lp.extraiMin();

        aux = vs_[p].adj_;

        while (aux != nullptr) {
            q = aux->v_;
            peso = aux->dist_;

            if ((*dist)[q] > (*dist)[p] + peso) {
                (*dist)[q] = (*dist)[p] + peso;
                lp.decresceChave(q, (*dist)[q]);
                (*prev)[q] = p;
            }

            aux = aux->prox_;
        }
    }

    return;
}
