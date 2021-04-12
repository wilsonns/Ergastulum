#include "Entidade.h"

Entidade::Entidade(int x, int y, int simbolo,std::string nome, const TCODColor cor)
{
    this->x = x;
    this->y = y;
    this->simbolo = simbolo;
    this->nome = nome;
    visao = 6;
    denso = true;
    atacador = NULL;
    destrutivel = NULL;
    ai = NULL;
    pegavel = NULL;
    container = NULL;
    //engine.logger->logar( "{} criado", nome);
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
                break;
            }
            for (std::vector<Entidade*>::iterator it = engine.entidades.begin(); it != engine.entidades.end();it++)
            {

                Entidade* entidade = *it;
                if (entidade != self)
                {
                    if (entidade->x == tx && entidade->y == ty)
                    {
                        if (std::find(self->ai->entidadesProximas.begin(), self->ai->entidadesProximas.end(), entidade) == self->ai->entidadesProximas.end())
                        {
                            self->ai->entidadesProximas.push_back(entidade);
                        }
                    }
                }

            }
        }
    }
}

void Entidade::adcionarAtributo(std::string s_atributo)
{
    Stats* o_atributo;
    atributos.emplace(s_atributo,o_atributo = new Stats());
}


void Entidade::modificarAtributo(std::string s_atributo, int valor)
{
    if (atributos.find(s_atributo) != atributos.end())
    {
        atributos[s_atributo]->nivelAjustado += valor;
    }
}


void Entidade::adcionarHabilidade(std::string s_habilidade)
{
    Habilidade* o_habilidade;
    habilidades.emplace(s_habilidade,o_habilidade = new Habilidade());
}

void Entidade::modificarHabilidade(std::string s_habilidade, int valor)
{
    if (habilidades.find(s_habilidade) != habilidades.end())
    {
        habilidades[s_habilidade]->nivelAjustado += valor;
    }
}

void Entidade::uparHabilidade(std::string s_habilidade, int xp)
{
    if (habilidades.find(s_habilidade) != habilidades.end())
    {
        habilidades[s_habilidade]->xp += xp;
        if (habilidades[s_habilidade]->xp >= habilidades[s_habilidade]->xpProx)
        {
            habilidades[s_habilidade]->nivelBase += 1;
            habilidades[s_habilidade]->nivelAjustado += 1;
            habilidades[s_habilidade]->xp -= habilidades[s_habilidade]->xpProx;
            habilidades[s_habilidade]->xpProx = (int)pow((100 * habilidades[s_habilidade]->nivelBase),1.5);
            if (this == engine.jogador)
            {
                engine.gui->mensagem(TCOD_light_yellow, "{} de {} subiu de nível!", s_habilidade, this->nome);
            }
        }
    }
}