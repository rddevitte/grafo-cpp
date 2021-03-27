#ifndef PILHA_H
#define PILHA_H

class NodoPilha
{
public:
	int n;
	NodoPilha *abaixo;
	NodoPilha(int n, NodoPilha *abaixo);
	~NodoPilha();
};

class Pilha
{
private:
	int tam;
	NodoPilha *topo;
public:
	Pilha();
	int  tamanho();
	bool vazia();
	void push(int n);
	int  pop();
	~Pilha();
};

#endif /* PILHA_H */
