#include "vertice.h"
#include "lista.h"
#include <iostream>

Vertice::Vertice()
    : adj_(nullptr)
{
}

void Vertice::insAdj(int a, int dist)
{
    Lista* aux;

    if (adj_ == nullptr)
        adj_ = new Lista(a, dist);
    else {
        aux = adj_;

        while (aux->prox_ != nullptr && aux->v_ != a)
            aux = aux->prox_;

        if (aux->v_ == a) {
            std::cerr << "[" << __func__
                      << "()] Erro: vértice " << a << " adjacente a "
                      << aux->v_ << " já existe\n";

            return;
        }

        aux->prox_ = new Lista(a, dist);
    }

    return;
}

Vertice::~Vertice()
{
    Lista* aux;

    while (adj_ != nullptr) {
        aux = adj_->prox_;
        delete adj_;
        adj_ = aux;
    }
}
