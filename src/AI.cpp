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

void aiJogador::atualizar(Entidade* self)
{
    if (self->ai->barraTurno >= 1)
    {
        if (self->destrutivel && self->destrutivel->morreu())
        {
            return;
        }
        int dx = 0, dy = 0;//variaveis que representam para onde o jogador vai se mover,variando de -1 a 1
        TCOD_key_t key;
        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL,false);
        switch (key.vk)
        {
        case TCODK_UP:
            dy = -1;
            break;
        case TCODK_DOWN:
            dy = 1;
            break;
        case TCODK_LEFT:
            dx = -1;
            break;
        case TCODK_RIGHT:
            dx = 1;
            break;
        /*case 49://baixoesquerda
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
                if (engine.entidades[i]->pegavel && engine.entidades[i]->x == self->x && engine.entidades[i]->y == self->y)
                {
                    if (engine.entidades[i]->pegavel->pegar(engine.entidades[i], self))
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
            Entidade* entidade = escolherDoInventario(self);
            if (entidade)
            {
                entidade->pegavel->usar(entidade, self);

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
            break;*/
        }
        if (dx != 0 || dy != 0)
        {
            moverOuAtacar(self, self->x + dx, self->y + dy);
        }
        //engine.log->inserirmsg("Turno do jogador finalizado");
        //self->ai->barraTurno -= 1;
        //engine.gui->adcMensagem(1, "X");
    }
    else
    {
        self->ai->barraTurno += self->ai->velocidade;
    }
}

bool aiJogador::moverOuAtacar(Entidade *self, int xalvo, int yalvo)
{
    if(engine.mapa->eParede(xalvo,yalvo))
    {
        return false;
    }
    for (Entidade** iterator = engine.entidades.begin(); iterator != engine.entidades.end(); iterator++)
    {
        Entidade* entidade = *iterator;
        if(entidade->x == xalvo && entidade->y == yalvo && entidade->destrutivel && !entidade->destrutivel->morreu() && entidade != self)
        {
            self->atacador->atacar(self, entidade);
            return false;
        }
    }
    self->x = xalvo;
    self->y = yalvo;
    return true;
}


Entidade* aiJogador::escolherDoInventario(Entidade* self)
{
    static const int LARGURA_INVENTARIO = 40;
    static const int ALTURA_INVENTARIO = 12;
    for (int x = (engine.mapa->largura - LARGURA_INVENTARIO) / 2; x < LARGURA_INVENTARIO; x++)
    {
        for (int y = (engine.mapa->altura - ALTURA_INVENTARIO) / 2; y < LARGURA_INVENTARIO; y++)
        {
            //mvprintw(y, x, "#");
        }
    }//DESENHAR A MOLDURA DO INVENTARIO
    int atalho = 'a';
    int i = 1;
    int x = (engine.mapa->largura - LARGURA_INVENTARIO) / 2;
    int y = (engine.mapa->altura - ALTURA_INVENTARIO) / 2;
    for (int j = 0; j < self->container->inventario.size();j++)
    {
       // mvprintw(y + j + 1, x + 1, "(%c)- %c", atalho, self->container->inventario[j]->nome);
        atalho++;
    }
    //refresh();
    /*
    int key = getch();
    while (key < 97 || key > 122)
    {
        if (key > 96 || key < 123)
        {
            int entidadeIndex = key - 'a';
            if (entidadeIndex >= 0 && entidadeIndex < self->container->inventario.size())
            {
                return self->container->inventario[entidadeIndex];
            }
        }*/
        return NULL;
    
    
}

aiMonstro::aiMonstro(float velocidade)
{
    this->velocidade = velocidade;
    barraTurno = 0;
}

void aiMonstro::atualizar(Entidade* self)
{
    if (self->ai->barraTurno >= 1)
    {
        if (self->destrutivel && self->destrutivel->morreu())
        {
            return;
        }
        moverOuAtacar(self, engine.jogador);
        self->ai->barraTurno += 1;
    }
    else
    {
        self->ai->barraTurno += velocidade;
    }
}

bool aiMonstro::moverOuAtacar(Entidade *self,Entidade *alvo)
{
    
    self->caminho = engine.pathMapa->acharCaminho(self, alvo);
    if (self->caminho.size() > 1 && engine.mapa->podeAndar(self->caminho[0]->x, self->caminho[0]->y) 
        &&  self->caminho[0]->x != alvo->x && self->caminho[0]->y != alvo->y)
    {
        self->x = self->caminho[0]->x;
        self->y = self->caminho[0]->y;
    }
    else if (self->caminho[0]->x == alvo->x && self->caminho[0]->y == alvo->y)
    {
        self->atacador->atacar(self, alvo);
    }
    return true;
}
