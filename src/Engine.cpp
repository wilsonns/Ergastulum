#include "Engine.h"
#include "main.h"

Engine::Engine()
{
    log = new LOG();
    mapa = new Mapa(70,43);
    pathMapa = new Pathfinding();
    gui = new GUI();
    jogador = new Entidade(1,1,'@',TCOD_white);
    jogador->destrutivel = new destrutivelJogador(5,2,3,"Seu Cadavi");
    jogador->atacador = new Atacador(2,3);
    jogador->ai = new aiJogador(1);
    jogador->container = new Container(10);
    entidades.push(jogador);
    rodando = true;
    debug = false;
    mostrarPath = false;
    //ctor
}

Engine::~Engine()
{
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
}

void Engine::atualizar()
{
    jogador->atualizar();
    for (Entidade** iterator = entidades.begin(); iterator != entidades.end();iterator++)
    {
        Entidade* entidade = *iterator;
        if (entidade != jogador)
        {
            entidade->atualizar();
        }
    }
}

int Engine::random(int minimo, int maximo, int bonus)
{
    return minimo + rand()%(maximo-minimo)+bonus;
}

