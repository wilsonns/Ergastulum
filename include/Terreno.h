#ifndef TERRENO_H
#define TERRENO_H

#include <main.h>
#include "Material.h"

class Material;

class Terreno
{
public:
	Terreno();
	Terreno(int simbf, int simba, Material *material);
	//~Terreno();
	virtual bool operar();
	void tornarDenso();
	void tornarNaoDenso();
	bool eDenso();
	void tornarOpaco();
	void tornarNaoOpaco();
	bool eOpaco();
	int simboloAberto, simboloFechado, simbAtual;//para portas e baús
	float movimento;
	bool porta;
	bool aberto;
	bool denso;
	bool opaco;
	Material* material;
private:

protected:

};

class Parede :public Terreno
{
public:
	Parede(int simbf, Material* material);
};

class Chao :public Terreno
{
public:
	Chao(int simbf, Material* material);
};


class Porta :public Terreno
{
public:
	Porta(int simbf, int simba, Material* material);
	bool operar();
};
#endif // TERRENO_H