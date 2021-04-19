#include "Mapa.h"
#include "main.h"

static const int TAMANHO_MAX_SALA = 12;
static const int TAMANHO_MIN_SALA = 6;

Mapa::Mapa(int largura, int altura)
{
    this->altura = altura;
    this->largura = largura;
    tiles = new Tile[altura * largura];
    mapa = new TCODMap(largura, altura);
    TCODBsp bsp(0, 0, largura, altura);
    bsp.splitRecursive(NULL, 8, TAMANHO_MAX_SALA, TAMANHO_MAX_SALA, 1.5f, 1.5f);
    BSPListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
    std::ifstream i("data/monstro.json", std::ifstream::binary);
    i >> j;

    //ctor
}


BSPListener::BSPListener(Mapa& mapa) :mapa(mapa), nSala(0)
{
}


bool BSPListener::visitNode(TCODBsp* node, void* userData)
{
    if (node->isLeaf())
    {
        int x, y, l, a;

        TCODRandom* rng = TCODRandom::getInstance();
        l = rng->getInt(TAMANHO_MIN_SALA, node->w - 2);
        a = rng->getInt(TAMANHO_MIN_SALA, node->h - 2);
        x = rng->getInt(node->x + 1, node->x + node->w - l - 1);
        y = rng->getInt(node->y + 1, node->y + node->h - a - 1);
        mapa.criarSala(nSala == 0, x, x + l - 1, y, y + a - 1);
        if (nSala != 0)
        {
            mapa.cavar(ultx, x + l / 2, ulty, ulty);
            mapa.cavar(x + l / 2, x + l / 2, ulty, y + a / 2);
        }
        ultx = x + l / 2;
        ulty = y + a / 2;
        nSala++;
    }
    return true;
}

Mapa::~Mapa()
{
    delete[] tiles;
    delete mapa;
    //dtor
}

void Mapa::fazerParede(int x, int y)
{
    tiles[x + y * largura].passavel = false;
}

void Mapa::cavar(int x1, int x2, int y1, int y2)
{
    if (x2 < x1) {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y2 < y1) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    for (int tilex = x1; tilex <= x2; tilex++) {
        for (int tiley = y1; tiley <= y2; tiley++) {
            mapa->setProperties(tilex, tiley, true, true);
        }
    }
}

bool Mapa::eParede(int x, int y)
{
    return !mapa->isWalkable(x, y);
}

bool Mapa::podeAndar(int x, int y)
{
    if (eParede(x, y) || tiles[x+y*largura].ocupante != NULL)
    {
        return false;
    }
    return true;
}

bool Mapa::estaNoFOV(int x, int y) const
{
    if (x < 0 || x >= largura || y < 0 || y >= altura)
    {
        return false;
    }
    if (mapa->isInFov(x, y))
    {
        tiles[x + y * largura].explorado = true;
        return true;
    }
    return false;

}

bool Mapa::foiExplorado(int x, int y) const
{
    return tiles[x + y * largura].explorado;
}

void Mapa::computarFOV()
{
    mapa->computeFov(engine.jogador->x, engine.jogador->y, engine.jogador->visao);
}

void Mapa::adcmonstro(int x, int y)
{
    std::string bicho;
    if (engine.random(0, 2, 0) == 0)
    {
        bicho = "Orc";
    }
    else
    {
        bicho = "Troll";
    }

    int simbolo = j[bicho]["simbolo"].get<int>();
    std::string nome = j[bicho]["nome"].get<std::string>();
    Entidade* monstro = new Entidade(x, y, simbolo, nome, TCOD_darker_green);
    monstro->visao = 5;
    monstro->destrutivel = new destrutivelMonstro(monstro,4, 2, 2, "Cadavi");
    monstro->atacador = new Atacador(monstro);
    monstro->container = new Container(5);
    monstro->ai = new aiMonstro(1);
    monstro->ai->faccao = ORCS;
    engine.entidades.push_back(monstro);
}

void Mapa::adcionarItem(int x, int y, int simbolo, int tipo, std::string nome, int valor, const TCODColor& cor)
{
    Entidade* item = new Entidade(x, y, simbolo, nome, cor);
    item->denso = false;
    if (tipo == POCAO)
    {
        item->pegavel = new Curador(valor);
        item->pegavel->tipo = tipo;
    }
    else if(tipo == ARMA)
    {
        item->pegavel = new Arma(valor);
        item->pegavel->tipo = tipo;
    }
    else if (tipo == ARMADURA)
    {
        item->pegavel = new Armadura(valor);
        item->pegavel->tipo = tipo;
    }
    else
    {
        delete item;
        return;
    }
    engine.entidades.push_back(item);
}

void Mapa::criarSala(bool primeiro, int x1, int x2, int y1, int y2)
{
    cavar(x1, x2, y1, y2);
    dungeon.push_back(new Sala(x1, y1, x2, y2));
    if (primeiro)
    {
        engine.jogador->x = ((x2 - x1) / 2) + x1;
        engine.jogador->y = ((y2 - y1) / 2) + y1;
    }
}

void Mapa::render()
{
    static const TCODColor paredeEscura(0, 0, 100);
    static const TCODColor chaoEscuro(50, 50, 150);
    static const TCODColor paredeClara(130, 110, 50);
    static const TCODColor chaoClaro(200, 180, 50);

    for (int x = 0; x < largura; x++)
    {
        for (int y = 0; y < altura; y += 1)
        {
            if (!engine.debug)
            {
                if (estaNoFOV(x, y))
                {
                    TCODConsole::root->setCharBackground(x, y, eParede(x, y) ? TCOD_lighter_grey : TCOD_lightest_gray);
                }

                else if (!estaNoFOV(x, y) && foiExplorado(x, y))
                {
                    TCODConsole::root->setCharBackground(x, y, eParede(x, y) ? TCOD_darkest_grey : TCOD_darker_gray);
                }
            }
            if (engine.debug)
            {
                TCODConsole::root->setCharBackground(x, y, eParede(x, y) ? paredeEscura : chaoEscuro);
            }

        }
    }
}

