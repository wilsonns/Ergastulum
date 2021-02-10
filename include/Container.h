#ifndef CONTAINER_H
#define CONTAINER_H
#include <main.h>

class Container
{
	
public:
	int tamanho;//tamano maximo do vetor inventario
	std::vector<Entidade*> inventario;//o vetor inventario

	Container(int tamanho);//ctor
	~Container();//dtor

	bool adcionar(Entidade* entidade);//adcionar um item ao inventário, retorna true se conseguir, false se não
	void remover(Entidade* entidade);//remover um item do inventário

};

#endif // CONTAINER_H