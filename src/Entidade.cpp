#include "Entidade.h"

Entidade::Entidade(int x, int y, const char *nome, char simbolo)
{
    this->x = x;
    this->y = y;
    this->nome = nome;
    this->simbolo = simbolo;
    visao = 6;
    atacador = NULL;
    destrutivel = NULL;
    ai = NULL;
    pegavel = NULL;
    container = NULL;
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
    if (engine.mapa->eVisivel(x,y))
    {
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "%c", simbolo);
        attroff(COLOR_PAIR(1));
    }
}

void Entidade::atualizar()
{
    if(ai) ai->atualizar(this);
    FOV();
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

void Entidade::FOV()
{
    if (ai == engine.jogador->ai)
    {
        for (int i = 0; i < engine.mapa->largura; i++)
        {
            for (int j = 0; j < engine.mapa->altura; j++)
            {
                engine.mapa->tornarNaoVisivel(i, j);
            }
        }
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
                    engine.mapa->tornarExplorado(tx, ty);
                    engine.mapa->tornarVisivel(tx, ty);
                    break;
                }
                engine.mapa->tornarExplorado(tx, ty);
                engine.mapa->tornarVisivel(tx, ty);


            }
        }
    }
}
