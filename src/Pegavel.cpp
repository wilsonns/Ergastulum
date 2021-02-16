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
		engine.entidades.remove(self);
		return true;
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
		int valorCurado = portador->destrutivel->curar(valor);
		if (valorCurado > 0)
		{
			return Pegavel::usar(self, portador);
		}
	}
	return false;
}
