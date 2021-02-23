#ifndef MAPA_H
#define MAPA_H

#include "main.h"

struct Tile
{
    bool passavel;//as entidades podem passar por aqui?
    bool explorado = false;//o jogador ja explorou aqui?
    
};

class Mapa
{
    public:

        int altura, largura;//altura e altura do mapa de jogo
        Mapa(int largura, int altura);//ctor
        virtual ~Mapa();//dtor

        ///FUN��ES
        void render();//Desenha o mapa na tela;;;;
        
        //PAREDE
        bool eParede(int x, int y); //Detecta paredes na posi��o x/y
        void fazerParede(int x, int y); //Torna x/y numa parede
        void cavar(int x1, int x2, int y1, int y2); // Tira a parede de x/y
        bool podeAndar(int x, int y); //Verifica se x/y � caminh�vel
        void criarSala(bool primeira, int x1, int x2, int y1, int y2);//Cria uma sala
        //FOV
        bool estaNoFOV(int x, int y)const; // verifica se x/y est� visivel
        void computarFOV();

        //EXPLORA��O
        bool foiExplorado(int x, int y)const;//x/y j� foi explorado? se sim, retorna verdadeiro, se n�o, falso


        //ADCIONAR ENTIDADES
        void adcmonstro(int x, int y);//adciona um monstro ao mapa
        void adcionarItem(int x, int y, int simbolo, int tipo, const char* nome, int valor, const TCODColor& cor);//adciona um item(atualmente, uma po��o de cura, o �nico item nessa porra) na posi��o x/y

    protected:
        Tile* tiles;//array de Tiles que cont�m as informa��es do mapa de jogo
        TCODMap* mapa;
    private:
};

#endif // MAPA_H
