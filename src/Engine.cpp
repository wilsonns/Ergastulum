#include "Engine.h"
#include "main.h"

Engine::Engine(int largura, int altura)
{
    srand(time(NULL));

    int dGdP = 1;
    int dBal = 1;
    int bGdP = -6;
    int bBal = -5;
    bool primeiro = true;

    for (int i = 1; i <= 40; i++)
    {
        if (primeiro)
        {
            danoGdP.emplace(i, std::to_string(dGdP) + "D" + std::to_string(bGdP));
            danoBal.emplace(i, std::to_string(dBal) + "D" + std::to_string(bBal));
            primeiro = false;
            continue;
        }
        if (i % 2 != 0)
        {
            bGdP++;
            if (i < 9)
            {
                bBal++;
            }
        }
        if (i >= 0)
        {
            bBal++;
        }
        if (bGdP > 2)
        {
            bGdP = -1;
            dGdP += 1;
        }
        if (bBal > 2)
        {
            bBal = -1;
            dBal += 1;
        }

        danoGdP.emplace(i, std::to_string(dGdP) + "D" + std::to_string(bGdP));
        danoBal.emplace(i, std::to_string(dBal) + "D" + std::to_string(bBal));
    }


    this->largura = largura;
    this->altura = altura;
    
    cursx = cursy = 5;
    cursSimb = 'X';
    cursS = 0;
    cursVisivel = false;
    //TCOD_console_set_custom_font("terminal.png", TCOD_FONT_LAYOUT_TCOD,16,16);
   
    TCODConsole::initRoot(largura, altura, "Ergastulum", false);

    materiais.emplace("Madeira",new Material("Madeira",TCOD_darker_sepia, 1.0f));
    materiais.emplace("Ferro",new Material("Ferro", TCOD_grey, 2.0f));
    materiais.emplace("Carne",new Material("Carne", TCOD_pink, 0.2f));
    materiais.emplace("Vidro",new Material("Vidro", TCOD_light_cyan, 0.1f));
    
    logger = new LOGGER();
    
    gui = new GUI();
    
    
    jogador = new Entidade(1, 1,'@' ,5,3,"Jogador",TCOD_red);
    jogador->ai = new aiJogador(jogador);
    jogador->container = new Container(5*jogador->getAtributo(ST));
    jogador->adcionarHabilidade("Espada", 13);

    mapa = new Mapa(largura, 43);
    pathMapa = new Pathfinding();

    mapa->mover(jogador->x, jogador->y, jogador);

    entidades.push_back(jogador);
  
    mapa->adcionarItem(mapa->dungeon[0]->xcentro + 1, mapa->dungeon[0]->ycentro + 1, '/',"Espada de Xessus","Espada","Uma espada abencoada por xessus", 5, TCOD_black,0);
    mapa->adcionarItem(mapa->dungeon[0]->xcentro - 1, mapa->dungeon[0]->ycentro - 1, ')', "Arco", "Arco", "Um arco muito foda!", 0, TCOD_lightest_red, 0);
    mapa->getTile(mapa->dungeon[0]->xcentro - 1, mapa->dungeon[0]->ycentro - 1)->itens->inventario[0]->eRanged = true;
    mapa->getTile(mapa->dungeon[0]->xcentro - 1, mapa->dungeon[0]->ycentro - 1)->itens->inventario[0]->eArma = true;
    for (int i = 10; i < 30;i++)
    {
        mapa->fazerParede(i, 15, materiais["Vidro"]);
        mapa->getTile(i, 15)->terreno->tornarNaoOpaco();
    }
    mapa->fazerPorta(16, 15, materiais["Madeira"]);
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
        if (mapa->eVisivel(entidade->x, entidade->y)||debug)
        {
            entidade->render();
        }
    }
    gui->render();

    if (cursVisivel)
    {

        TCODConsole::root->setChar(cursx - 1, cursy - 1, 218);
        TCODConsole::root->setCharForeground(cursx - 1, cursy - 1, TCOD_dark_gray);
        

        TCODConsole::root->setChar(cursx + 1, cursy + 1, 217);
        TCODConsole::root->setCharForeground(cursx + 1, cursy + 1, TCOD_dark_gray);


        TCODConsole::root->setChar(cursx + 1, cursy - 1, 191);
        TCODConsole::root->setCharForeground(cursx + 1, cursy - 1, TCOD_dark_gray);


        TCODConsole::root->setChar(cursx - 1, cursy + 1, 192);
        TCODConsole::root->setCharForeground(cursx - 1, cursy + 1, TCOD_dark_gray);
    }
    root->flush();

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
                if (entidade->morreu())
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
    if (minimo > maximo)
    {
        int tmp = maximo;
        maximo = minimo;
        minimo = tmp;
    }
    return minimo + (rand() % maximo);
}

void Engine::mandarParaOInicio(Entidade* entidade)
{
    entidades.erase(std::find(entidades.begin(), entidades.end(), entidade));
    entidades.insert(entidades.begin(), entidade);
}