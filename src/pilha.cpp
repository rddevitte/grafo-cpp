#include <iostream>
#include "../inc/pilha.h"

using namespace std;

NodoPilha::NodoPilha(int n, NodoPilha *abaixo)
{
	this->n = n;
	this->abaixo = abaixo;
}

NodoPilha::~NodoPilha()
{
}

Pilha::Pilha()
{
	tam = 0;
	topo = NULL;
}

Pilha::~Pilha()
{
	while (tam > 0)
	{
		NodoPilha *aux = topo;
		topo = topo->abaixo;
		delete aux;
		tam--;
	}
}

bool Pilha::vazia() const
{
	if (tam == 0)
		return true;

	return false;
}

void Pilha::push(int n)
{
	NodoPilha *novo;

	novo = new NodoPilha(n, topo);
	topo = novo;
	tam++;

	return;
}

int Pilha::pop()
{
	NodoPilha *aux;
	int n;

	if (tam == 0)
	{
		cerr << "[" << __func__ << "()] Erro: pilha vazia\n";
		return -1;
	}

	n = topo->n;

	aux = topo;
	topo = topo->abaixo;
	delete aux;

	tam--;

	return n;
}
