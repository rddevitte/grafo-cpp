#ifndef LISTAPRIOR_H
#define LISTAPRIOR_H

#define INF 0x3FFFFFFF

class ListaPrior {
public:
    class NodoListaPrior {
    public:
        int v_;
        int dist_; // a chave de ordenação na lista
        NodoListaPrior* prox_;
        NodoListaPrior(int v, int dist);
        ~NodoListaPrior();
    };

    ListaPrior(int i, int tam);
    ListaPrior(const ListaPrior&);
    ListaPrior& operator=(const ListaPrior&);
    bool vazia() const;
    void imprime() const;
    int extraiMin();
    void decresceChave(int v, int dist);
    ~ListaPrior();

private:
    NodoListaPrior* min_;
    int i_; // vértice inicial
    int tam_; // tamanho da lista
};

#endif /* LISTAPRIOR_H */
