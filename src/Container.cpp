#include "Container.h"

Container::Container(int tamanho)
{
	this->tamanho = tamanho;
}

Container::~Container()
{
	inventario.clear();
}


bool Container::contemArma(Entidade* portador)
{
	if (portador->container->inventario.size() > 0)
	{
		for (Entidade** it = portador->container->inventario.begin(); it != portador->container->inventario.end();it++)
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
	inventario.push(entidade);
	return true;
}

void Container::remover(Entidade* entidade)
{
	inventario.remove(entidade);
}