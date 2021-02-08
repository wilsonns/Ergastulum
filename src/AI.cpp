#include "AI.h"
#include <main.h>

AI::AI()
{
    //ctor
}

AI::~AI()
{
    //dtor
}

void aiJogador::atualizar(Entidade *owner)
{
    if(owner->destrutivel && owner->destrutivel->morreu())
    {
        return;
    }
    int dx = 0, dy =0;
    int key = getch();
    switch(key)
    {
        case KEY_UP:
        case 56://cima
            dy = -1;
            break;
        case KEY_DOWN:
        case 50://baixo
            dy = 1;
            break;
        case KEY_LEFT:
        case 52://esquerda
            dx = -1;
            break;
        case KEY_RIGHT:
        case 54://direita
            dx = 1;
            break;
        case 49://baixoesquerda
            dy = 1;
            dx = -1;
            break;
        case 51://baixodireita
            dy = 1;
            dx = 1;
            break;
        case 55://cimaesqyuerda
            dy = -1;
            dx = -1;
            break;
        case 57: //cimadireita
            dy = -1;
            dx = 1;
            break;
        case 53://fazer nada tecla 5
            break;
        case KEY_F(1):
            engine.rodando = false;
            break;
        case KEY_F(2):
            engine.debug = !engine.debug;
            break;
        case KEY_F(3):
            engine.mostrarPath = !engine.mostrarPath;
            break;
    }
    if(dx != 0 || dy != 0)
    {
        moverOuAtacar(owner,owner->x+dx,owner->y+dy);
    }
    engine.log->inserirmsg("Turno do jogador finalizado");
}

bool aiJogador::moverOuAtacar(Entidade *owner, int xalvo, int yalvo)
{
    if(engine.mapa->eParede(xalvo,yalvo))
    {
        return false;
    }

    for (unsigned int i = 0; i < engine.entidades.size(); i++)
    {
        Entidade* entidade = engine.entidades[i];
        if (entidade->x == xalvo && entidade->y == yalvo
            && entidade->destrutivel && !entidade->destrutivel->morreu() && entidade != owner)
        {
            owner->atacador->atacar(owner, entidade);
            return false;
        }
    }
    owner->x = xalvo;
    owner->y = yalvo;
    return true;
}

void aiMonstro::atualizar(Entidade *owner)
{
    if(owner->destrutivel && owner->destrutivel->morreu())
    {
        return;
    }
    moverOuAtacar(owner,engine.jogador->x,engine.jogador->y);
    engine.log->inserirmsg("Turno do monstro finalizado");
}

bool aiMonstro::moverOuAtacar(Entidade *owner,int xalvo, int yalvo)
{
    owner->caminho = engine.pathMapa->acharCaminho(owner, engine.jogador);
    for (int i = 0; i < owner->caminho.size(); i++)
    {
        engine.log->inserirmsg("Caminho[" + std::to_string(i) + "] X:" + std::to_string(owner->caminho[i]->x) + "Y:" + std::to_string(owner->caminho[i]->y));
    }
    owner->x = owner->caminho[0]->x;
    owner->y = owner->caminho[0]->y;
    /*owner->caminho.erase(owner->caminho.begin());
    int dx = xalvo - owner->x;
    int dy = yalvo - owner->y;
    float distancia = sqrtf((dx * dx) + (dy * dy));

    if (distancia >= 2)
    {
        dx = (int)(round(dx / distancia));
        dy = (int)(round(dy / distancia));
        
        if(engine.mapa->podeAndar(owner->x +dx, owner->y + dy))
        {
            owner->x += dx;
            owner->y += dy;
        }
    }
    else if(owner->atacador)
    {
        owner->atacador->atacar(owner, engine.jogador);
    }*/
    return true;
}
