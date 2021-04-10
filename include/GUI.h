#ifndef GUI_H
#define GUI_H

#include <main.h>

struct Mensagem
{
    std::string texto;
    TCODColor cor;
    Mensagem(std::string texto, const TCODColor& cor)
    {
        this->cor = cor;
        this->texto = texto;
    }
    ~Mensagem() 
    {
    }
};

class GUI
{
    public:
        GUI();//ctor
        virtual ~GUI();//dtor

        static const int ALTURA_PAINEL = 7;
        static const int LARGURA_BARRA = 20;

        static const int X_MENSAGEM = LARGURA_BARRA+2;
        static const int ALTURA_PAINEL_MSG = ALTURA_PAINEL - 1;

        void render();//desenhar a interface na tela

        //MENSAGENS
        void mensagem(const TCODColor& cor, std::string texto, ...);


    protected:
        TCODConsole* con;
        std::vector<Mensagem*> log;
        void renderMouse();


        void renderBarra(int x, int y, int largura, int valor, int valormax, const TCODColor& corBarra, const TCODColor& corFundo);

    private:
};

#endif // GUI_H
