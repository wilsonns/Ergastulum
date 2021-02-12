#include "Atacador.h"
#include "main.h"

Atacador::Atacador(int forca, int destreza)
{
    this->forca = forca;
    this->destreza = destreza;
    //ctor
}

Atacador::~Atacador()
{
    //dtor
}

void Atacador::atacar(Entidade *self, Entidade *alvo)
{
    if (alvo->destrutivel && !alvo->destrutivel->morreu())
    {
        //Primeiro passo: self ataca e o alvo tenta se esquivar
        int acerto = engine.random(1, 20, destreza);
        int esquiva = engine.random(1, 20, alvo->destrutivel->agilidade);

        if (acerto - esquiva <= 0)
        {
            ///MENSAGEM DE FALHA
        }
        else
        {
            int dano = (engine.random(1, 6, forca) - alvo->destrutivel->resistencia);

            if (dano > 0)
            {
                /// MENSAGEM DE CAUSAR DANO
                std::cout << self->nome << " atacou " << alvo->nome << " causando " << int(dano) << " dano!" << std::endl;
            }
            else
            {
                ///MENSAGEM DE FALHAR EM CAUSAR DANO
                std::cout << self->nome << " atacou " << alvo->nome << " sem efeito!" << std::endl;
            }
            alvo->destrutivel->tomarDano(alvo, dano);
        }
    }
    else
    {
        ///MENSAGEM DE NÃO ATACAR NADA
        std::cout << self->nome << " ataca em vao!" << std::endl;
    }
}

