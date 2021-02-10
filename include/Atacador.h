#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    public:
        float poder;//A quantidade de dano que a entidade é capaz de causar em um destrutivel


        Atacador(float poder);//ctor
        virtual ~Atacador();//dtor

        void atacar(Entidade *owner, Entidade *alvo);//owner ataca o alvo destrutivel e causa dano

    protected:

    private:
};

#endif // ATACADOR_H
