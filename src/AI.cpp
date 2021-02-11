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

aiJogador::aiJogador(float velocidade)
{
    this->velocidade = velocidade;
    barraTurno = 0;
}

void aiJogador::atualizar(Entidade* owner)
{
    if (owner->ai->barraTurno >= 1)
    {
        if (owner->destrutivel && owner->destrutivel->morreu())
        {
            return;
        }
        int dx = 0, dy = 0;//variaveis que representam para onde o jogador vai se mover,variando de -1 a 1
        int key = getch();
        switch (key)
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
        case 'g':
        case 'G'://tecla g/G - Pegar item;
        {
            bool achado = false;
            for (unsigned short int i = 0; i < engine.entidades.size();i++)
            {
                if (engine.entidades[i]->pegavel && engine.entidades[i]->x == owner->x && engine.entidades[i]->y == owner->y)
                {
                    if (engine.entidades[i]->pegavel->pegar(engine.entidades[i], owner))
                    {
                        achado = true;
                        // MENSAGEM - VOCÊ PEGOU O ITEM
                        break;
                    }
                    else if (!achado)
                    {
                        achado = true;
                        //MENSAGEM - INVENTARIO CHEIO
                    }
                }
                if (!achado)
                {
                    ///MENSAGEM - NÃO TEM NADA PRA PEGAR AQUI
                }
            }
        }
        break;
        case 'i':
        case 'I':
        {
            Entidade* entidade = escolherDoInventario(owner);
            if (entidade)
            {
                entidade->pegavel->usar(entidade, owner);

            }
        }
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
        if (dx != 0 || dy != 0)
        {
            moverOuAtacar(owner, owner->x + dx, owner->y + dy);
        }
        engine.log->inserirmsg("Turno do jogador finalizado");
        owner->ai->barraTurno -= 1;
    }
    else
    {
        owner->ai->barraTurno += owner->ai->velocidade;
    }
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


Entidade* aiJogador::escolherDoInventario(Entidade* owner)
{
    static const int LARGURA_INVENTARIO = 40;
    static const int ALTURA_INVENTARIO = 12;
    for (int x = (engine.mapa->largura - LARGURA_INVENTARIO) / 2; x < LARGURA_INVENTARIO; x++)
    {
        for (int y = (engine.mapa->altura - ALTURA_INVENTARIO) / 2; y < LARGURA_INVENTARIO; y++)
        {
            mvprintw(y, x, "#");
        }
    }//DESENHAR A MOLDURA DO INVENTARIO
    int atalho = 'a';
    int i = 1;
    int x = (engine.mapa->largura - LARGURA_INVENTARIO) / 2;
    int y = (engine.mapa->altura - ALTURA_INVENTARIO) / 2;
    for (int j = 0; j < owner->container->inventario.size();j++)
    {
        mvprintw(y + j + 1, x + 1, "(%c)- %c", atalho, owner->container->inventario[j]->nome);
        atalho++;
    }
    refresh();/*
    int key = getch();
    while (key < 97 || key > 122)
    {
        if (key > 96 || key < 123)
        {
            int entidadeIndex = key - 'a';
            if (entidadeIndex >= 0 && entidadeIndex < owner->container->inventario.size())
            {
                return owner->container->inventario[entidadeIndex];
            }
        }*/
        return NULL;
    
    
}

aiMonstro::aiMonstro(float velocidade)
{
    this->velocidade = velocidade;
    barraTurno = 0;
}

void aiMonstro::atualizar(Entidade* owner)
{
    if (owner->ai->barraTurno >= 1)
    {
        if (owner->destrutivel && owner->destrutivel->morreu())
        {
            return;
        }
        moverOuAtacar(owner, engine.jogador);
        engine.log->inserirmsg("Turno do monstro finalizado");
        owner->ai->barraTurno -= 1;
    }
    else
    {
        owner->ai->barraTurno += velocidade;
    }
}

bool aiMonstro::moverOuAtacar(Entidade *owner,Entidade *alvo)
{
    
    owner->caminho = engine.pathMapa->acharCaminho(owner, alvo);
    for (int i = 0; i < owner->caminho.size(); i++)
    {
        engine.log->inserirmsg("Caminho[" + std::to_string(i) + "] X:" + std::to_string(owner->caminho[i]->x) + "Y:" + std::to_string(owner->caminho[i]->y));
    }
    if (owner->caminho.size() > 1 && engine.mapa->podeAndar(owner->caminho[0]->x, owner->caminho[0]->y) 
        &&  owner->caminho[0]->x != alvo->x && owner->caminho[0]->y != alvo->y)
    {
        owner->x = owner->caminho[0]->x;
        owner->y = owner->caminho[0]->y;
    }
    else if (owner->caminho[0]->x == alvo->x && owner->caminho[0]->y == alvo->y)
    {
        owner->atacador->atacar(owner, alvo);
    }
    return true;
}
