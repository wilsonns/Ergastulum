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

void AI::atualizar()
{
    pa = 5 * (self->atributos["Destreza"]->nivelAjustado + self->atributos["Agilidade"]->nivelAjustado);
}

float AI::condicaoFisica()
{
    return self->destrutivel->hp / self->destrutivel->hpMax;
}

aiJogador::aiJogador(Entidade* self)
{
    this->self = self;
    alvo = NULL;
}

void aiJogador::atualizar()
{
    AI::atualizar();
    if (self->destrutivel && self->destrutivel->morreu())
    {
        return;
    }
    int dx = 0, dy = 0;//variaveis que representam para onde o jogador vai se mover,variando de -1 a 1

    if (engine.mouse.mbutton)
    {
        Tile *tile = engine.mapa->getTile(engine.mouse.cx, engine.mouse.cy);
        if (tile->ocupante != NULL)
        {

            Entidade* entidade = tile->ocupante;
            
            static const int LARGURA_INVENTARIO = 50;
            static const int ALTURA_INVENTARIO = 14;
            
            TCODConsole con(LARGURA_INVENTARIO, ALTURA_INVENTARIO);

            con.setDefaultForeground(TCODColor(200, 180, 50));
            con.printFrame(0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, true, TCOD_BKGND_DEFAULT, entidade->nome.c_str());

            TCODConsole::blit(&con, 0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, TCODConsole::root, 10, engine.altura / 2 - ALTURA_INVENTARIO);
            TCODConsole::flush();


            TCOD_key_t key;
            TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
            if (key.vk == TCODK_ESCAPE)
            {

            }
        }
        else if (engine.debug == true && tile->ocupante == NULL)
        {
            Entidade* entidade = new Entidade(engine.mouse.cx, engine.mouse.cy, 'D', 5, 5, "Debugão",TCOD_color_add(TCOD_red,TCOD_black));
            entidade->destrutivel = new Destrutivel(entidade, 1, 1, 1);
            entidade->atacador = new Atacador(entidade, 1, 1, 1);
            entidade->ai = new aiMonstro(entidade, 1);
            engine.mapa->mover(engine.mouse.cx, engine.mouse.cy, entidade);
            engine.entidades.push_back(entidade);
        }
    }

    switch (engine.ultimoBotao.vk)
    {
    case TCODK_UP:
    case TCODK_KP8:
        dy = -1;
        break;
    case TCODK_DOWN:
    case TCODK_KP2:
        dy = 1;
        break;
    case TCODK_LEFT:
    case TCODK_KP4:
        dx = -1;
        break;
    case TCODK_RIGHT:
    case TCODK_KP6:
        dx = 1;
        break;
    case TCODK_KP7:
        dx = -1;
        dy = -1;
        break;
    case TCODK_KP9:
        dx = 1;
        dy = -1;
        break;
    case TCODK_KP1:
        dx = -1;
        dy = 1;
        break;
    case TCODK_KP3:
        dx = 1;
        dy = 1;
        break;
    case TCODK_CHAR:
        botaoAcao(engine.ultimoBotao.c);
        break;
    case TCODK_F1:
        engine.rodando = false;
        break;
    default:
        break;
    }
    if (dx != 0 || dy != 0)
    {
        moverOuAtacar(self->x + dx, self->y + dy);
    }
}

bool aiJogador::moverOuAtacar(int xalvo, int yalvo)
{
    if(engine.mapa->eParede(xalvo,yalvo))
    {
        return false;
    }
    for (std::vector<Entidade*>::iterator it = engine.entidades.begin(); it != engine.entidades.end(); it++)
    {
        Entidade* entidade = *it;
        if(entidade->x == xalvo && entidade->y == yalvo && entidade->destrutivel && !entidade->destrutivel->morreu() && entidade != self)
        {
            self->atacador->atacar(entidade);
            return false;
        }
    }
    engine.mapa->mover(xalvo, yalvo, self);
    self->x = xalvo;
    self->y = yalvo;
    engine.statusJogo = Engine::TURNO_INIMIGO;
    return true;
}

