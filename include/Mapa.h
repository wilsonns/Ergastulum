#ifndef MAPA_H
#define MAPA_H

#include "main.h"

struct Tile
{
    bool visivel;//o jogador pode enxergar o que tem aqui?
    bool passavel;//as entidades podem passar por aqui?
    bool explorado;//o jogador ja explorou aqui?
    int tipo;//não utilizado ainda
    
};

class Mapa
{
    public:
        int altura, largura;//altura e altura do mapa de jogo
        Tile *tiles;//array de Tiles que contém as informações do mapa de jogo
        Mapa(int largura, int altura);//ctor
        virtual ~Mapa();//dtor

        ///FUNÇÕES
        void render();//Desenha o mapa na tela;;;;
        
        //PAREDE
        bool eParede(int x, int y); //Detecta paredes na posição x/y
        void fazerParede(int x, int y); //Torna x/y numa parede
        void cavar(int x, int y); // Tira a parede de x/y
        bool podeAndar(int x, int y); //Verifica se x/y é caminhável
        
        //FOV
        bool eVisivel(int x, int y); // verifica se x/y está visivel
        void tornarVisivel(int x, int y); // Torna x/y visivel
        void tornarNaoVisivel(int x, int y); //Deixa x/y nao visivel

        //EXPLORAÇÃO
        bool eExplorado(int x, int y);//x/y já foi explorado? se sim, retorna verdadeiro, se não, falso
        void tornarExplorado(int x, int y);//Torna x/y explorado

        //ADCIONAR ITEMS
        void adcionarItem(int x, int y);//adciona um item(atualmente, uma poção de cura, o único item nessa porra) na posição x/y

    protected:

    private:
};

#endif // MAPA_H
