#include "Mapa.h"
#include "main.h"

Mapa::Mapa(int largura, int altura)
{
    this->altura = altura;
    this->largura = largura;
    tiles = new Tile[altura*largura];
    mapa = new TCODMap(largura, altura);
    //ctor
}

Mapa::~Mapa()
{
    delete [] tiles;
    delete mapa;
    //dtor
}

void Mapa::fazerParede(int x, int y)
{
    tiles[x+y*largura].passavel = false;
}

void Mapa::cavar(int x1,int x2, int y1, int y2)
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
            mapa->setProperties(tilex, tiley, true,true);
        }
    }
}

bool Mapa::eParede(int x, int y)
{
    return !mapa->isWalkable(x,y);
}

bool Mapa::podeAndar(int x, int y)
{
    if(eParede(x,y))
    {
        return false;
    }
    for(Entidade **iterator=engine.entidades.begin();iterator!=engine.entidades.end();iterator++)
    {
        Entidade* entidade = *iterator;
        if(entidade->denso && entidade->x == x && entidade->y == y)
        {
            return false;
        }
    }
    return true;
}

bool Mapa::estaNoFOV(int x, int y) const
{
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
    mapa->computeFov(engine.jogador->x, engine.jogador->y);
}

void Mapa::adcmonstro(int x, int y)
{
    Entidade* monstro = new Entidade(x, y, 'O', TCOD_darker_green);
    monstro->destrutivel = new destrutivelMonstro(4, 2, 2, "Cadavi");
    monstro->atacador = new Atacador(2, 3);
    monstro->ai = new aiMonstro(1);
    engine.entidades.push(monstro);
}

void Mapa::adcionarItem(int x, int y)
{
    Entidade* pocaoDeCura = new Entidade(x, y,'!',TCOD_pink);
    pocaoDeCura->denso = false;
    pocaoDeCura->pegavel = new Curador(10);
    engine.entidades.push(pocaoDeCura);
}

void Mapa::render()
{
    static const TCODColor paredeEscura(0, 0, 100);
    static const TCODColor chaoEscuro(50, 50, 150);
    static const TCODColor paredeClara(130, 110, 50);
    static const TCODColor chaoClaro(200, 180, 50);

    for(int x = 0; x < largura;x++)
    {
        for (int y = 0; y < altura;y += 1)
        {
           if(estaNoFOV(x,y))
           {

            TCODConsole::root->setCharBackground(x, y, eParede(x,y)?paredeClara:chaoClaro);
            }
           else
           {
               TCODConsole::root->setCharBackground(x, y, eParede(x, y) ? paredeEscura : chaoEscuro);
           }
       
        }
    }
}