Item* aiJogador::escolherDoInventario(Container* container, bool inventarioDoJogador)
{
    static const int LARGURA_INVENTARIO = 50;
    static const int ALTURA_INVENTARIO = 14;
    static TCODConsole con(LARGURA_INVENTARIO, ALTURA_INVENTARIO);

    con.setDefaultForeground(TCODColor(200,180,50));
    con.printFrame(0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, true, TCOD_BKGND_DEFAULT, "inventario");
    if (inventarioDoJogador)
    {
        con.printf(35, ALTURA_INVENTARIO - 1, "Peso:%i/%i", engine.jogador->container->pesoAtual, engine.jogador->container->tamanho);
    }
    int atalho = 'a';
    int y = 1;
    for (std::vector<Item*>::iterator it=container->inventario.begin();it != container->inventario.end();it++)
    {
        Item* entidade = *it;
        con.setDefaultForeground(TCOD_white);
        con.printf(2, y, "(%c) - %s",atalho,entidade->nome.c_str());
        atalho++;
        y++;
    }
    TCODConsole::blit(&con, 0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, TCODConsole::root, 10, engine.altura / 2 - ALTURA_INVENTARIO);
    TCODConsole::flush();

    TCOD_key_t key;
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
    if (key.vk == TCODK_CHAR)
    {
        int itemIndex = key.c - 'a';
        if (itemIndex >= 0 && itemIndex < container->inventario.size())
        {
            return container->inventario[itemIndex];
        }
    }
    return NULL;
}

Entidade* aiJogador::mirar(int alcance)
{
    engine.cursx = self->x;
    engine.cursy = self->y;
    bool buscando = true;
    engine.cursVisivel = true;
    while (buscando)
    {
        engine.render();
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        switch (key.vk)
        {
        case TCODK_UP:
            if (self->distanciaDiag(self->x, self->y, engine.cursx, engine.cursy - 1) < alcance)
                {
                    engine.cursy -= 1;
                }
            break;

        case TCODK_DOWN:
            if (self->distanciaDiag(self->x, self->y, engine.cursx, engine.cursy + 1) < alcance)
                {
                    engine.cursy += 1;
                }
           break;

        case TCODK_LEFT:

            if (self->distanciaDiag(self->x, self->y, engine.cursx-1, engine.cursy) < alcance)
            {
                engine.cursx -= 1;
            }
            break;

        case TCODK_RIGHT:

            if (self->distanciaDiag(self->x, self->y, engine.cursx + 1, engine.cursy) < alcance)
            {
                engine.cursx += 1;
            }
            break;
        case TCODK_ESCAPE:
            buscando = false;
            break;
        case TCODK_ENTER:
            Tile* tile = engine.mapa->getTile(engine.cursx, engine.cursy);
            if (tile->ocupante)
            {

                engine.cursVisivel = false;
                int X = tile->ocupante->x - self->x;
                int Y = tile->ocupante->y - self->y;
                int x = pow((double)X, 2);
                int y = pow((double)Y, 2);
                int d = abs(sqrt((double)x +(double)y));
                double anguloRadiano = atan2((double)X, (double)Y);
                double anguloGraus = anguloRadiano * 180 / 3.14;
                engine.logger->debugLog("Radianos: {}", std::to_string(anguloRadiano));
                engine.logger->debugLog("Graus: {}", std::to_string(anguloGraus));
                return tile->ocupante;
            }
            break;
        }
    }
    engine.cursVisivel = false;


    Entidade * fodase = NULL;
    return fodase;
}

void aiJogador::mostrarPersonagem()
{
    static const int LARGURA_INVENTARIO = 50;
    static const int ALTURA_INVENTARIO = 14;
    static TCODConsole per(LARGURA_INVENTARIO, ALTURA_INVENTARIO);

    per.setDefaultForeground(TCODColor(200, 180, 50));
    per.printFrame(0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, true, TCOD_BKGND_DEFAULT, engine.jogador->nome.c_str());
    per.printf(1, 1, "Atributos");
    int i = 3;
    for (auto x:self->atributos)
    {
        per.printf(1, i, "%s: %i/%i", x.first.c_str(), x.second->nivelBase, x.second->nivelAjustado);
        i++;
    }
    per.printf(30, 3, "Hp:%i/%i", self->destrutivel->hp, self->destrutivel->hpMax);
    i = 5;
    for (auto x : self->habilidades)
    {
        per.printf(1, i, "%s: %i/%i", x.first.c_str(), x.second->nivelBase, x.second->nivelAjustado);
        i++;
    }

    TCOD_key_t key;
    TCODConsole::blit(&per, 0, 0, LARGURA_INVENTARIO, ALTURA_INVENTARIO, TCODConsole::root, 10, engine.altura / 2 - ALTURA_INVENTARIO, 0.9f , 0.9f);
    TCODConsole::flush();
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
    if (key.vk == TCODK_ESCAPE)
    {

    }
}

