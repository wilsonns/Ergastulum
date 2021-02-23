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

float AI::condicaoFisica(Entidade* self)
{
    return self->destrutivel->hp / self->destrutivel->hpMax;
}//retorna um numero de 0 a 1 baseado na condição fisica da entidade

float AI::forcaPercebida(Entidade* self)
{
    return self->atacador->forcaBase * condicaoFisica(self);
}

float AI::perigoPercebido(Entidade* self)
{
    return (self->destrutivel->resistencia * self->atacador->forca) * condicaoFisica(self);
}

aiJogador::aiJogador(float velocidade)
{
    alvo = NULL;
 }

void aiJogador::atualizar(Entidade* self)
{
    if (self->destrutivel && self->destrutivel->morreu())
    {
        return;
    }
    int dx = 0, dy = 0;//variaveis que representam para onde o jogador vai se mover,variando de -1 a 1
    switch (engine.ultimoBotao.vk)
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
    case TCODK_CHAR:
        botaoAcao(self, engine.ultimoBotao.c);
        break;
    default:
        break;
    }
    if (dx != 0 || dy != 0)
    {
        moverOuAtacar(self, self->x + dx, self->y + dy);
        engine.mapa->computarFOV();
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
    engine.statusJogo = Engine::TURNO_INIMIGO;
    return true;
}

Entidade* aiJogador::escolherDoInventario(Entidade* self)
{
    static const int LARGURA_INVENTARIO = 50;
    static const int ALTURA_INVENTARIO = 14;
    static TCODConsole con(LARGURA_INVENTARIO, ALTURA_INVENTARIO);

    con.setDefaultForeground(TCODColor(200,180,50));
    con.printFrame(0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, true, TCOD_BKGND_DEFAULT, "inventario");
    

   
    int atalho = 'a';
    int y = 1;
    for (Entidade** it=self->container->inventario.begin();it!=self->container->inventario.end();it++)
    {
        Entidade* entidade = *it;
        con.setDefaultForeground(entidade->cor);
        con.printf(2, y, "(%c) %s",atalho,entidade->nome);
        atalho++;
        y++;
    }
    TCODConsole::blit(&con, 0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, TCODConsole::root, 10, engine.altura / 2-ALTURA_INVENTARIO);
    TCODConsole::flush();

    TCOD_key_t key;
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
    if (key.vk == TCODK_CHAR)
    {
        int entidadeIndex = key.c - 'a';
        if (entidadeIndex >= 0 && entidadeIndex < self->container->inventario.size())
        {
            return self->container->inventario.get(entidadeIndex);
        }
    }
    return NULL;
}
void aiJogador::botaoAcao(Entidade* self, int ascii)
{
    switch (ascii)
    {
    case 'g':
    case 'G'://Pegar um item no chão abaixo de vc
    {
        bool achado = false;
        for (Entidade** iterator = engine.entidades.begin();iterator != engine.entidades.end();iterator++)
        {
            Entidade* entidade = *iterator;
            {
                if (entidade->pegavel && entidade->x == self->x && entidade->y == self->y)
                {
                    if (entidade->pegavel->pegar(entidade, self))
                    {
                        achado = true;
                        engine.gui->mensagem(TCOD_white, "%s pega o %s!", self->nome, entidade->nome);
                        break;
                    }
                    else if (!achado)
                    {
                        achado = true;
                        engine.gui->mensagem(TCOD_white, "Seu inventario esta cheio!");
                    }
                }
                if (!achado)
                {
                    engine.gui->mensagem(TCOD_white, "Nao tem nada para pegar aqui!");
                }
            }
        }
    }
    break;
    case 'i':
    case 'I'://Abrir o inventario
    {
        Entidade* entidade = escolherDoInventario(self);
        if (entidade)
        {
            if (entidade->pegavel->usar(entidade, self))
            {
                engine.statusJogo = Engine::TURNO_INIMIGO;
            }

        }
        break;
    }
    case 'c':
    case 'C'://Não lembro o que isso era pra fazer :p
    {

    }break;
    case 'd':
    case 'D'://Derrubar um item no local onde a entidade está
    {
        Entidade* entidade = escolherDoInventario(self);
        if (entidade)
        {
            if (entidade->pegavel->soltar(entidade, self))
            {
                engine.statusJogo = Engine::TURNO_INIMIGO;
            }
        }
    }break;
    }
}


