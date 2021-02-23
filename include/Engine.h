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
    std::vector<Entidade*> entidades;//cria um vector de entidades livres no mapa(inimigos, itens)
    Entidade *jogador;//cria um pointer para o jogador
    LOG *log;//cria o log externo para debug
    GUI *gui;//Cria a interface do jogo
    TCOD_key_t ultimoBotao;
   
    bool rodando; //o jogo est� rodando?
    bool debug; // o jogo esta no modo debug?
    bool mostrarPath; //mostrar caminhos de cada entidade
    
    
    Engine(int largura, int altura); //ctor
    virtual ~Engine();//dtor/

    int random(int minimo, int maximo, int bonus); // retorna um valor inteiro entre minimo e maximo + o bonus

    void mandarParaOInicio(Entidade* entidade);

    bool vetorContem(std::vector<Entidade> localvec, Entidade entidade);

    void atualizar(); //chama todas as fun��es de atualizar
    void render(); //chama todas as fun��es de render

protected:

private:
};

extern Engine engine; //Avisa o compilador que em algum dos arquivos .cpp tem a declara��o desse objeto;

#endif // ENGINE_H