void aiJogador::botaoAcao(int ascii)
{
    switch (ascii)
    {
    case 'f':
        self->atacador->atacarRanged(mirar(5));
        break;
    case 'p'://Pegar um item no chão abaixo de vc
    {
        Tile* tile = engine.mapa->getTile(self->x, self->y);
        if (tile->itens->inventario.empty())
        {
            engine.gui->mensagem(TCOD_white, "Nao tem nada aqui para ser pego.");
        }
        else
        {
            Item* item = escolherDoInventario(tile->itens);
            if (item)
            {
                item->pegar(self);
                tile->itens->remover(item);
            }
        }
    }
    break;
    case 'i'://Abrir o inventario
    {
        Item* item = escolherDoInventario(self->container, true);
        if (item)
        {
            if (item->usar())
            {
                engine.statusJogo = Engine::TURNO_INIMIGO;
            }

        }
        break;
    }
    case 'P':
        mostrarPersonagem();
        break;
    case 'd'://Derrubar um item no local onde a entidade está
    {
        Item* item = escolherDoInventario(self->container);
        if (item)
        {
            if (item->soltar())
            {
                engine.statusJogo = Engine::TURNO_INIMIGO;
            }
        }
    }
    break;
    case 't'://Teste de criacao de janela
        if (engine.gui->janela)
        {
            delete engine.gui->janela;
            engine.gui->janela = nullptr;
        }
        else
        {
            engine.gui->janela = engine.gui->criarJanela("Fodase", 10, 10, 10, 10);
        }
        break;
    case 'x':
        engine.debug = !engine.debug;
        break;
    case'u':
        self->uparHabilidade("Ataque", 200);
        break;
    case's':
    {
        std::string q = "Qual direcao deseja atacar?";
        int largura = q.length();
        int altura = 3;

        static TCODConsole mensagem(largura, altura);
        mensagem.setDefaultForeground(TCODColor(200, 180, 50));
        mensagem.printFrame(0, 0, largura, altura, true, TCOD_BKGND_DEFAULT);
        mensagem.printf(1, 1, q.c_str());

        TCOD_key_t key;
        TCODConsole::blit(&mensagem, 0, 0, largura, altura, TCODConsole::root, 0, 0, 0.9f, 0.9f);
        TCODConsole::flush();
        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);

        switch (key.vk)
            {

            case TCODK_UP:
            case TCODK_KP8:
                self->atacador->atacar(engine.mapa->getTile(self->x, self->y - 1));
                break;
            case TCODK_DOWN:
            case TCODK_KP2:
                self->atacador->atacar(engine.mapa->getTile(self->x, self->y + 1));
                break;
            case TCODK_LEFT:
            case TCODK_KP4:
                self->atacador->atacar(engine.mapa->getTile(self->x - 1, self->y));
                break;
            case TCODK_RIGHT:
            case TCODK_KP6:
                self->atacador->atacar(engine.mapa->getTile(self->x + 1, self->y));
                break;
            case TCODK_KP7:
                break;
            case TCODK_KP9:
                break;
            case TCODK_KP1:
                break;
            case TCODK_KP3:
                break;
            default:
                break;

            }

        break;
        }
    }
}

aiMonstro::aiMonstro(Entidade* self, int inteligencia)
{
    this->self = self;
    self->adcionarAtributo("Inteligencia");
    self->modificarAtributo("Inteligencia", inteligencia);
    alvo = NULL;
}

void aiMonstro::atualizar()
{
    AI::atualizar();
    if (self->destrutivel && self->destrutivel->morreu())
    {
        return;
    }
    if (self->distancia(engine.jogador) <= self->visao)
    {
        alvo = engine.jogador;
        moverOuAtacar();
    }
    else
    {
        alvo = NULL;
    }
}

void aiMonstro::moverOuAtacar()
{
    self->caminho = engine.pathMapa->acharCaminho(self, alvo);
    if (self->caminho.size() > 1)
    {
        engine.mapa->mover(self->caminho[0]->x, self->caminho[0]->y, self);
        self->x = self->caminho[0]->x;
        self->y = self->caminho[0]->y;
    }
    else if(self->caminho.size() <= 1)
    {
        self->atacador->atacar(alvo);
    }
}

/*
Fluxograma da AI

se o bicho não tiver 
&& houver armas nas vizinhanças
{ ir até a arma
pegar a arma
equipar a arma
}
*/