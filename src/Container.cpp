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
	inventario.push(entidade);
	return true;
}

void Container::remover(Entidade* entidade)
{
	inventario.remove(entidade);
}