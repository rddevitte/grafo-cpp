#ifndef LISTA_H
#define LISTA_H

class Lista
{
public:
	int v;
	int dist;
	Lista *prox;
	Lista(int v, int dist);
	~Lista();
};

#endif /* LISTA_H */
