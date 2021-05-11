#ifndef MAPA_H
#define MAPA_H

#include "main.h"
#include "Container.h"
#include "Destrutivel.h"

class Container;
class DestrutivelTerreno;

struct Tile
{
    Tile();
    Tile(int simbolo, TCODColor cor);
    ~Tile();

    DestrutivelTerreno* destrutivel;
    
    int simbolo;
    TCODColor cor;
        
    bool passavel = false;//as entidades podem passar por aqui?
    bool explorado = false;//o jogador ja explorou aqui?
    bool visivel = false;//o jogador pode ver aqui?
    
    Entidade* ocupante = NULL;//se ha uma entidade ocupante aqui atualmente
    Container* itens;
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


#define TAM_MAX 5
#define TAM_MIN 2
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
    json j;
    int altura, largura;//altura e altura do mapa de jogo
    Mapa(int largura, int altura);//ctor
    virtual ~Mapa();//dtor


    std::vector<std::string> monstros;

    ///FUNÇÕES
    void render();//Desenha o mapa na tela;;;;

    //PAREDE
    bool eParede(int x, int y); //Detecta paredes na posição x/y
    void fazerParede(int x, int y); //Torna x/y numa parede
    void cavar(int x1, int x2, int y1, int y2); // Tira a parede de x/y
    void cavar(Tile* tile);//tira a parede num tile especifico
    bool podeAndar(int x, int y); //Verifica se x/y é caminhável
    bool temEntidade(int x, int y);//Busca se há entidades em x/y
    bool temEntidade(int x, int y, Entidade* entidade);//busca se uma entidade especifica está em x/y
    Tile* getTile(int x, int y);//pega a Tile na posição x/y
    //FOV
    bool estaNoFOV(int x, int y)const; // verifica se x/y está visivel
    
    void tornarVisivel(int x, int y);//torna x/y visivel
    void tornarNaoVisivel(int x, int y);//torna x/y não visivel
    void tornarExplorado(int x, int y);//torna x/y explorado

    //EXPLORAÇÃO
    bool eExplorado(int x, int y);//x/y já foi explorado? se sim, retorna verdadeiro, se não, falso
    bool eVisivel(int x, int y);

    //CRIAÇÃO DE DUNGEON
    std::vector<Sala*> dungeon;
    void criarSala(bool primeira, int x1, int x2, int y1, int y2);//Cria uma sala

    //ADCIONAR ENTIDADES
    void adcmonstro(int x, int y);//adciona um monstro ao mapa
    
    /*
    adciona item em uma coordenada no mapa
    */
    void adcionarItem(int x, int y, int simbolo, 
        std::string nome, std::string tipo, std::string descricao, 
        int valor, const TCODColor& cor, int peso);//adciona um item(atualmente, uma poção de cura, o único item nessa porra) na posição x/y
    
    void adcionarItem(Entidade* portador, int simbolo, std::string nome, int valor, const TCODColor& cor);//adciona um item direto no inventario de uma entidade
    void mover(int x, int y, Entidade* ocupante);

protected:
    //Tile* tiles;//array de Tiles que contém as informações do mapa de jogo
    std::vector<Tile*> tiles;
    TCODMap* mapa;
    friend class BspListener;
private:
};

#endif // MAPA_H
