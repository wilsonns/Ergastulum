#include "Destrutivel.h"

Destrutivel::Destrutivel(Entidade* self, int vigor, int resistencia, int agilidade, std::string nomeCadaver)
{
    this->self = self;
    self->adcionarAtributo("Vigor");
    self->modificarAtributo("Vigor", vigor);
    self->adcionarAtributo("Resistencia");
    self->modificarAtributo("Resistencia", resistencia);
    self->adcionarAtributo("Agilidade");
    self->modificarAtributo("Agilidade", agilidade);

    this->hpMax = self->atributos["Vigor"]->nivelAjustado * 5;
    this->hp = hpMax;
    
    this->nomeCadaver = nomeCadaver;

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
        morrer();
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
    for (std::vector<Entidade*>::iterator it = self->container->inventario.begin(); it !=self->container->inventario.end();it++)
    {
        Entidade* entidade = *it;
        entidade->pegavel->soltar(entidade,self);
    }
    engine.mandarParaOInicio(self);
}

destrutivelMonstro::destrutivelMonstro(Entidade *self, int vigor, int resistencia,int agilidade, std::string nomeCadaver) : 
    Destrutivel(self, vigor,resistencia,agilidade,nomeCadaver)
{
}

destrutivelJogador::destrutivelJogador(Entidade* self, int vigor, int resistencia, int agilidade, std::string nomeCadaver) :
    Destrutivel(self, vigor, resistencia, agilidade, nomeCadaver)
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

void destrutivelTerreno::destruir(Tile* self)
{
    self->passavel = true;
}