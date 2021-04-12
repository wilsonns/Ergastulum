#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    public:        
        Entidade* self;
        Atacador(Entidade* self, int forca = 1, int destreza = 1, int ataque = 0);//ctor
        virtual ~Atacador();//dtor

        void atacar(Entidade* alvo);//self ataca o alvo destrutivel e causa dano
};

#endif // ATACADOR_H
