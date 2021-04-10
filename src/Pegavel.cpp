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
		std::vector<Entidade*>::iterator it = std::find(engine.entidades.begin(), engine.entidades.end(), self);
		if (*it == self)
		{
			engine.entidades.erase(it);
			return true;
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

bool Pegavel::soltar(Entidade* self, Entidade* portador)
{
	if (portador->container)
	{
		//engine.mapa->adcionarItem(portador->x, portador->y, self->simbolo, self->pegavel->tipo, self->nome, 5, self->cor);
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
//ARMA
Arma::Arma(int dano)
{
	this->dano = dano;
}

bool Arma::usar(Entidade* self, Entidade* portador)
{
	if (portador->container->arma == NULL)
	{
		equipar(self, portador);
		return true;
	}
	else if (portador->container->arma == self)
	{
		desequipar(self, portador);
		return true;
	}
	return false;
}

void Arma::equipar(Entidade* self, Entidade* portador)
{
	if (portador->container->arma == NULL)
	{
		portador->container->arma = self;

		engine.gui->mensagem(TCOD_white, "{} equipa {}!", portador->nome, self->nome);
	}
	else if (portador->container->arma != NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja esta empunhando uma arma!", portador->nome);
		return;
	}
}

void Arma::desequipar(Entidade* self, Entidade* portador)
{
	if (portador->container->arma != NULL)
	{
//		portador->atacador->forca -= dano;
		portador->container->arma = NULL;
		engine.gui->mensagem(TCOD_white, "{} desequipa {}!", portador->nome, self->nome);
	}
	else if (portador->container->arma == NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja nao tem nenhuma uma arma!", portador->nome);
		return;
	}
}
///ARMADURA

Armadura::Armadura(int bResistencia)
{
	this->bResistencia = bResistencia;
}

bool Armadura::usar(Entidade* self, Entidade* portador)
{
	if (portador->container->armadura == NULL)
	{
		equipar(self, portador);
		return true;
	}
	else if (portador->container->armadura == self)
	{
		desequipar(self, portador);
		return true;
	}
	return false;
}

void Armadura::equipar(Entidade* self, Entidade* portador)
{
	if (portador->container->armadura == NULL)
	{
		portador->container->armadura = self;
		portador->destrutivel->resistencia += bResistencia;
		engine.gui->mensagem(TCOD_white, "{} veste {}!", portador->nome, self->nome);
	}
	else if (portador->container->armadura != NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja esta trajando uma armadura!", portador->nome);
		return;
	}
}

void Armadura::desequipar(Entidade* self, Entidade* portador)
{
	if (portador->container->armadura != NULL)
	{
		portador->destrutivel->resistencia -= bResistencia;
		portador->container->armadura = NULL;
		engine.gui->mensagem(TCOD_white, "{} tira {}!", portador->nome, self->nome);
	}
	else if (portador->container->armadura == NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja nao tem nenhuma uma armadura!", portador->nome);
		return;
	}
}


