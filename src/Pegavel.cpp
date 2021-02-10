#include "Pegavel.h"

Pegavel::Pegavel()
{
	//ctor
}

Pegavel::~Pegavel()
{
	//dtor
}

bool Pegavel::pegar(Entidade* owner, Entidade* portador)
{
	if (portador->container && portador->container->adcionar(owner))
	{
		for (unsigned short int i = 0; i < engine.entidades.size();i++)
		{
			if(engine.entidades[i] == owner)
			{
				engine.entidades.erase(engine.entidades.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool Pegavel::usar(Entidade* owner, Entidade* portador)
{
	if (portador->container)
	{
		portador->container->remover(owner);
		delete owner;
		return true;
	}
	return false;
}

Curador::Curador(float valor)
{
	this->valor = valor;
}

bool Curador::usar(Entidade* owner, Entidade* portador)
{
	if (portador->destrutivel)
	{
		float valorCurado = portador->destrutivel->curar(valor);
		if (valorCurado > 0)
		{
			return Pegavel::usar(owner, portador);
		}
	}
	return false;
}
