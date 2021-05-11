#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <main.h>

class Terreno
{
public:
	Terreno();
	~Terreno();


private:
	int x, y; //posicao do objeto no mapa
	int simboloAberto, simboloFechado;//para portas e baús
	DestrutivelTerreno * destrutivel;

protected:

};

#endif // ENTIDADE_H
