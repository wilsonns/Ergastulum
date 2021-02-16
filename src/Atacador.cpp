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
                /// MENSAGEM
                //engine.gui->mensagens.push_back(new Mensagem(_strdup("%c ataca %c causando %i dano!"),1,self->nome,alvo->nome,dano));
            }
            else
            {
                ///MENSAGEM DE FALHAR EM CAUSAR DANO
            }
            alvo->destrutivel->tomarDano(alvo, dano);
        }
    }
    else
    {
        ///MENSAGEM DE NÃO ATACAR NADA
    }
}

