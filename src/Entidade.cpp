#include "Entidade.h"

Entidade::Entidade(int x, int y, int simbolo,int tamanho ,int visao, std::string nome, const TCODColor cor)
{
    this->x = x;
    this->y = y;
    this->simbolo = simbolo;
    this->tamanho = tamanho;
    this->nome = nome;
    this->visao = visao;
    this->cor = cor;
    denso = true;
    atacador = NULL;
    destrutivel = NULL;
    ai = NULL;
    item = NULL;
    container = NULL;
    engine.logger->debugLog("{} criado", nome);
//ctor
}

Entidade::~Entidade()
{
    if (atacador) { delete atacador; }
    if (destrutivel) { delete destrutivel; }
    if (ai) { delete ai; }
    if (item) { delete item; }
    if (container) { delete container; }
    engine.logger->debugLog("{} destruido", nome);
    //dtor
}

float Entidade::distancia(Entidade* alvo)
{
    int dx = alvo->x - x;
    int dy = alvo->y - y;
    float distancia = sqrtf(dx * dx + dy * dy);
    return distancia;
}

void Entidade::render()
{
    
    TCODConsole::root->setChar(x, y, simbolo);
    TCODConsole::root->setCharForeground(x, y, cor);
}

void Entidade::atualizar()
{
     if (ai) { ai   ->atualizar(); }
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
    if (!engine.debug)
    {
        for (unsigned short int i = 0; i < 360; i++)
        {
            unsigned int nx = 0;
            unsigned int ny = 0;
            float grau = i * 0.0174532f;
            nx = round(cos(grau) * visao) + x;
            ny = round(sin(grau) * visao) + y;

            int d = distanciaDiag(x, y, nx, ny);
            for (int j = 0; j < d; j++)
            {
                int tx = lerp(x, nx, j / ((float)d));
                int ty = lerp(y, ny, j / ((float)d));

                if (tx < 0 || tx > engine.mapa->largura) continue;
                if (ty < 0 || ty > engine.mapa->altura) continue;

                engine.mapa->tornarVisivel(tx, ty);
                engine.mapa->tornarExplorado(tx, ty);

                if (engine.mapa->eParede(tx, ty))
                {
                    break;
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < engine.mapa->largura; x++)
        {
            for (int y = 0; y < engine.mapa->altura; y++)
            {
                engine.mapa->tornarVisivel(x, y);
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
                engine.gui->mensagem(TCOD_light_yellow, "{} de {} subiu de nivel!", s_habilidade, this->nome);
            }
        }
    }
}

int Entidade::getAtributo(std::string atributo)
{
    return atributos[atributo]->nivelAjustado;
}


int Entidade::getHabilidade(std::string habilidade)
{
    return habilidades[habilidade]->nivelAjustado;
}

/*
Mobilia::Mobilia(int x, int y, int simbolo, int simboloAberto, std::string nome, const TCODColor cor)
{
    this->x = x;
    this->y = y; 
    this->simbolo = simbolo;
    this->nome = nome;
    this->cor = cor;
    
    this->ai = NULL;
    this->container = new Container(5);
    this->atacador = NULL;
    this->destrutivel = new Destrutivel(this, 1, 1, 0, this->nome + " quebrado");
    this->item = NULL;
}

bool Mobilia::abrir()
{

}

bool Mobilia::fechar()
{

}*/