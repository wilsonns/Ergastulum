#ifndef MAPA_H
#define MAPA_H

#include "main.h"

struct Tile
{
    bool passavel;//as entidades podem passar por aqui?
    bool explorado = false;//o jogador ja explorou aqui?
    
};

struct Sala
{
    int x, y, altura, largura, xcentro, ycentro;
    Sala(int x, int y, int largura, int altura)
    {
        this->x = x;
        this->y = y;
        this->largura = largura;
        this->altura = altura;
        xcentro = ((largura - x) / 2) + x;
        ycentro = ((altura - y) / 2) + y;
    }
};


#define TAM_MAX 10
#define TAM_MIN 5
#define ITEM_MAX 2
#define MON_MAX 4
class BSPListener :public ITCODBspCallback
{
private:
    Mapa& mapa;
    int nSala;
    int ultx, ulty;
public:
    BSPListener(Mapa& mapa);

    bool visitNode(TCODBsp* node, void* userData);
 };
class Mapa
{
    public:

        int altura, largura;//altura e altura do mapa de jogo
        Mapa(int largura, int altura);//ctor
        virtual ~Mapa();//dtor

        ///FUNÇÕES
        void render();//Desenha o mapa na tela;;;;
        
        //PAREDE
        bool eParede(int x, int y); //Detecta paredes na posição x/y
        void fazerParede(int x, int y); //Torna x/y numa parede
        void cavar(int x1, int x2, int y1, int y2); // Tira a parede de x/y
        bool podeAndar(int x, int y); //Verifica se x/y é caminhável
        //FOV
        bool estaNoFOV(int x, int y)const; // verifica se x/y está visivel
        void computarFOV();

        //EXPLORAÇÃO
        bool foiExplorado(int x, int y)const;//x/y já foi explorado? se sim, retorna verdadeiro, se não, falso

        //CRIAÇÃO DE DUNGEON
        std::vector<Sala*> dungeon;
        void criarSala(bool primeira, int x1, int x2, int y1, int y2);//Cria uma sala

        //ADCIONAR ENTIDADES
        void adcmonstro(int x, int y);//adciona um monstro ao mapa
        void adcionarItem(int x, int y, int simbolo, int tipo, const char* nome, int valor, const TCODColor& cor);//adciona um item(atualmente, uma poção de cura, o único item nessa porra) na posição x/y

    protected:
        Tile* tiles;//array de Tiles que contém as informações do mapa de jogo
        TCODMap* mapa;
        friend class BspListener;
    private:
};

#endif // MAPA_H
