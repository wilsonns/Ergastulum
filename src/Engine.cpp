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
    debug = true;
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
    for (unsigned int i = 0; i < mortos.size(); i++)
    {
        mortos[i]->render();
    }
    for (unsigned int i = 0; i < entidades.size(); i++)
    {
        entidades[i]->render();
    }
    refresh();

    if (debug == true && mostrarPath == true)
    {
        for (int i = 0; i < entidades.size();i++)
        {
            if (entidades[i]->caminho.size() != 0)
            {
                for (int j = 0; j < entidades[i]->caminho.size();j++)
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(entidades[i]->caminho[j]->y, entidades[i]->caminho[j]->x, "x");
                    attroff(COLOR_PAIR(3));
                }
            }
            else
            {
                attron(COLOR_PAIR(4));
                mvprintw(entidades[i]->y, entidades[i]->x, "X");
                attroff(COLOR_PAIR(4));
            }
        }
    }
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
    monstro->ai = new aiMonstro(1);
    entidades.push_back(monstro);
}
