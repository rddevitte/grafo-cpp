#ifndef FILA_H
#define FILA_H

class NodoFila
{
public:
	int n;
	NodoFila *ant;
	NodoFila(int n);
	~NodoFila();
};

class Fila
{
private:
	int tam;
	NodoFila *frente, *atras;
public:
	Fila();
	bool vazia();
	void insere(int i);
	int  retira();
	~Fila();
};

#endif /* FILA_H */
