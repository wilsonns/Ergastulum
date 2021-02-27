#include "Entidade.h"

Entidade::Entidade(int x, int y, int simbolo, const TCODColor cor)
{
    this->x = x;
    this->y = y;
    this->simbolo = simbolo;
    visao = 6;
    denso = true;
    atacador = NULL;
    destrutivel = NULL;
    ai = NULL;
    pegavel = NULL;
    container = NULL;

    //Equips
    armadura = arma = escudo = NULL;
    //ctor
}

Entidade::~Entidade()
{
    if (atacador) { delete atacador; }
    if (destrutivel) { delete destrutivel; }
    if (ai) { delete ai; }
    if (pegavel) { delete pegavel; }
    if (container) { delete container; }
    //dtor
}

void Entidade::render()
{
    TCODConsole::root->setChar(x, y, simbolo);
    TCODConsole::root->setCharForeground(x, y, cor);
}

void Entidade::atualizar()
{
     if (ai) { ai->atualizar(this); }
}

float Entidade::maximo(float a, float b)
{
    return a > b ? a : b;
}
int Entidade::distanciaDiag(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    return maximo(abs(dx), abs(dy));
}

float Entidade::lerp(float inicio, float fim, float t)
{
    return inicio + t * (fim - inicio);
}

void Entidade::FOV(Entidade* self)
{
    /*for (int i = 0; i < engine.mapa->largura; i++)
    {
        for (int j = 0; j < engine.mapa->altura; j++)
        {
            engine.mapa->tornarNaoVisivel(i, j);
        }
    }*/
    self->ai->entidadesProximas.clear();

    for (int i = 0; i < 360; i++)
    {
        int nx = 0;
        int ny = 0;
        float grau = i * GRAUPRAD;
        nx = round(cos(grau) * visao) + x;
        ny = round(sin(grau) * visao) + y;

        int d = distanciaDiag(x, y, nx, ny);
        for (int j = 0; j < d; j++)
        {
            int tx = lerp(x, nx, j / ((float)d));
            int ty = lerp(y, ny, j / ((float)d));

            if (tx < 0 || tx > engine.mapa->largura) continue;
            if (ty < 0 || ty > engine.mapa->altura) continue;

            if (engine.mapa->eParede(tx, ty))
            {
                /*engine.mapa->tornarExplorado(tx, ty);
                engine.mapa->tornarVisivel(tx, ty);*/
                break;
            }
            for (Entidade** it = engine.entidades.begin(); it != engine.entidades.end();it++)
            {

                Entidade* entidade = *it;
                if (entidade != self)
                {
                    if (entidade->x == tx && entidade->y == ty)
                    {
                        if (!self->ai->entidadesProximas.contains(entidade))
                        {
                            self->ai->entidadesProximas.push(entidade);
                        }
                    }
                }

            }
            /*
            engine.mapa->tornarExplorado(tx, ty);
            engine.mapa->tornarVisivel(tx, ty);
            */

        }
    }
}