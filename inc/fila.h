#ifndef FILA_H
#define FILA_H

class Fila {
public:
    class NodoFila {
    public:
        int n_;
        NodoFila* ant_;
        explicit NodoFila(int n);
        ~NodoFila();
    };

    Fila();
    bool vazia() const;
    void insere(int i);
    int retira();
    ~Fila();

private:
    int tam_;
    NodoFila *frente_, *atras_;
};

#endif /* FILA_H */
