#include "Item.h"

Item::Item(std::string nome, int simbolo, TCODColor cor, int peso)
{
	this->nome = nome;
	this->simbolo = simbolo;
	this->cor = cor;
	this->peso = peso;
	//ctor
}

Item::~Item()
{
	//dtor
}

bool Item::pegar(Entidade* portador)
{
	if (portador->container && portador->container->adcionar(this))
	{
		this->portador = portador;
		return true;
	}
	return false;
}

bool Item::usar()
{
	if (portador->container)
	{
		portador->container->remover(this);
		this->portador = NULL;
		return true;
	}
	return false;
}

bool Item::soltar()
{
	if (portador->container)
	{
		engine.mapa->adcionarItem(portador->x, portador->y, this->simbolo,this->nome,0,this->cor,this->peso);
		portador->container->remover(this);
		return true;
	}
	return false;
}
