#include "../inc/pilha.h"
#include <iostream>

NodoPilha::NodoPilha(int n, NodoPilha* abaixo)
    : n_(n)
    , abaixo_(abaixo)
{
}

NodoPilha::~NodoPilha()
{
}

Pilha::Pilha()
    : tam_(0)
    , topo_(nullptr)
{
}

Pilha::~Pilha()
{
    while (tam_ > 0) {
        NodoPilha* aux = topo_;
        topo_ = topo_->abaixo_;
        delete aux;
        tam_--;
    }
}

bool Pilha::vazia() const
{
    return (tam_ == 0);
}

void Pilha::push(int n)
{
    NodoPilha* novo;

    novo = new NodoPilha(n, topo_);
    topo_ = novo;
    tam_++;

    return;
}

int Pilha::pop()
{
    NodoPilha* aux;
    int n;

    if (tam_ == 0) {
        std::cerr << "[" << __func__ << "()] Erro: pilha vazia\n";
        return -1;
    }

    n = topo_->n_;

    aux = topo_;
    topo_ = topo_->abaixo_;
    delete aux;

    tam_--;

    return n;
}
