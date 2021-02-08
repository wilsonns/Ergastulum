#ifndef PATHFINDING_H
#define PATHFINDING_H

#include<main.h>

struct Nodo
{   
    int x, y; //posicao no espaço bidimensional
    int f, g, h;
    bool visitado;
    Nodo* pai = nullptr;

    bool operator ==(const Nodo& outro) const {
        return x == outro.x && y == outro.y;
    }
    bool operator !=(const Nodo& outro) const {
        return x != outro.x || y == outro.y;
    }

    Nodo operator =(Nodo outro) {
        x = outro.x;
        y = outro.y;
        return outro;
    }
    
    bool operator <(const Nodo& outro) const {
        return f < outro.f;
    }
    
    std::vector<Nodo*> vizinhos;
};



class Pathfinding
{
public:
    Pathfinding();
    ~Pathfinding();

    void atualizar();

    Nodo* nodos;

    ///LISTAS 
    std::list<Nodo*> aberta;
    std::list<Nodo*> fechada;

    ///F G H
    inline int calcularF(Nodo* nodo)
    {
        nodo->f = nodo->g + nodo->h;
        return nodo->f;
    }
    inline int calcularG(Nodo* nodo, Nodo* inicio)
    {
        int dx = nodo->x - inicio->x;
        int dy = nodo->y - inicio->y;
        int distancia = sqrt((dx * dx) + (dy * dy));
        nodo->g = nodo->pai->g + distancia;
        return nodo->g;
    }
    inline int calcularH(Nodo* nodo, Nodo* objetivo)
    {
        int dx = objetivo->x - nodo->x;
        int dy = objetivo->y - nodo->y;
        int distancia = sqrt((dx * dx) + (dy * dy));
        return distancia;
    }

    bool compararF(Nodo l, Nodo r);

    std::list<Nodo*> organizarPorF(std::list<Nodo*> lista);

    bool estaNaLista(std::list<Nodo*>& lista, Nodo* nodo);


   std::vector<Nodo*> acharCaminho(Entidade* owner, Entidade* alvo);
protected:

private:
};

#endif // PATHFINDING_H
