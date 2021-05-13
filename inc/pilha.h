#ifndef PILHA_H
#define PILHA_H

class NodoPilha {
public:
    int n_;
    NodoPilha* abaixo_;
    NodoPilha(int n, NodoPilha* abaixo);
    ~NodoPilha();
};

class Pilha {
private:
    int tam_;
    NodoPilha* topo_;

public:
    Pilha();
    bool vazia() const;
    void push(int n);
    int pop();
    ~Pilha();
};

#endif /* PILHA_H */
