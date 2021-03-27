#ifndef VERTICE_H
#define VERTICE_H

#include "lista.h"

class Vertice
{
public:
	Lista *adj;
	Vertice();
	void insAdj(int a, int dist);
	~Vertice();
};

#endif /* VERTICE_H */
