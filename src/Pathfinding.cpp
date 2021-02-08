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
            nodos[x + y * engine.mapa->largura].visitado = false;
            nodos[x + y * engine.mapa->largura].pai = nullptr;
        }
    }
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura;y++)
        {
            if (y > 0 )
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
            if (y > 0 && x > 0 )
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y - 1) * engine.mapa->largura]);
            }
            if (y < engine.mapa->altura-1 && x > 0 )
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y + 1) * engine.mapa->largura]);
            }
            if (y > 0 && x < engine.mapa->largura-1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y - 1) * engine.mapa->largura]);
            }

            if (y < engine.mapa->altura - 1 && x < engine.mapa->largura-1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y + 1) * engine.mapa->largura]);
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


/*bool Pathfinding::estaNaLista(std::list<Nodo*>& lista, Nodo* nodo)
{

}
*/
std::vector<Nodo*> Pathfinding::acharCaminho(Entidade* owner, Entidade* alvo)
{
    // 1. Begin at the starting point A and add it to an “open list” of squares to be considered. The open list is kind of like
    //    a shopping list.Right now there is just one item on the list, but we will have more later.It contains squares that
    //    might fall along the path you want to take, but maybe not.Basically, this is a list of squares that need to be
    //    checked out.
    //    2. Look at all the reachable or walkable squares adjacent to the starting point, ignoring squares with walls, water,
    //    or other illegal terrain.Add them to the open list, too.For each of these squares, save point A as its “parent
    //    square”.This parent square stuff is important when we want to trace our path.It will be explained more later.
    //    3. Drop the starting square A from your open list, and add it to a “closed list” of squares that you don’t need to
    //    look at again for now.
    aberta.clear();
    fechada.clear();
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura; y++)
        {
            nodos[x + y * engine.mapa->largura].f = 0;
            nodos[x + y * engine.mapa->largura].g = 0;
            nodos[x + y * engine.mapa->largura].h = 0;
            nodos[x + y * engine.mapa->largura].pai = nullptr;
        }
    }

    Nodo* inicio = &nodos[owner->x + owner->y * engine.mapa->largura];
    Nodo* objetivo = &nodos[alvo->x + alvo->y * engine.mapa->largura];
    Nodo* atual = nullptr;
    inicio->f = 0;
    inicio->g = 0;
    inicio->h = calcularH(inicio,objetivo);

    atual = inicio;

    aberta.push_back(atual);

    while (!aberta.empty())
    {
        
        //std::sort(aberta.begin(), aberta.end(), [](Nodo const* l, Nodo const* r) {return l->f < r->f;});
        //aberta.sort([](const Nodo& x, const Nodo& y) {return x.f < y.f;});
        aberta = organizarPorF(aberta);
        atual = aberta.front();
        aberta.pop_front();
        fechada.push_back(atual);
        for (int i = 0; i < atual->vizinhos.size(); i++)
        {
            if (!engine.mapa->eParede(atual->vizinhos[i]->x, atual->vizinhos[i]->y)
                    && !estaNaLista(aberta, atual->vizinhos[i]) && !estaNaLista(fechada,atual->vizinhos[i]))
                {
                    atual->vizinhos[i]->pai = atual;
                    atual->vizinhos[i]->g = calcularG(atual->vizinhos[i], inicio);
                    atual->vizinhos[i]->h = calcularH(atual->vizinhos[i], objetivo);
                    atual->vizinhos[i]->f = calcularF(atual->vizinhos[i]);
                    aberta.push_back(atual->vizinhos[i]);
                }
                else if (!engine.mapa->eParede(atual->vizinhos[i]->x, atual->vizinhos[i]->y) 
                    && estaNaLista(aberta, atual->vizinhos[i]) && !estaNaLista(fechada, atual->vizinhos[i]))
                {
                    atual->vizinhos[i]->g = calcularG(atual->vizinhos[i], inicio);
                    atual->vizinhos[i]->f = calcularF(atual->vizinhos[i]);
                    atual->vizinhos[i]->pai = atual;
                }
        }
        if(atual == objetivo)
        {
            break;
        }


    }

    if(atual == objetivo)
    {
        std::vector<Nodo*> caminho;
        for (int i = 0; atual != inicio; i++)
        {
            caminho.push_back(atual);
            atual = atual->pai;
        }
        std::reverse(caminho.begin(), caminho.end());
        return caminho;
    }
    else
    {
        std::vector<Nodo*> caminho;
        return caminho;
    }
}

bool Pathfinding::estaNaLista(std::list<Nodo*>& lista, Nodo* nodo)
{
    bool encontrado = (std::find(lista.begin(), lista.end(), nodo) != lista.end());
    
    if (encontrado)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Pathfinding::compararF(Nodo l, Nodo r)
{
    if (l.f < r.f)
    {
        return true;
    }
    
    if (l.f > r.f)
    {
        return false;
    }
    return true;
}
std::list<Nodo*> Pathfinding::organizarPorF(std::list<Nodo*> lista)
{
    std::list<Nodo*> copialista;
    unsigned int tam = lista.size();
    while (copialista.size() != tam)
    {
        int menorF = 999;
        for (auto const &it: lista)
        {
            if (it->f < menorF)
            {
                menorF = it->f;
            }
        }
        std::list<Nodo*>::iterator it1 = lista.begin();
        int index = 0;
        for (auto const &it : lista)
        {
            if (lista.size() != 0)
            {
                if (it->f == menorF)
                {

                   copialista.push_back(it);
                   lista.erase(it1);
                   break;
                }
            }
            else if (lista.size() == 0)
            {
                break;
            }
            if (lista.size() != 0)
            {
                std::advance(it1, 1);
            }
            else
            {
                break;
            }
            
        }
    
    }
    return copialista;
}