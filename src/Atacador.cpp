#include "Atacador.h"

Atacador::Atacador(Entidade *self, int forca, int destreza, int ataque)
{
    this->self = self;
    self->adcionarAtributo("Forca");
    self->modificarAtributo("Forca", forca);
    self->adcionarAtributo("Destreza");
    self->modificarAtributo("Destreza", destreza);
    if (ataque > 0)
    {
        self->adcionarHabilidade("Ataque");
        self->modificarHabilidade("Ataque", ataque);
    }
    //ctor
}

Atacador::~Atacador()
{
    //dtor
}



void Atacador::atacar(Entidade* alvo)
{
    if (alvo->destrutivel && !alvo->destrutivel->morreu())
    {
        //Primeiro passo: self ataca e o alvo tenta se esquivar
        int acerto = engine.random(1, 20, int((self->habilidades.find("Ataque")!= self->habilidades.end()?(int)self->habilidades["Ataque"]:-4)
        *(self->atributos.find("Destreza")!= self->atributos.end()?self->atributos["Destreza"]->nivelAjustado:0.9)));
        int esquiva = engine.random(1, 20, alvo->destrutivel->agilidade);

        if (acerto - esquiva <= 0)
        {
            engine.gui->mensagem(TCOD_white, "{} ataca {}, mas {} se esquiva!", self->nome, alvo->nome, alvo->nome);
            ///MENSAGEM DE FALHA
        }
        else
        {
            int dano = (engine.random(1, 6, self->atributos["Forca"]->nivelAjustado - alvo->atributos["Resistencia"]->nivelAjustado));

            if (dano > 0)
            {
                engine.gui->mensagem(TCOD_white, "{} ataca {} causando {} dano!", self->nome, alvo->nome, std::to_string(dano));
                /// MENSAGEM
            }
            else
            {

                engine.gui->mensagem(TCOD_white, "{} ataca {} mas não causa dano nenhum!", self->nome, alvo->nome);
                ///MENSAGEM DE FALHAR EM CAUSAR DANO
            }
            alvo->destrutivel->tomarDano(dano);
        }
    }
}