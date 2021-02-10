#include "Destrutivel.h"

Destrutivel::Destrutivel(float hpMax, float defesa, const char *nomeCadaver)
{
    this->hpMax = hpMax;
    this->hp = hpMax;
    this-> defesa = defesa;
    this->nomeCadaver = nomeCadaver;

    //ctor
}

Destrutivel::~Destrutivel()
{
    //dtor
}

float Destrutivel::tomarDano(Entidade *owner, float dano)
{
    hp -= dano;
    if(hp <= 0)
    {
        morrer(owner);
    }
    return dano;
}

float Destrutivel::curar(float valor)
{
    hp += valor;
    if (hp > hpMax)
    {
        valor = hp - hpMax;
        hp = hpMax;
    }
    return valor;
}

void Destrutivel::morrer(Entidade *owner)
{
    owner->simbolo = '%';
    owner->nome = nomeCadaver;
    owner->denso = false;
    for(unsigned int i = 0; i < engine.entidades.size();i++)
    {
        if(engine.entidades[i] == owner)
        {

            engine.entidades.erase(engine.entidades.begin()+i);
            engine.entidades.insert(engine.entidades.begin(),owner);
        }
    }
}

destrutivelMonstro::destrutivelMonstro(float hpMax, float defesa, const char* nomeCadaver) : Destrutivel(hpMax,defesa,nomeCadaver)
{
}

destrutivelJogador::destrutivelJogador(float hpMax, float defesa, const char* nomeCadaver) : Destrutivel(hpMax,defesa,nomeCadaver)
{
}

void destrutivelMonstro::morrer(Entidade *owner)
{
    std::cout << owner->nome << " morreu!" << std::endl;
    Destrutivel::morrer(owner);

}


void destrutivelJogador::morrer(Entidade *owner)
{
    std::cout << "Você Morreu!!!!!"<<std::endl;
    Destrutivel::morrer(owner);
    engine.rodando = false;
}
