#include "Mapa.h"
#include "main.h"

Tile::Tile()
{
    //dummy
}

Tile::Tile(int simbolo, TCODColor cor)
{
    this->simbolo = simbolo;
    this->cor = cor;
    itens = new Container(10);
    int rand = engine.random(0, engine.materiais.size(), 0);
    terreno = new Parede('#',engine.materiais["Madeira"]);
    if (itens->inventario.size() > 0)
    {
        engine.logger->debugLog("Deu ruim mano");
    }
    //ctor
}

Tile::~Tile()
{
    delete itens;
    //dtor
}

Mapa::Mapa(int largura, int altura)
{
    this->altura = altura;
    this->largura = largura;

    std::ifstream i("data/monstro.json", std::ifstream::binary);
    i >> j;
    for (auto& i : j.items())
    {
        monstros.push_back(i.key());
    }
    //tiles = new Tile[altura * largura];

    for (int i = 0; i < altura * largura; i++)
    {
        tiles.push_back(new Tile('#',TCOD_blue));
    }
    mapa = new TCODMap(largura, altura);
    /*TCODBsp bsp(0, 0, largura, altura);
    bsp.splitRecursive(NULL, 8, TAM_MAX, TAM_MAX, 1.5f, 1.5f);
    BSPListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
    */
    criarSala(true, 10, 20, 10, 20);

    engine.logger->debugLog("Mapa criado!");

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
        l = rng->getInt(TAM_MIN, node->w - 2);
        a = rng->getInt(TAM_MIN, node->h - 2);
        x = rng->getInt(node->x + 1, node->x + node->w - l - 1);
        y = rng->getInt(node->y + 1, node->y + node->h - a - 1);
        bool f = true;
        mapa.criarSala(f , x, x + l - 1, y, y + a - 1);
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
    for (auto i : tiles)
    {
        delete i;
    }
    delete mapa;
    //dtor
}

void Mapa::fazerParede(int x, int y,Material*material)
{
    int index = x + y * largura;
    if (tiles[index]->terreno)
    {
        delete tiles[index]->terreno;
    }
    tiles[index]->terreno = new Parede('#', material);

    //tiles[index]->passavel = false;
}

void Mapa::fazerPorta(int x, int y, Material* material)
{
    int index = x + y * largura;
    if (tiles[index]->terreno)
    {
        delete tiles[index]->terreno;
    }
    tiles[index]->terreno = new Porta('+', '/', engine.materiais["Madeira"]);
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
            int index = tilex + tiley * largura;
            Material* mat = tiles[index]->terreno->material;
            delete tiles[index]->terreno;
            int rand = engine.random(0, engine.materiais.size(), 0);
            tiles[index]->terreno = new Chao('.',mat);
        }
    }
}

void Mapa::cavar(Tile* tile)
{
    Material *mat = tile->terreno->material;
    delete tile->terreno;
    int rand = engine.random(0, engine.materiais.size(), 0);
    tile->terreno = new Chao('.', mat);
}

bool Mapa::eDenso(int x, int y)
{
    int index = x + y * largura;
    return tiles[index]->terreno->eDenso();
}

bool Mapa::eOpaco(int x, int y)
{
    int index = x + y * largura;
    return tiles[index]->terreno->eOpaco();
}

bool Mapa::temEntidade(int x, int y)
{
    if (tiles[x + y * largura]->ocupante != NULL)
    {
        return true;
    }
    return false;
}


bool Mapa::temEntidade(int x, int y, Entidade* entidade)
{

    int index = x + y * largura;
    if (tiles[index]->ocupante == entidade)
    {
        return true;
    }
    return false;
}


bool Mapa::podeAndar(int x, int y)
{
    if (getTile(x, y)->terreno->porta && !temEntidade(x,y))
    {
        return true;
    }
    if (eDenso(x, y) || temEntidade(x,y))
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

    int index = x + y * largura;
    if (tiles[index]->visivel == true)
    {
        return true;
    }
    return false;
}

void Mapa::tornarVisivel(int x, int y)
{
    int index = x + y * largura;
    tiles[index]->visivel = true;
}

