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

bool Pegavel::soltar(Entidade* self, Entidade* portador)
{
	if (portador->container)
	{
		engine.mapa->adcionarItem(portador->x, portador->y, self->simbolo, self->pegavel->tipo, self->nome, 5, self->cor);
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

Arma::Arma(int dano)
{
	this->dano = dano;
}

bool Arma::usar(Entidade* self, Entidade* portador)
{
	if (portador->arma == NULL)
	{
		equipar(self, portador);
		return true;
	}
	else if (portador->arma == self)
	{
		desequipar(self, portador);
		return true;
	}
	return false;
}

void Arma::equipar(Entidade* self, Entidade* portador)
{
	if (portador->arma == NULL)
	{
		portador->arma = self;
		portador->atacador->forca += dano;
		engine.gui->mensagem(TCOD_white, "%s equipa %s!", portador->nome, self->nome);
	}
	else if (portador->arma != NULL)
	{
		engine.gui->mensagem(TCOD_white, "%s ja esta empunhando uma arma!", portador->nome);
		return;
	}
}

void Arma::desequipar(Entidade* self, Entidade* portador)
{
	if (portador->arma != NULL)
	{
		portador->atacador->forca -= dano;
		portador->arma = NULL;
		engine.gui->mensagem(TCOD_white, "%s desequipa %s!", portador->nome, self->nome);
	}
	else if (portador->arma == NULL)
	{
		engine.gui->mensagem(TCOD_white, "%s ja nao tem nenhuma uma arma!", portador->nome);
		return;
	}
}