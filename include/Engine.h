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



    Mapa *mapa;//cria o mapa
    Pathfinding* pathMapa;//cria o mapa de pathfinding compartilhado por todas as entidades que se movem
    std::vector<Entidade*> entidades;//cria o vetor de entidades livres no mapa(inimigos, itens)
    std::vector<Entidade*> mortos;//cria o vetor de entidades mortas
    Entidade *jogador;//cria um pointer para o jogador
    LOG *log;//cria o log externo para debug
    GUI *gui;//Cria a interface do jogo
    bool rodando; //o jogo está rodando?
    bool debug; // o jogo esta no modo debug?
    bool mostrarPath; //mostrar caminhos de cada entidade
    Engine(); //ctor
    virtual ~Engine();//dtor/

    void adcmonstro(int x, int y);//adciona um monstro ao mapa

    int random(int minimo, int maximo, int bonus); // retorna um valor inteiro entre minimo e maximo + o bonus

    void atualizar(); //chama todas as funções de atualizar
    void render(); //chama todas as funções de render

protected:

private:
};

extern Engine engine; //Avisa o compilador que em algum dos arquivos .cpp tem a declaração desse objeto;

#endif // ENGINE_H
