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
        TURNO_NOVO,
        TURNO_INIMIGO,
        VITORIA,
        DERROTA
    }statusJogo;//O status do jogo

    int largura, altura; //Largura e altura da tela

    Mapa *mapa;//cria o mapa
    Pathfinding* pathMapa;//cria o mapa de pathfinding compartilhado por todas as entidades que se movem
    TCODList<Entidade*> entidades;//cria uma TCODList de entidades livres no mapa(inimigos, itens)
    Entidade *jogador;//cria um pointer para o jogador
    Entidade* fim;//cria um pointer para 
    LOG *log;//cria o log externo para debug
    GUI *gui;//Cria a interface do jogo
    TCOD_key_t ultimoBotao;
    TCOD_mouse_t mouse;
    std::vector<TCODBsp*> folhas;


    bool rodando; //o jogo está rodando?
    bool debug; // o jogo esta no modo debug?
    bool mostrarPath; //mostrar caminhos de cada entidade
    
    
    Engine(int largura, int altura); //ctor
    virtual ~Engine();//dtor/

    int random(int minimo, int maximo, int bonus); // retorna um valor inteiro entre minimo e maximo + o bonus
    int randomf(float minimo, float maximo, float bonus);

    void mandarParaOInicio(Entidade* entidade);

    void atualizar(); //chama todas as funções de atualizar
    void render(); //chama todas as funções de render

protected:

private:
};

extern Engine engine; //Avisa o compilador que em algum dos arquivos .cpp tem a declaração desse objeto;

#endif // ENGINE_H
