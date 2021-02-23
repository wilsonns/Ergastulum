#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    public:
        //Atributos
        int forca;//A quantidade de dano que a entidade é capaz de causar em um destrutivel
        int forcaBase;
        int destreza;//A capacidade do atacador de acertar uym alvo
        int destrezaBase;
                     //Habilidades
        //int manoamano;//habilidade com as mãos para bnrigar

        Atacador(int forca,int destreza);//ctor
        virtual ~Atacador();//dtor

        void atacar(Entidade *self, Entidade *alvo);//self ataca o alvo destrutivel e causa dano

    protected:

    private:
};

#endif // ATACADOR_H
