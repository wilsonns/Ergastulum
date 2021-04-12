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
			
		        engine.aRemover.push_back(*it);
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
		engine.mapa->adcionarItem(portador->x, portador->y, self->simbolo, self->pegavel->tipo, self->nome,self->pegavel->valor, self->cor);
		portador->container->remover(self);
		delete self;
		return true;
	}
	return false;
}

/// Curador
/// 
/// 
/// 

Curador::Curador(int valor)
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

/// Arma
/// 
/// 
/// 

Arma::Arma(int dano)
{
	this->valor = dano;
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
		portador->modificarAtributo("Forca", valor);
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
		portador->modificarAtributo("Forca", valor*(-1));
		portador->container->arma = NULL;
		engine.gui->mensagem(TCOD_white, "{} desequipa {}!", portador->nome, self->nome);
	}
	else if (portador->container->arma == NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja nao tem nenhuma uma arma!", portador->nome);
		return;
	}
}
/// ARMADURA
/// 
/// 
/// 

Armadura::Armadura(int bResistencia)
{
	this->valor = bResistencia;
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
		portador->modificarAtributo("Resistencia",valor);
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
		portador->modificarAtributo("Resistencia", valor*(-1)); 
		portador->container->armadura = NULL;
		engine.gui->mensagem(TCOD_white, "{} tira {}!", portador->nome, self->nome);
	}
	else if (portador->container->armadura == NULL)
	{
		engine.gui->mensagem(TCOD_white, "{} ja nao tem nenhuma uma armadura!", portador->nome);
		return;
	}
}


