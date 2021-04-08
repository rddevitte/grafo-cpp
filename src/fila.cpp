#include <iostream>
#include "../inc/fila.h"

using namespace std;

NodoFila::NodoFila(int _n) : n(_n)
{
	ant = NULL;
}

NodoFila::~NodoFila()
{
}

Fila::Fila()
{
	tam = 0;
	frente = atras = NULL;
}

Fila::~Fila()
{
	while (tam > 0)
	{
		NodoFila *aux = frente;
		frente = frente->ant;
		delete aux;
		tam--;
	}

	atras = NULL;
}

bool Fila::vazia() const
{
	if (tam == 0)
		return true;

	return false;
}

void Fila::insere(int i)
{
	NodoFila *novo;

	novo = new NodoFila(i);

	if (tam == 0)
		frente = atras = novo;
	else
	{
		atras->ant = novo;
		atras = novo;
	}

	tam++;

	return;
}

int Fila::retira()
{
	NodoFila *aux;
	int n;

	if (vazia())
	{
		cerr << "[" << __func__ << "()] Erro: fila vazia\n";
		return -1;
	}

	n = frente->n;

	aux = frente;
	frente = frente->ant;
	delete aux;

	tam--;

	if (tam == 0)
		atras = NULL;

	return n;
}
