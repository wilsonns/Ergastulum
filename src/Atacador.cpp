#include "Atacador.h"
#include "main.h"

Atacador::Atacador(float poder)
{
    this->poder = poder;
    //ctor
}

Atacador::~Atacador()
{
    //dtor
}

void Atacador::atacar(Entidade *owner, Entidade *alvo)
{
    if(alvo->destrutivel && !alvo->destrutivel->morreu())
    {
        float dano;
        dano = (engine.random(1,2,(int)(poder))-(alvo->destrutivel->defesa));

        if(dano > 0)
        {
            std::cout << owner->nome << " atacou " << alvo->nome << " causando " << int(dano)  << " dano!" << std::endl;
        }
        else
        {
            std::cout << owner->nome << " atacou " << alvo->nome << " sem efeito!" << std::endl;
        }
        alvo->destrutivel->tomarDano(alvo, dano);
            if(alvo->ai)
            {
                delete alvo->ai;
                alvo->ai = new aiMonstro();
                
            }
    }
    else
    {
        std::cout << owner->nome << " ataca em vao!" << std::endl;
    }
}

