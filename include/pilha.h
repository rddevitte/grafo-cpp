#ifndef PILHA_H
#define PILHA_H

class Pilha {
public:
    class NodoPilha {
    public:
        int n_;
        NodoPilha* abaixo_;
        NodoPilha(int n, NodoPilha* abaixo);
        ~NodoPilha();
    };

    Pilha();
    bool vazia() const;
    void push(int n);
    int pop();
    ~Pilha();

private:
    int tam_;
    NodoPilha* topo_;
};

#endif /* PILHA_H */
