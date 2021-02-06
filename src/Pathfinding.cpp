#include "Pathfinding.h"
#include "main.h"



Pathfinding::Pathfinding()
{
    nodos = new Nodo[engine.mapa->largura * engine.mapa->altura];
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura; y++)
        {
            nodos[x + y * engine.mapa->largura].x = x;
            nodos[x + y * engine.mapa->largura].y = y;
        }
    }
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura;y++)
        {
            if (y > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 0) + (y - 1) * engine.mapa->largura]);
            }
            if (y < engine.mapa->altura-1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 0) + (y + 1) * engine.mapa->largura]);
            }
            if (x > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y + 0) * engine.mapa->largura]);
            }

            if (y < engine.mapa->largura - 1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y + 0) * engine.mapa->largura]);
            }
        }
    }
    //CTOR
}

Pathfinding::~Pathfinding()
{
    delete[] nodos;
    //DTOR
}

void Pathfinding::atualizar()
{
}

int Pathfinding::calcularF(Nodo* nodo)
{
    nodo->f = nodo->g + nodo->h;
    return nodo->f;
}
int Pathfinding::calcularG(Nodo* nodo, Nodo* inicio)
{
    nodo->g = nodo->pai->g + 10;
    return nodo->g;
}
int Pathfinding::calcularH(Nodo* nodo, Nodo* objetivo)
{
    int dx =  objetivo->x - nodo->x;
    int dy = objetivo->y - nodo->y ;
    int distancia = sqrt((dx * dx) + (dy * dy));
    return distancia;
}

/*bool Pathfinding::estaNaLista(std::list<Nodo*>& lista, Nodo* nodo)
{

}
*/
std::vector<Nodo*> Pathfinding::acharCaminho(Entidade* owner, Entidade* alvo)
{
    /// 1.Comece pelo ponto inicial, adicionando-o à lista aberta; 
    /// 2. Olhe nos nodos ao redor e 
    /// 
    /// 
    /// 
    /// 

    Nodo* inicio = &nodos[owner->x + owner->y * engine.mapa->largura];
    Nodo* objetivo = &nodos[alvo->x + alvo->y * engine.mapa->largura];
    Nodo* atual = nullptr;
    inicio->f = 0;
    atual = inicio;

    aberta.push_back(atual);



    while (!aberta.empty() || atual != objetivo)
    {
        for (unsigned int i = 0; i < atual->vizinhos.size();i++)
        {
            atual->vizinhos[i]->pai = atual;
            atual->vizinhos[i]->g = calcularG(atual->vizinhos[i], inicio);
            atual->vizinhos[i]->h = calcularH(atual->vizinhos[i], objetivo);
            atual->vizinhos[i]->f = calcularF(atual->vizinhos[i]);
        }
    }

    std::vector<Nodo*> caminho;
    return caminho;
}

