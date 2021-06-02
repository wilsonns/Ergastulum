#include "Destrutivel.h"

Destrutivel::Destrutivel()
{
    //dummy
}

Destrutivel::Destrutivel(Entidade* self, std::string nomeCadaver)
{
    /*this->self = self;
    this->nomeCadaver = nomeCadaver;
    */
    //ctor
}

Destrutivel::~Destrutivel()
{
    //dtor
}

int Destrutivel::tomarDano(int dano)
{
    hp -= dano;
    if(hp <= 0)
    {
        this->morrer();
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

void Destrutivel::morrer()
{
self->simbolo = '%';
engine.gui->mensagem(TCOD_darker_red, "{} morreu!", self->nome);
self->nome = nomeCadaver;
self->denso = false;
self->ai = NULL;
for (std::vector<Item*>::iterator it = self->container->inventario.begin(); it != self->container->inventario.end(); it++)
{
    Item* item = *it;
    item->soltar();
}
engine.mapa->adcionarItem(self->x, self->y, self->simbolo, self->nome, "Cadaver", "", 0, TCOD_darker_red, 0);
engine.entidades.erase((std::find(engine.entidades.begin(),engine.entidades.end(),self)));
}

destrutivelMonstro::destrutivelMonstro(Entidade *self, std::string nomeCadaver) : 
    Destrutivel(self,nomeCadaver)
{
}

destrutivelJogador::destrutivelJogador(Entidade* self, std::string nomeCadaver) :
    Destrutivel(self, nomeCadaver)
{
}

void destrutivelMonstro::morrer()
{
    Destrutivel::morrer();
}


void destrutivelJogador::morrer()
{
    Destrutivel::morrer();

    engine.rodando = false;
}

DestrutivelTerreno::DestrutivelTerreno(Tile* self, int resistencia)
{
    this->self = self;
    this->resistencia = resistencia;
    this->hpMax = 20;
    this->hp = hpMax;
}

void DestrutivelTerreno::destruir()
{
  //  self->passavel = true;
}

int DestrutivelTerreno::tomarDano(int dano)
{
    hp -= dano;
    if (hp <= 0)
    {
        this->destruir();
    }
    return dano;
}