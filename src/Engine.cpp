#include "Engine.h"
#include "main.h"

Engine::Engine(int largura, int altura)
{
    this->largura = largura;
    this->altura = altura;

    TCODConsole::initRoot(largura, altura, "Joguim sem Nome do Will", false);
    log = new LOG();
    mapa = new Mapa(largura,43);
    pathMapa = new Pathfinding();
    gui = new GUI();
    jogador = new Entidade(1,1,'@',TCOD_white);
    jogador->destrutivel = new destrutivelJogador(5,2,3,"Seu Cadavi");
    jogador->atacador = new Atacador(2,3);
    jogador->ai = new aiJogador(1);
    jogador->container = new Container(10);
    jogador->nome = "Will";
    entidades.push(jogador);
    rodando = true;
    debug = false;
    mostrarPath = false;
    statusJogo = Engine::INICIO;
    //ctor
}

Engine::~Engine()
{
    entidades.clearAndDelete();
    delete mapa;
    delete gui;
    //dtor
}

void Engine::render()
{
    auto root = TCODConsole::root;
    root->clear();
    mapa->render();
    for (Entidade** iterator = entidades.begin();iterator != entidades.end();iterator++)
    {
        Entidade* entidade = *iterator;
        if (mapa->estaNoFOV(entidade->x, entidade->y))
        {
            entidade->render();
        }
    }
    gui->render();
}

void Engine::atualizar()
{
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &ultimoBotao, NULL);
    if (statusJogo == INICIO || statusJogo == TURNO_NOVO)
    {
        jogador->atualizar();
    }
    else if(statusJogo == TURNO_INIMIGO)
    {
        for (Entidade** it = entidades.begin(); it != entidades.end();it++)
        {
            Entidade* entidade = *it;
            if (entidade != jogador)
            {
                entidade->atualizar();
            }
        }
        statusJogo = Engine::TURNO_NOVO;
    }
}

int Engine::random(int minimo, int maximo, int bonus)
{
    return minimo + rand()%(maximo-minimo)+bonus;
}

void Engine::mandarParaOInicio(Entidade* entidade)
{
    entidades.remove(entidade);
    entidades.insertBefore(entidade,0);
}