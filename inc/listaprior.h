#ifndef LISTAPRIOR_H
#define LISTAPRIOR_H

#define INF 0x3FFFFFFF

class NodoListaPrior
{
public:
	int v;
	int dist; // a chave de ordenação na lista
	NodoListaPrior *prox;
	NodoListaPrior(int v, int dist);
	~NodoListaPrior();
};

class ListaPrior
{
private:
	NodoListaPrior *min;
	int i; // vértice inicial
	int tam; // tamanho da lista
public:
	ListaPrior(int i, int tam);
	bool vazia() const;
	void imprime() const;
	int  extraiMin();
	void decresceChave(int v, int dist);
	~ListaPrior();
};

#endif /* LISTAPRIOR_H */
