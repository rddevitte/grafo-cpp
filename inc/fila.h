#ifndef FILA_H
#define FILA_H

class NodoFila {
public:
    int n_;
    NodoFila* ant_;
    explicit NodoFila(int n);
    ~NodoFila();
};

class Fila {
private:
    int tam_;
    NodoFila *frente_, *atras_;

public:
    Fila();
    bool vazia() const;
    void insere(int i);
    int retira();
    ~Fila();
};

#endif /* FILA_H */
