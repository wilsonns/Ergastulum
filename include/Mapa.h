#ifndef MAPA_H
#define MAPA_H

#include "main.h"

struct Tile
{
    bool visivel;
    bool passavel;
    bool explorado;
    int tipo;
    
};

class Mapa
{
    public:
        int altura, largura;
        Tile *tiles;
        Mapa(int largura, int altura);
        virtual ~Mapa();

        ///FUN��ES
        void render();//Desenha o mapa na tela;;;;
        
        //PAREDE
        bool eParede(int x, int y); //Detecta paredes na posi��o x/y
        void fazerParede(int x, int y); //Torna x/y numa parede
        void cavar(int x, int y); // Tira a parede de x/y
        bool podeAndar(int x, int y); //Verifica se x/y � caminh�vel
        
        //FOV
        bool eVisivel(int x, int y); // verifica se x/y est� visivel
        void tornarVisivel(int x, int y); // Torna x/y visivel
        void tornarNaoVisivel(int x, int y); //Deixa x/y nao visivel

        //EXPLORA��O
        bool eExplorado(int x, int y);
        void tornarExplorado(int x, int y);

    protected:

    private:
};

#endif // MAPA_H
