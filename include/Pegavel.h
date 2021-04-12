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

	int tipo;//Vide enum tipoItem acima
	int valor;//O valor principal do item, sendo cura pra poção, dano pra arma, etc

	bool pegar(Entidade* self, Entidade* portador);//se conseguir pegar o item, retorna verdadeiro
	virtual bool usar(Entidade* self, Entidade* portador);//função virtual para usar o item, veja a referencia de cada classe filha
	virtual bool soltar(Entidade* self, Entidade* portador);
	//virtual void equipar(Entidade* self, Entidade* portador);
	//virtual void desequipar(Entidade* self, Entidade* portador);

};

class Curador : public Pegavel
{
public:
	Curador(int valor);//ctor
	bool usar(Entidade* self, Entidade* portador);//retorna verdadeiro se conseguir usar o item, que vai curar o valor em pontos de vida do portador
};

class Arma : public Pegavel
{
public:
	Arma(int dano);
	bool usar(Entidade* self, Entidade* portador);
	void equipar(Entidade* self, Entidade* portador);
	void desequipar(Entidade* self, Entidade* portador);

private:

};

class Armadura : public Pegavel
{
public:
	Armadura(int bResistencia);
	
	bool usar(Entidade* self, Entidade* portador);
	void equipar(Entidade* self, Entidade* portador);
	void desequipar(Entidade* self, Entidade* portador);

private:

};

#endif // PEGAVEL_H