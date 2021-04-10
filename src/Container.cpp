#include "Container.h"

Container::Container(int tamanho)
{
	this->tamanho = tamanho;
	//Equips
	armadura = arma = escudo = NULL;

}

Container::~Container()
{
	inventario.clear();
}


bool Container::contemArma(Entidade* portador)
{
	if (portador->container->inventario.size() > 0)
	{
		for (std::vector<Entidade*>::iterator it = inventario.begin(); it != inventario.end();it++)
		{
			Entidade* entidade = *it;
			if (entidade->pegavel->tipo == 2)
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
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
	for (std::vector<Entidade*>::iterator it = inventario.begin();it != inventario.end();it++)
	{
		Entidade* comparavel = *it;

		if(comparavel == entidade)
		{
			inventario.erase(it);
		}
	}
}
