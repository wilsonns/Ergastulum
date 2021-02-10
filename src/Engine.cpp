#include "Engine.h"
#include "main.h"

Engine::Engine()
{
    log = new LOG();
    mapa = new Mapa(80,25);
    pathMapa = new Pathfinding();
    gui = new GUI();
    jogador = new Entidade(1,9,"Jogador",'@');
    jogador->destrutivel = new destrutivelJogador(20,0,"Seu Cadavi");
    jogador->atacador = new Atacador(2);
    jogador->ai = new aiJogador(1);
    jogador->container = new Container(10);
    entidades.push_back(jogador);
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
    clear();
    mapa->render();
    for(unsigned int i = 0; i < mortos.size(); i++)
    {
        mortos[i]->render();
    }
    for (unsigned int i = 0; i < entidades.size(); i++)
    {
        entidades[i]->render();
    }
    refresh();
    /*
    if (mostrarPath == true)
    {
        for (int i = 0; i < mapa->largura; i++)
        {
            for (int j = 0; j < mapa->altura; j++)
            {
                if (engine.pathMapa->nodos[i + j * mapa->largura].obstaculo)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(j, i, "X");
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(j, i, "O");
                    attroff(COLOR_PAIR(3));

                }
            }
        }
        if (engine.pathMapa->nodos[jogador->x + jogador->y * mapa->largura].obstaculo)
        {
            attron(COLOR_PAIR(4));
            mvprintw(22,0,"Obstaculo");
            attroff(COLOR_PAIR(4));
        }
        else
        {
           attron(COLOR_PAIR(3));
           mvprintw(22, 0, "Sem obstaculo");
           attroff(COLOR_PAIR(3));
        }
    }*/

    if (debug == true)
    {
        for (unsigned int i = 0; i < entidades.size(); i++)
        {
            mvprintw(i, 70, "x:%i/y:%i", entidades[i]->x, entidades[i]->y);
        }
    }

    refresh();
    gui->render();
    wrefresh(gui->msgs);
}
void Engine::atualizar()
{
    jogador->atualizar();
    for(unsigned int i = 0; i < entidades.size();i++)
    {
        if(entidades[i] != jogador)
        {
            entidades[i]->atualizar();
        }
    }
}

int Engine::random(int minimo, int maximo, int bonus)
{
    return minimo + rand()%(maximo-minimo)+bonus;
}

void Engine::adcmonstro(int x, int y)
{
    Entidade *monstro = new Entidade(x,y,"Orc" ,'O');
    monstro->destrutivel = new destrutivelMonstro(20,2,"Cadavi");
    monstro->atacador = new Atacador(1);
    monstro->ai = new aiMonstro(0.25);
    entidades.push_back(monstro);
}
