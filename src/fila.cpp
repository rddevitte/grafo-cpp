#include "../inc/fila.h"
#include <iostream>

Fila::NodoFila::NodoFila(int n)
    : n_(n)
    , ant_(nullptr)
{
}

Fila::NodoFila::~NodoFila()
{
}

Fila::Fila()
    : tam_(0)
    , frente_(nullptr)
    , atras_(nullptr)
{
}

Fila::~Fila()
{
    while (tam_ > 0) {
        NodoFila* aux = frente_;
        frente_ = frente_->ant_;
        delete aux;
        tam_--;
    }

    atras_ = nullptr;
}

bool Fila::vazia() const
{
    return (tam_ == 0);
}

void Fila::insere(int i)
{
    NodoFila* novo;

    novo = new NodoFila(i);

    if (tam_ == 0)
        frente_ = atras_ = novo;
    else {
        atras_->ant_ = novo;
        atras_ = novo;
    }

    tam_++;

    return;
}

int Fila::retira()
{
    NodoFila* aux;
    int n;

    if (vazia()) {
        std::cerr << "[" << __func__ << "()] Erro: fila vazia\n";
        return -1;
    }

    n = frente_->n_;

    aux = frente_;
    frente_ = frente_->ant_;
    delete aux;

    tam_--;

    if (tam_ == 0)
        atras_ = nullptr;

    return n;
}
