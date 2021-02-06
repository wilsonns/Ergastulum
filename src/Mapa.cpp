#include "Mapa.h"
#include "main.h"

Mapa::Mapa(int largura, int altura)
{
    this->altura = altura;
    this->largura = largura;
    tiles = new Tile[altura*largura];
    for(int x = 0; x < largura;x++)
    {
        for (int y = 0; y < altura;y++)
        {
            tiles[x + y * largura].explorado = false;
            tiles[x + y * largura].passavel = false;
            tiles[x + y * largura].visivel = false;
        }
    }
    //ctor
}

Mapa::~Mapa()
{
    delete [] tiles;
    //dtor
}

void Mapa::fazerParede(int x, int y)
{
    tiles[x+y*largura].passavel = false;
}

void Mapa::cavar(int x, int y)
{
    tiles[x+y*largura].passavel = true;
}

bool Mapa::eParede(int x, int y)
{
    return !tiles[x+y*largura].passavel;
}

bool Mapa::podeAndar(int x, int y)
{
    if(eParede(x,y))
    {
        return false;
    }
    for(unsigned int it = 0; it < engine.entidades.size();it++)
    {
        if(engine.entidades[it]->denso && engine.entidades[it]->x == x && engine.entidades[it]->y == y)
        {
            return false;
        }
    }
    return true;
}

bool Mapa::eVisivel(int x, int y)
{
    return tiles[x + y * largura].visivel;
}

void Mapa::tornarVisivel(int x, int y)
{
    tiles[x + y * largura].visivel = true;
}


void Mapa::tornarNaoVisivel(int x, int y)
{
    tiles[x + y * largura].visivel = false;
}

bool Mapa::eExplorado(int x, int y)
{
    return tiles[x + y * largura].explorado;
}
void Mapa::tornarExplorado(int x, int y)
{
    tiles[x + y * largura].explorado = true;
}

void Mapa::render()
{
    for(int x = 0; x < largura;x++)
    {
        for(int y = 0; y < altura;y+=1)
        {
            if (eParede(x, y) && eVisivel(x, y) && eExplorado(x, y))
            {
                attron(COLOR_PAIR(1));
                mvprintw(y, x, "#");
                attroff(COLOR_PAIR(1));
            }
            else if (!eParede(x, y) && eVisivel(x, y) && eExplorado(x, y))
            {
                attron(COLOR_PAIR(1));
                mvprintw(y, x, ".");
                attron(COLOR_PAIR(1));
            } 
            else if (eParede(x, y) && !eVisivel(x, y) && eExplorado(x, y))
            {
                attron(COLOR_PAIR(2));
                mvprintw(y, x, "#");
                attroff(COLOR_PAIR(2));
            }
            else if (!eParede(x, y) && !eVisivel(x, y) && eExplorado(x, y))
            {
                attron(COLOR_PAIR(2));
                mvprintw(y, x, ".");
                attron(COLOR_PAIR(2));
            }
            
        }
    }
}
