#ifndef MATERIAL_H
#define MATERIAL_H

#include<main.h>

class Material
{
public:
	Material(std::string nome,const TCODColor cor, float durabilidade);
	std::string nome;
	TCODColor cor;
	float durabilidade;
};

#endif // MATERIAL_H
