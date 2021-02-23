#include "Atacador.h"
#include "main.h"

Atacador::Atacador(int forca, int destreza)
{
    this->forca = forca;
    forcaBase = forca;
    this->destreza = destreza;
    destrezaBase = destreza;
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
            engine.gui->mensagem(TCOD_white, "%s ataca %s, mas %s se esquiva!", self->nome, alvo->nome, alvo->nome);
            ///MENSAGEM DE FALHA
        }
        else
        {
            int dano = (engine.random(1, 6, forca) - alvo->destrutivel->resistencia);
       

            if (dano > 0)
            {
                engine.gui->mensagem(TCOD_white, "%s ataca %s causando %i dano!", self->nome, alvo->nome, dano);
                /// MENSAGEM
                //engine.gui->mensagens.push_back(new Mensagem(_strdup("%c ataca %c causando %i dano!"),1,self->nome,alvo->nome,dano));
            }
            else
            {

                engine.gui->mensagem(TCOD_white, "%s ataca %s mas não causa dano nenhum!", self->nome, alvo->nome);
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

