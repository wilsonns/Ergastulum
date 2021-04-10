#include "Atacador.h"
#include "main.h"

Atacador::Atacador(float forca, float destreza, float ataque)
{
    adcionarAtributo("Forca", forca);
    adcionarAtributo("Destreza", destreza);
    if (ataque > 0)
    {
        adcionarHabilidade("Ataque", ataque);
    }
    //ctor
}

Atacador::~Atacador()
{
    //dtor
}

void Atacador::adcionarAtributo(std::string atributo, float valorInicial)
{
    atributos.emplace(std::make_pair(atributo, valorInicial));
}


void Atacador::modificarAtributo(std::string atributo, float valor)
{
    if (atributos.find(atributo) != atributos.end())
    {
        atributos[atributo] += valor;
    }
}


void Atacador::adcionarHabilidade(std::string habilidade, float valorInicial)
{
    habilidades.emplace(std::make_pair(habilidade, valorInicial));
}

void Atacador::modificarHabilidade(std::string habilidade, float valor)
{
    if (habilidades.find(habilidade) != habilidades.end())
    {
        habilidades[habilidade] += valor;
    }
}


void Atacador::atacar(Entidade* self, Entidade* alvo)
{
    if (alvo->destrutivel && !alvo->destrutivel->morreu())
    {
        //Primeiro passo: self ataca e o alvo tenta se esquivar
        int acerto = engine.random(1, 20, int((habilidades.find("Ataque")!=habilidades.end()?(int)habilidades["Ataque"]:-4)
        *(atributos.find("Destreza")!= atributos.end()?habilidades["Destreza"]:0.9)));
        int esquiva = engine.random(1, 20, alvo->destrutivel->agilidade);

        if (acerto - esquiva <= 0)
        {
            engine.gui->mensagem(TCOD_white, "{} ataca {}, mas {} se esquiva!", self->nome, alvo->nome, alvo->nome);
            ///MENSAGEM DE FALHA
        }
        else
        {
            int dano = (engine.random(1, 6, atributos["Forca"]) - alvo->destrutivel->resistencia);
       

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
            alvo->destrutivel->tomarDano(alvo, dano);
        }
    }
    else
    {
        ///MENSAGEM DE NÃO ATACAR NADA
    }
}