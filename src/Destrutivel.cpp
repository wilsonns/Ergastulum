#include "Destrutivel.h"

Destrutivel::Destrutivel(int vigor, int resistencia,int agilidade, const char *nomeCadaver)
{
    this->hpMax = vigor * 5;
    this->hp = hpMax;
    this->resistencia = resistencia;
    resistenciaBase = resistencia;
    this->agilidade = agilidade;
    agilidadeBase = agilidade;
    this->nomeCadaver = nomeCadaver;

    //ctor
}

Destrutivel::~Destrutivel()
{
    //dtor
}

int Destrutivel::tomarDano(Entidade *self, int dano)
{
    hp -= dano;
    if(hp <= 0)
    {
        morrer(self);
    }
    return dano;
}

int Destrutivel::curar(int valor)
{
    hp += valor;
    if (hp > hpMax)
    {
        valor = hp - hpMax;
        hp = hpMax;
    }
    return valor;
}

void Destrutivel::morrer(Entidade *self)
{
    self->simbolo = '%';
    self->nome = nomeCadaver;
    self->denso = false;
    engine.mandarParaOInicio(self);
}

destrutivelMonstro::destrutivelMonstro(int vigor, int resistencia,int agilidade, const char* nomeCadaver) : 
    Destrutivel(vigor,resistencia,agilidade,nomeCadaver)
{
}

destrutivelJogador::destrutivelJogador(int vigor, int resistencia, int agilidade, const char* nomeCadaver) : 
    Destrutivel(vigor, resistencia, agilidade, nomeCadaver)
{
}

void destrutivelMonstro::morrer(Entidade *self)
{
    Destrutivel::morrer(self);
}


void destrutivelJogador::morrer(Entidade *self)
{
    Destrutivel::morrer(self);
    engine.rodando = false;
}
