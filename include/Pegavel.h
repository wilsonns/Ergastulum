#ifndef PEGAVEL_H
#define PEGAVEL_H
#include <main.h>

enum tipoItem
{
	POCAO = 1,
	ARMA = 2,
	ARMADURA = 3,
	ESCUDO = 4
};

class Pegavel
{
public:
	Pegavel();//CTOR
	virtual ~Pegavel();//DTOR

	int tipo = 1;

	bool pegar(Entidade* self, Entidade* portador);//se conseguir pegar o item, retorna verdadeiro
	virtual bool usar(Entidade* self, Entidade* portador);//função virtual para usar o item, veja a referencia de cada classe filha
	virtual bool soltar(Entidade* self, Entidade* portador);
	//virtual void equipar(Entidade* self, Entidade* portador);
	//virtual void desequipar(Entidade* self, Entidade* portador);

};

class Curador : public Pegavel
{
public:
	float valor;//o valor de cura que o curador cura

	Curador(float valor);//ctor
	bool usar(Entidade* self, Entidade* portador);//retorna verdadeiro se conseguir usar o item, que vai curar o valor em pontos de vida do portador
};

class Arma : public Pegavel
{
public:
	int dano;
	Arma(int dano);
	bool usar(Entidade* self, Entidade* portador);
	void equipar(Entidade* self, Entidade* portador);
	void desequipar(Entidade* self, Entidade* portador);

private:

};

#endif // PEGAVEL_H