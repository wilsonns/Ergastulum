#include "Engine.h"
#include "main.h"

Engine::Engine(int largura, int altura)
{
    this->largura = largura;
    this->altura = altura;

    TCODConsole::initRoot(largura, altura, "Joguim sem Nome do Will", false);
    logger = new LOGGER();
    gui = new GUI();
    jogador = new Entidade(1, 1, '@',"Will", TCOD_white);
    jogador->destrutivel = new destrutivelJogador(jogador,5, 2, 3, "Cadaver de" + jogador->nome);
    jogador->atacador = new Atacador(jogador,2,2,1); 
    jogador->ai = new aiJogador(1);
    jogador->ai->faccao = JOGADOR;
    jogador->container = new Container(10);
    jogador->nome = "Will";


    mapa = new Mapa(largura, 43);
    pathMapa = new Pathfinding();

    entidades.push_back(jogador);
  
    mapa->adcionarItem(mapa->dungeon[0]->xcentro + 1, mapa->dungeon[0]->ycentro + 1, '/', ARMA, "Espada de Xessus", 5, TCOD_silver);

    rodando = true;
    debug = true;
    mostrarPath = false;
    statusJogo = Engine::INICIO;
    //ctor
}

Engine::~Engine()
{
    entidades.clear();
    delete mapa;
    delete gui;
    //dtor
}

void Engine::render()
{
    auto root = TCODConsole::root;
    root->clear();
    mapa->render();
    for (std::vector<Entidade*>::iterator it = entidades.begin(); it != entidades.end(); it++)
    {
        Entidade* entidade = *it;
        if (mapa->estaNoFOV(entidade->x, entidade->y))
        {
            entidade->render();
        }
    }
    gui->render();
}

void Engine::atualizar()
{
    engine.mapa->computarFOV();
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &ultimoBotao, &mouse);
    if (statusJogo == INICIO || statusJogo == TURNO_NOVO)
    {
        jogador->atualizar();
    }
    else if (statusJogo == TURNO_INIMIGO)
    {
        for (std::vector<Entidade*>::iterator it = entidades.begin(); it != entidades.end();)
        {
            Entidade* entidade = *it;

            if (entidade->ai && entidade != jogador)
            {
                entidade->atualizar();
            }
            if (aRemover.size() > 0)
            {
                for (std::vector<Entidade*>::iterator it2 = aRemover.begin();!aRemover.empty();)
                {
                    Entidade* ent = *it2;
                    entidades.erase(std::find(entidades.begin(),entidades.end(),ent));
                    aRemover.erase(it2);
                    it = entidades.end();
                }
            }
            else
            {
                ++it;
            }
        }
        statusJogo = Engine::TURNO_NOVO;
    }
}

int Engine::random(int minimo, int maximo, int bonus)
{
    return minimo + rand() % (maximo - minimo) + bonus;
}

void Engine::mandarParaOInicio(Entidade* entidade)
{
//    entidades.erase(std::find(entidades.begin(), entidades.end(), entidade));
//    entidades.insert(entidades.begin(), std::find(entidades.begin(), entidades.end(), entidade));
}