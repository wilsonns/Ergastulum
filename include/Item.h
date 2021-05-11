#ifndef ITEM_H
#define ITEM_H
#include <main.h>

class Item
{
public:
	Item(std::string nome,std::string tipo,std::string descricao,int simbolo,TCODColor cor,int peso);//CTOR
	virtual ~Item();//DTOR

	Entidade* portador;//a entidade que está segurando esse item em seu inventário
	
	std::string nome;
	std::string tipo;
	std::string descricao;
	int simbolo;
	TCODColor cor;
	

	//BOOLS
	bool eArma;//se o item pode ser usado como arma
		bool eRanged;//se o item pode fazer ataques à distancia
	bool eArmadura;//se o item pode ser usado como armadura

	//INTS
	int cargas;//se o item tem uma quantidade de cargas
	int maxCargas;//se o item tem uma quantidade maxima de cargas
	int dano;//dano causado pelo objeto se usado como arma
	int blindagem;//a quantidade de dano tankado pelo item se usado como armadura
	int peso;//o peso do item para caber no inventario do personagem

	bool pegar(Entidade* portador);//se conseguir pegar o item, retorna verdadeiro
	bool usar();//função virtual para usar o item, veja a referencia de cada classe filha
	bool soltar();//devolver o item ao chão
	bool equipar();//equipa um item no slot correspondente
};
#endif // ITEM_H