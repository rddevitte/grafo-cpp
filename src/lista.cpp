#include <iostream>
#include "../inc/lista.h"

Lista::Lista(int v, int dist)
{
	this->v = v;
	this->dist = dist;
	prox = NULL;
}

Lista::~Lista()
{
}
