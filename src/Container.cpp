#include "Container.h"

Container::Container(int tamanho)
{
	this->tamanho = tamanho;
	this->pesoAtual = 0;
	armadura = arma = escudo = NULL;

}

Container::~Container()
{
	inventario.clear();
}


bool Container::estaCheio()
{
	if (tamanho > 0 && inventario.size() >= tamanho)
	{
		return true;
	}
	return false;
}

bool Container::adcionar(Item* item)
{
	if (estaCheio() || item->peso+pesoAtual > tamanho)
	{
		//inventário cheio
		return false;
	}
	pesoAtual += item->peso;
	inventario.push_back(item);
	return true;
}

void Container::remover(Item* item)
{
	pesoAtual -= item->peso;
	inventario.erase(std::find(inventario.begin(), inventario.end(), item));
}
