#ifndef CONTAINER_H
#define CONTAINER_H
#include <main.h>

class Container
{
	
public:
	int tamanho;//tamano maximo do vetor inventario
	int pesoAtual;//pesso atual sendo carregado pelo item
	std::vector<Item*> inventario;//o vetor inventario

	//Os slots de Equipamento
	Item* armadura;
	Item* arma;
	Item* escudo;
	
	Container(int tamanho);//ctor
	~Container();//dtor

	bool estaCheio();//retorna true se o vetor iventario estiver cheio

	bool adcionar(Item* item);//adcionar um item ao inventário, retorna true se conseguir, false se não
	void remover(Item* item);//remover um item do inventário
};

#endif // CONTAINER_H