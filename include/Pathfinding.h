#ifndef PATHFINDING_H
#define PATHFINDING_H

#include<main.h>

struct Nodo
{   
    int x, y; //posicao no espaço bidimensional
    int f, g, h;//F = custo para se mover nesse Nodo/ G = distancia desse nodo ao nodo inicial/ H= disantica aproximada desse nodo ao objetivo
    Nodo* pai = nullptr;//O nodo a partir do qual esse nodo foi visitado

    bool operator ==(const Nodo& outro) const {
        return x == outro.x && y == outro.y;
    }//faz com que o operador == compare os valores x e y dos nodos
    bool operator !=(const Nodo& outro) const {
        return x != outro.x || y == outro.y;
    }//idem acima

    Nodo operator =(Nodo outro) {
        x = outro.x;
        y = outro.y;
        return outro;
    }//idem acima
    
    bool operator <(const Nodo& outro) const {
        return f < outro.f;
    }
    
    std::vector<Nodo*> vizinhos;//Vetor que contem os 8(ou 4) vizinhos desse nodo
};



class Pathfinding
{
public:
    Pathfinding();//ctor
    ~Pathfinding();//dtor

    Nodo* nodos;//cria o array que contem todos os nodos do mapa

    ///LISTAS 
    std::list<Nodo*> aberta;//declara a lista aberta de ndoos a serem analizados
    std::list<Nodo*> fechada;//declara a lista fechada de nodos que ja forma analizados

    ///F G H
    inline int calcularF(Nodo* nodo)
    {
        nodo->f = (nodo->g + nodo->h);
        return nodo->f;
    }
    inline int calcularG(Nodo* nodo, Nodo* inicio)
    {
        if ((
            ((nodo->pai->x == nodo->x - 1) && (nodo->pai->y == nodo->y - 1))
            ||
            ((nodo->pai->x == nodo->x - 1) && (nodo->pai->y == nodo->y + 1))
            ||
            ((nodo->pai->x == nodo->x + 1) && (nodo->pai->y == nodo->y + 1))
            ||
            ((nodo->pai->x == nodo->x + 1) && (nodo->pai->y == nodo->y - 1))
            ))
        {
            nodo->g = nodo->pai->g + 14;
            return nodo->g;
        }
        else
        {

            nodo->g = nodo->pai->g + 10;
            return nodo->g;
        }
    }
    inline int calcularH(Nodo* nodo, Nodo* objetivo)
    {
        int dx = nodo->x - objetivo->x;
        int dy = nodo->y - objetivo->y;
        int distancia = (int)(sqrtf((dx * dx) + (dy * dy)));
        return distancia*10;
    }

    bool compararF(Nodo l, Nodo r);//Compara o valor F de dois nodos e retorna verdadeiro se forem iguais, falso se não forem

    std::list<Nodo*> organizarPorF(std::list<Nodo*> lista);//Recebe uma lista de nodos e reorganiza ela de acordo com os valores F de cada nodo

    bool estaNaLista(std::list<Nodo*>& lista, Nodo* nodo);//recebe uma lista e um nodo e retorna veradadeiro se esse nodo estiver na lista

    std::vector<Nodo*> acharCaminho(Entidade* self, Entidade* alvo);//retorna o vetor caminho para a entidade proprietaria

protected:

private:
};

#endif // PATHFINDING_H
