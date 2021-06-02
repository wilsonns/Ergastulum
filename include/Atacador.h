#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    public:        
        Entidade* self;
        Atacador(Entidade* self);//ctor
        virtual ~Atacador();//dtor

        void atacar(Entidade* alvo);//self ataca o alvo destrutivel e causa dano
        void atacarRanged(Entidade* alvo);//ataca o alvo à distancia
        void atacar(Tile* alvo);
};

#endif // ATACADOR_H
