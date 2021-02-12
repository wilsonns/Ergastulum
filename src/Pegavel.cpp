#include "Pegavel.h"

Pegavel::Pegavel()
{
	//ctor
}

Pegavel::~Pegavel()
{
	//dtor
}

bool Pegavel::pegar(Entidade* self, Entidade* portador)
{
	if (portador->container && portador->container->adcionar(self))
	{
		for (unsigned short int i = 0; i < engine.entidades.size();i++)
		{
			if(engine.entidades[i] == self)
			{
				engine.entidades.erase(engine.entidades.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool Pegavel::usar(Entidade* self, Entidade* portador)
{
	if (portador->container)
	{
		portador->container->remover(self);
		delete self;
		return true;
	}
	return false;
}

Curador::Curador(float valor)
{
	this->valor = valor;
}

bool Curador::usar(Entidade* self, Entidade* portador)
{
	if (portador->destrutivel)
	{
		float valorCurado = portador->destrutivel->curar(valor);
		if (valorCurado > 0)
		{
			return Pegavel::usar(self, portador);
		}
	}
	return false;
}
