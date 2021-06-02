#include "Atacador.h"

Atacador::Atacador(Entidade *self)
{
    //this->self = self;
    
    //SKILLS
    //ctor
}

Atacador::~Atacador()
{
    //dtor
}



void Atacador::atacar(Entidade* alvo)
{
    if (!alvo->morreu())
    {
        //Primeiro passo: self ataca e o alvo tenta se esquivar
        //Tipo de dano
        int acerto;
        Item* arma = self->container->arma;
        int nivel = 0;
        if(arma)
        {
            std::string tipo = self->container->arma->tipo;
            //nivel = self->habilidades[tipo]->nivelAjustado == 0 ? -3 : self->habilidades[tipo]->nivelAjustado;
            }
        else
        {
            //nivel = self->habilidades["Desarmado"]->nivelAjustado == 0 ? -3 : self->habilidades["Desarmado"]->nivelAjustado;
            
        }
        acerto = engine.random(1, 100, nivel);

        
        int esquiva;
        int agilidade = 0;
        //= alvo->atributos["Agilidade"]->nivelAjustado;
        if (agilidade == 0)
        {
            esquiva = -99;
        }
        else
        {
            esquiva = engine.random(1, 100, agilidade);
        }
        std::string ataque;
        if (arma)
        {
            if (arma->tipo == "Espada")
            {
                ataque = "corta";
            }
        }
        else
        {
            switch (engine.random(1, 2))
            {
            case 1:
                ataque = "soca";
                break;
            case 2:
                ataque = "chuta";
                break;
            }
        }
        if (acerto < esquiva)
        {
            engine.gui->mensagem(TCOD_white, "{} {} {}, mas {} se esquiva!", self->nome,ataque, alvo->nome, alvo->nome);
            ///MENSAGEM DE FALHA
        }
        else
        {
            int dano;
            if (arma)
            {
                dano = engine.random(1, arma->dano, self->getAtributo(ST));
            }
            else
            {
                //dano = engine.random(1, self->atributos["Forca"]->nivelAjustado, (int)(self->atributos["Forca"]->nivelAjustado * 0.1f));
            }

            if (dano <= 0)
            {
                dano = 1;
            }
            engine.gui->mensagem(TCOD_white, "{} {} {} causando {} dano!", self->nome,ataque, alvo->nome, std::to_string(dano));
            /// MENSAGEM
            alvo->tomarDano(dano);
        }
    }
}

void Atacador::atacarRanged(Entidade* alvo)
{
    if (alvo && !alvo->morreu() /*&& self->container->arma->eRanged*/)
    {
        int acerto = engine.random(0, 100, self->getAtributo("Destreza") + self->getHabilidade("Arco"));
        if (acerto > 50)
        {
            int dano = engine.random(1, 6);
            if (dano > 0)
            {
                dano = alvo->tomarDano(dano);
                engine.gui->mensagem(TCOD_white, "{} dispara contra {} e acerta, causando {} dano!", self->nome, alvo->nome, std::to_string(dano));
            }
        }
        else
        {

            engine.gui->mensagem(TCOD_white, "{} dispara contra {}, mas nao acerta!", self->nome, alvo->nome, alvo->nome);
            return;
        }
    }
    else if(alvo == NULL)
    {
//        engine.gui->mensagem(TCOD_white, "{} nao pode ser usada para atacar a distancia!", self->container->arma->nome);
    }
}

void Atacador::atacar(Tile* alvo)
{
    /*if (alvo->destrutivel && !alvo->destrutivel->destruido() && !alvo->passavel)
    {
        //int dano = self->atributos["Forca"]->nivelAjustado - alvo->destrutivel->resistencia;
        int dano = 0;
        if (dano > 0)
        {
            alvo->destrutivel->tomarDano(dano);
        }
    }*/
}
