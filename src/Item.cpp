#include "Item.h"

Item::Item(std::string nome, std::string tipo, std::string descricao, int simbolo, TCODColor cor, int peso)
{
	this->nome = nome;
	this->tipo = tipo;
	this->descricao = descricao;
	this->simbolo = simbolo;
	this->cor = cor;
	this->peso = peso;
	//ctor
}

Item::~Item()
{
	//dtor
}

void Item::fazerArma()
{
	this->eArma = true;
}

void Item::fazerRanged()
{
	this->eRanged = true;
}

void Item::fazerArmadura()
{
	this->eArmadura = true;
}


void Item::setCargas(int cargas)
{
	this->cargas = cargas;
}

void Item::setMaxCargas(int cargas)
{
	maxCargas = cargas;
	if (this->cargas > maxCargas)
	{
		this->cargas = maxCargas;
	}
}
void Item::setDano(int dano)
{
	this->dano = dano;
}

void Item::setBlindagem(int blindagem)
{
	this->blindagem = blindagem;
}

void Item::setPeso(int peso)
{
	this->peso = peso;
}


bool Item::pegar(Entidade* portador)
{
	if (portador->container && portador->container->adcionar(this))
	{
		this->portador = portador;
		return true;
	}
	return false;
}

bool Item::usar()
{
	if (portador->container)
	{
		if (eArma)
		{
			equipar();
		}
		return true;
	}
	return false;
}

bool Item::soltar()
{
	if (portador->container)
	{
		engine.mapa->adcionarItem(portador->x, portador->y, this->simbolo,this->nome,this->tipo,this->descricao,0,this->cor,this->peso);
		portador->container->remover(this);
		return true;
	}
	return false;
}

bool Item::equipar()
{
	if (portador->container->arma)
	{
		engine.gui->mensagem(TCOD_white, "{} ja esta empunhando {}.", portador->nome, portador->container->arma->nome);
		return false;
	}
	else
	{
		portador->container->arma = this;
		engine.gui->mensagem(TCOD_white, "{} empunha {}.", portador->nome, portador->container->arma->nome);
		return true;
	}
}
