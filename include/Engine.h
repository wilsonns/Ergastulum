#ifndef ENGINE_H
#define ENGINE_H

#include <main.h>

class Engine
{
public:
    enum StatusJogo
    {
        INICIO,
        PARADO,
        NOVO_TURNO,
        VITORIA,
        DERROTA
    };
    Mapa *mapa;
    
    Pathfinding* pathMapa;
    std::vector<Entidade*> entidades;
    std::vector<Entidade*> mortos;
    Entidade *jogador;
    LOG *log;
    GUI *gui;
    bool rodando;
    bool debug;
    bool mostrarPath;
    Engine();
    virtual ~Engine();

    void adcmonstro(int x, int y);

    int random(int minimo, int maximo, int bonus);

    void atualizar();
    void render();

protected:

private:
};

extern Engine engine;

#endif // ENGINE_H
