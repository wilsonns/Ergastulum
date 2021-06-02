#include "Material.h"


Material::Material(std::string nome,const TCODColor cor, float durabilidade)
{
	this->nome = nome;
	this->cor = cor;
	this->durabilidade = durabilidade;
}