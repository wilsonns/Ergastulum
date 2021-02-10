#include "Container.h"

Container::Container(int tamanho)
{
	this->tamanho = tamanho;
}

Container::~Container()
{
	inventario.clear();
}

bool Container::adcionar(Entidade* entidade)
{
	if (tamanho > 0 && inventario.size() >= tamanho)
	{
		//inventário cheio
		return false;
	}
	inventario.push_back(entidade);
	return true;
}

void Container::remover(Entidade* entidade)
{
	for (unsigned short int i = 0; i < inventario.size(); i++)
	{
		if (inventario[i] == entidade)
		{
			inventario.erase(inventario.begin() + i);
		}
	}
}