void Mapa::tornarNaoVisivel(int x, int y)
{
    int index = x + y * largura;
    tiles[index]->visivel = false;
}

void Mapa::tornarExplorado(int x, int y)
{
    int index = x + y * largura;
    tiles[index]->explorado = true;
}

bool Mapa::eVisivel(int x, int y)
{
    int index = x + y * largura;
    return tiles[index]->visivel;
}

bool Mapa::eExplorado(int x, int y)
{
    int index = x + y * largura;
    return tiles[index]->explorado;
}

Tile* Mapa::getTile(int x, int y) 
{

    int index = x + y * largura;
    return tiles[index];
}

void Mapa::adcmonstro(int x, int y)
{
    std::string bicho;
    int it = engine.random(0, monstros.size()-1, 0);
    
    bicho = monstros[it];

    std::string simb = j[bicho]["simbolo"].get<std::string>();
    int tamanho = j[bicho]["tamanho"].get<int>();
    
    std::string nome = j[bicho]["nome"].get<std::string>();

    char simbolo = simb[0];
    
    Entidade* monstro = new Entidade(x, y, simbolo,tamanho,0, nome, TCOD_darker_green);
    
    monstro->container = new Container(5);
    monstro->ai = new aiMonstro(monstro,1);
    
    mover(monstro->x,monstro->y,monstro);
    engine.entidades.push_back(monstro);
}

void Mapa::adcionarItem(int x, int y, int simbolo,std::string nome,std::string tipo,std::string descricao, int valor, const TCODColor& cor, int peso)
{
    Item* obj = new Item(nome, tipo, descricao, simbolo, cor, peso);
    if (tipo == "Espada")
    {
        obj->eArma = true;
    }
    if (getTile(x,y)->itens->adcionar(obj))
    {
        return;
    }
    delete obj;
}

void Mapa::adcionarItem(Entidade* portador, int simbolo, std::string nome, int valor, const TCODColor& cor)
{

}

void Mapa::mover(int x, int y, Entidade* ocupante)
{

    int index = x + y * largura;
    int indexocupante = ocupante->x + ocupante->y * largura;
    tiles[indexocupante]->ocupante = nullptr;
    tiles[index]->ocupante = ocupante;
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
    for (int i = 0; i < MON_MAX; i++)
    {
        int r = engine.random(0, 10, 0);
        if (r > 8)
        {
            continue;
        }
        else
        {
            adcmonstro(engine.random(x1, x2), engine.random(y1, y2));
        }
    }
}

void Mapa::render()
{
    /*
    static const TCODColor paredeEscura(0, 0, 100);
    static const TCODColor chaoEscuro(50, 50, 150);
    static const TCODColor paredeClara(130, 110, 50);
    static const TCODColor chaoClaro(200, 180, 50);
    */
    for (int x = 0; x < largura; x++)
    {
        for (int y = 0; y < altura; y += 1)
        {
            Tile* tile = getTile(x, y);
            TCODColor cor = tile->terreno->material->cor;
            if (eVisivel(x, y))
            {
//                TCODConsole::root->setCharBackground(x, y, !eDenso(x, y) ? TCOD_lighter_grey : TCOD_lightest_gray);

                TCODConsole::root->setCharBackground(x, y, cor);
                if (!tile->itens->inventario.empty())
                {
                    Item* item = tile->itens->inventario.back();
                    TCODConsole::root->setChar(x, y, item->simbolo);
                    TCODConsole::root->setCharForeground(x, y, item->cor);
                }
                else
                {
                    TCODConsole::root->setChar(x, y, tile->terreno->simbAtual);
                    TCODConsole::root->setCharForeground(x, y, TCOD_white);
                }
            }

            else if (!eVisivel(x, y) && eExplorado(x, y))
            {
                float coefCor = 0.3f;
                TCODConsole::root->setChar(x, y, tile->terreno->simbAtual);
                TCODConsole::root->setCharBackground(x, y, (cor*coefCor));
                TCODConsole::root->setCharForeground(x, y, TCOD_dark_grey);
            //    TCODConsole::root->setCharBackground(x, y, !eDenso(x, y) ? TCOD_darkest_grey : TCOD_darker_gray);
            }
        }
    }
}