#include "Terreno.h"

Terreno::Terreno()
{

}

Terreno::Terreno(int simbf, int simba,Material *material)
{
	simboloAberto = simba;
	simboloFechado = simbf;
	simbAtual = simbf;
	aberto = NULL;
	denso = true;
	opaco = false;
	this->material = material;
}

bool Terreno::operar()
{
	return true;
}

void Terreno::tornarDenso()
{
	denso = true;
}
void Terreno::tornarNaoDenso()
{
	denso = false;
}

bool Terreno::eDenso()
{
	return denso;
}

void Terreno::tornarOpaco()
{
	opaco = true;
}

void Terreno::tornarNaoOpaco()
{
	opaco = false;
}


bool Terreno::eOpaco()
{
	return opaco;
}

Parede::Parede(int simbf,Material*material)
{
	simboloAberto = simbf;
	simboloFechado = simbf;
	simbAtual = simbf;
	aberto = NULL;
	porta = false;
	denso = true;
	opaco = true;
	this->material = material;
}

Chao::Chao(int simbf,Material*material)
{
	simboloAberto = simbf;
	simboloFechado = simbf;
	simbAtual = simbf;
	aberto = NULL;

	porta = false;
	denso = false;
	opaco = false;
	this->material = material;

}


Porta::Porta(int simbf, int simba, Material* material)
{
	simboloAberto = simba;
	simboloFechado = simbf;
	simbAtual = simbf;
	this->material = material;
	aberto = false;

	porta = true;
	denso = true;
	opaco = true;
}

bool Porta::operar()
{
	aberto = !aberto;
	if (aberto)
	{
		simbAtual = simboloAberto;
		denso = false;
		opaco = false;
		return true;
	}
	else
	{
		simbAtual = simboloFechado;
		denso = true;
		opaco = true;
		return true;
	}
}