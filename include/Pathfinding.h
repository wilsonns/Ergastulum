#ifndef PATHFINDING_H
#define PATHFINDING_H

#include<main.h>

struct Nodo
{   
    int x, y; //posicao no espaço bidimensional
    int f, g, h;
    Nodo* pai;

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
    int calcularF(Nodo* nodo);
    int calcularG(Nodo* nodo, Nodo* inicio);
    int calcularH(Nodo* nodo, Nodo* objetivo);


//    bool estaNaLista(std::list<Nodo*>& lista, Nodo* nodo);


   std::vector<Nodo*> acharCaminho(Entidade* owner, Entidade* alvo);
protected:

private:
};

#endif // PATHFINDING_H
