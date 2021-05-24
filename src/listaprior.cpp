#include "../inc/listaprior.h"
#include <iostream>

ListaPrior::NodoListaPrior::NodoListaPrior(int v, int dist)
    : v_(v)
    , dist_(dist)
    , prox_(nullptr)
{
}

ListaPrior::NodoListaPrior::~NodoListaPrior()
{
}

ListaPrior::ListaPrior(int i, int tam)
    : tam_(tam)
{
    if (i < 0 || i > 1) {
        std::cerr << "[" << __func__
                  << "()] i deve ser 0 ou 1, assumindo 0\n";
        i_ = 0;
    } else {
        i_ = i;
    }

    min_ = new NodoListaPrior(i_, INF);

    NodoListaPrior* aux = min_;

    for (int n = i_ + 1; n < tam_ + i_; n++) {
        aux->prox_ = new NodoListaPrior(n, INF);
        aux = aux->prox_;
    }
}

ListaPrior::ListaPrior(const ListaPrior& l)
{
    i_ = l.i_;
    tam_ = l.tam_;

    min_ = new NodoListaPrior(i_, INF);

    NodoListaPrior* aux = min_;

    for (int n = i_ + 1; n < tam_ + i_; n++) {
        aux->prox_ = new NodoListaPrior(n, INF);
        aux = aux->prox_;
    }
}

ListaPrior& ListaPrior::operator=(const ListaPrior& l)
{
    if (&l != this) {
        delete min_;

        i_ = l.i_;
        tam_ = l.tam_;

        min_ = new NodoListaPrior(i_, INF);

        NodoListaPrior* aux = min_;

        for (int n = i_ + 1; n < tam_ + i_; n++) {
            aux->prox_ = new NodoListaPrior(n, INF);
            aux = aux->prox_;
        }
    }

    return *this;
}

bool ListaPrior::vazia() const
{
    return (tam_ == 0);
}

void ListaPrior::imprime() const
{
    NodoListaPrior* aux;

    if (tam_ == 0) {
        std::cerr << "[" << __func__ << "()] Erro: lista prior. vazia\n";
        return;
    }

    aux = min_;

    std::cout << "Lista prior. de tam. " << tam_ << ":";

    while (aux != nullptr) {
        std::cout << " " << aux->v_ << "(";

        if (aux->dist_ == INF)
            std::cout << "Inf";
        else
            std::cout << aux->dist_;

        std::cout << ")";

        aux = aux->prox_;
    }

    std::cout << "\n";

    return;
}

int ListaPrior::extraiMin()
{
    NodoListaPrior* aux;
    int m;

    if (min_ == nullptr) {
        std::cerr << "[" << __func__ << "()] Erro: lista vazia\n";
        return -1;
    }

    m = min_->v_;

    aux = min_;
    min_ = min_->prox_;
    delete aux;

    tam_--;

    return m;
}

void ListaPrior::decresceChave(int v, int dist)
{
    NodoListaPrior *aux, *ant;

    if (v < i_) {
        std::cerr << "[" << __func__
                  << "()] Erro: vértice " << v << " inválido\n";
        return;
    }

    /* Se chave alvo está no início da lista, apenas muda chave (dist) */
    if (v == min_->v_) {
        min_->dist_ = dist;
    }
    /* Senão, percorre a lista e refaz os apontamentos */
    else {
        ant = min_;
        aux = min_->prox_;

        while (aux != nullptr && v != aux->v_) {
            ant = aux;
            aux = aux->prox_;
        }

        if (aux == nullptr) {
            std::cerr << "[" << __func__
                      << "()] Vértice " << v << " não encontrado\n";
            return;
        }

        aux->dist_ = dist;

        /* Reapontamentos */

        /* Caso 1: nova chave do vértice alvo é menor ou igual
		   que a chave do vértice inicial (min) */
        if (aux->dist_ <= min_->dist_) {
            ant->prox_ = aux->prox_;
            aux->prox_ = min_;
            min_ = aux;
        }
        /* Caso 2: nova chave é igual ou maior que a anterior e
		   não há vértices à frente -> não necessita mover ponteiros */
        else if (aux->dist_ >= ant->dist_) {
            /* Prossegue (sai do if()) */
        }
        /* Caso 3: nova chave é igual ou maior que a anterior e menor
		   ou igual ao vértice à frente -> mesmo do caso anterior */
        else if (aux->dist_ >= ant->dist_ && aux->dist_ <= aux->prox_->dist_) {
            /* Prossegue (sai do if()) */
        }
        /* Caso 4: nova chave é menor que a anterior
		   -> necessita movimentação */
        else {
            ant->prox_ = aux->prox_;
            ant = min_;

            while (ant->prox_ != nullptr && ant->prox_->dist_ <= aux->dist_)
                ant = ant->prox_;

            aux->prox_ = ant->prox_;
            ant->prox_ = aux;
        }
    }

    return;
}

ListaPrior::~ListaPrior()
{
    while (min_ != nullptr) {
        NodoListaPrior* aux = min_;
        min_ = min_->prox_;
        delete aux;
        tam_--;
    }
}
