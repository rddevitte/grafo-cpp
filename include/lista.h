#ifndef LISTA_H
#define LISTA_H

class Lista {
public:
    int v_;
    int dist_;
    Lista* prox_;
    Lista(int v, int dist);
    ~Lista();
};

#endif /* LISTA_H */
