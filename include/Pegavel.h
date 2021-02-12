#ifndef PEGAVEL_H
#define PEGAVEL_H
#include <main.h>

class Pegavel
{
public:
	Pegavel();//CTOR
	virtual ~Pegavel();//DTOR

	bool pegar(Entidade* self, Entidade* portador);//se conseguir pegar o item, retorna verdadeiro
	virtual bool usar(Entidade* self, Entidade* portador);//função virtual para usar o item, veja a referencia de cada classe filha
};

class Curador : public Pegavel
{
public:
	float valor;//o valor de cura que o curador cura

	Curador(float valor);//ctor
	bool usar(Entidade* self, Entidade* portador);//retorna verdadeiro se conseguir usar o item, que vai curar o valor em pontos de vida do portador
};

#endif // PEGAVEL_H