aiMonstro::aiMonstro(float velocidade)
{
    alvo = NULL;
}

void aiMonstro::atualizar(Entidade* self)
{
        if (self->destrutivel && self->destrutivel->morreu())
        {
            return;
        }
        self->FOV(self);
        moverOuAtacar(self, self->ai->alvo);
}

void aiMonstro::moverOuAtacar(Entidade *self,Entidade *alvo)
{
    if (self->arma == NULL && self->container->contemArma(self))
    {
        for (Entidade** it = self->container->inventario.begin(); it != self->container->inventario.end();it++)
        {
            Entidade* entidade = *it;
            if (entidade->pegavel->tipo == 2)
            {
                entidade->pegavel->usar(entidade, self);
            }
        }
    }
    acharAlvo(self);
    
    if (alvo)
    {
        self->caminho = engine.pathMapa->acharCaminho(self, alvo);
        if (self->caminho.size() > 1 && engine.mapa->podeAndar(self->caminho[0]->x, self->caminho[0]->y)
            && self->caminho[0]->x != alvo->x && self->caminho[0]->y != alvo->y)
        {
            self->x = self->caminho[0]->x;
            self->y = self->caminho[0]->y;
        }
        else if (self->caminho.size() <= 1)
        {
            if (self->x == alvo->x && self->y == alvo->y && alvo->pegavel)
            {
                alvo->pegavel->pegar(alvo, self);
                return;
            }
            if (alvo->pegavel && !alvo->denso)
            {
                self->x = self->caminho[0]->x;
                self->y = self->caminho[0]->y;
                return;
            }
            self->atacador->atacar(self, alvo);
        }
        else if (self->caminho.size() == 0)
        {
            return;
        }
    }
    return ;
}

void aiMonstro::acharAlvo(Entidade* self)
{
    if (self->ai->inteligencia >= 1)
    {
        if (self->arma == NULL && !self->container->contemArma(self))
        {
            int menorD = 999;//a menor distancia entre a entidade e uma arma na sua lista de entidades proximas
            for (Entidade** it = self->ai->entidadesProximas.begin(); it != self->ai->entidadesProximas.end();it++)
            {
                Entidade* entidade = *it;
                if (entidade->pegavel && entidade->pegavel->tipo == 2)
                {
                    int dx = entidade->x - self->x;
                    int dy = entidade->y - self->y;
                    int distancia = sqrt((dx * dx) + (dy * dy));
                    if (distancia < menorD)
                    {
                        menorD = distancia;
                        self->ai->alvo = entidade;
                    }
                }
            }

        }
        else if (self->arma)
        {
            int menorD = 999;//a menor distancia entre a entidade e uma arma na sua lista de entidades proximas
            for (Entidade** it = self->ai->entidadesProximas.begin(); it != self->ai->entidadesProximas.end();it++)
            {
                Entidade* entidade = *it;
                if (entidade->destrutivel && !entidade->destrutivel->morreu())
                {
                    int dx = entidade->x - self->x;
                    int dy = entidade->y - self->y;
                    int distancia = sqrt((dx * dx) + (dy * dy));
                    if (distancia < menorD)
                    {
                        menorD = distancia;
                        self->ai->alvo = entidade;
                    }
                }
            }
        }
    }
}

/*
Fluxograma da AI

se o bicho não tiver arma && houver armas nas vizinhanças
{ ir até a arma
pegar a arma
equipar a arma
}
*/