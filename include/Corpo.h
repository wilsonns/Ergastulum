#ifndef CORPO_H
#define CORPO_H

#include<main.h>

class Parte
{
public:
	Parte();
	~Parte();
	int getTamanho();
	int getPV();
	void setPv(int PV);
private:
	Parte* pai;
	int tamanho;
	int PVmax;
	int PV;
	std::vector<Parte*> filhos;
};

#endif // CORPO_H
