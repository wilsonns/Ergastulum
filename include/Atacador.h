#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    public:
        float poder;


        Atacador(float poder);
        virtual ~Atacador();

        void atacar(Entidade *owner, Entidade *alvo);

    protected:

    private:
};

#endif // ATACADOR_H
