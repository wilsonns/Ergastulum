#include "Engine.h"
#include "main.h"

Engine::Engine(int largura, int altura)
{
    srand(time(NULL));
    this->largura = largura;
    this->altura = altura;
    TCODConsole::initRoot(largura, altura, "Joguim sem Nome do Will", false);
    
    logger = new LOGGER();
    gui = new GUI();
    jogador = new Entidade(1, 1, '@' ,5,3,"Will",TCOD_black);
    jogador->destrutivel = new destrutivelJogador(jogador,5, 2, 3, "Cadaver de" + jogador->nome);
    jogador->atacador = new Atacador(jogador,20,2,1); 
    jogador->ai = new aiJogador(jogador);
    jogador->container = new Container(5*jogador->atributos["Forca"]->nivelAjustado);


    mapa = new Mapa(largura, 43);
    pathMapa = new Pathfinding();

    mapa->mover(jogador->x, jogador->y, jogador);

    entidades.push_back(jogador);
  
    mapa->adcionarItem(mapa->dungeon[0]->xcentro + 1, mapa->dungeon[0]->ycentro + 1, '/',"Espada de Xessus", 5, TCOD_black,5);
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
        if (mapa->eVisivel(entidade->x, entidade->y))
        {
            entidade->render();
        }
    }
    gui->render();
}

void Engine::atualizar()
{
    for (int x = 0; x < mapa->largura; x++)
    {
        for (int y = 0; y < mapa->altura; y++)
        {
            mapa->tornarNaoVisivel(x, y);
        }
    }
    engine.jogador->FOV();
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
                if (entidade->destrutivel->morreu())
                {
                    continue;
                }
                else
                {
                    it++;
                    continue;
                }
            }
            it++;
        }
        statusJogo = Engine::TURNO_NOVO;
    }
}

int Engine::random(int minimo, int maximo, int bonus)
{
    return rand() % ((maximo - minimo + 1) + minimo)+bonus;
}

void Engine::mandarParaOInicio(Entidade* entidade)
{
    entidades.erase(std::find(entidades.begin(), entidades.end(), entidade));
    entidades.insert(entidades.begin(), entidade);
}