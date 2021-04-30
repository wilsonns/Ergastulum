#ifndef AI_H
#define AI_H
#include<main.h>

class AI
{
    public:
        Entidade* self;
        Entidade* alvo;
        int pa; //pontos de a��o utilizados para agir, vou decidir se s�o baseados em destreza, agilidade ou nos dois
        AI();//CTOR
        virtual ~AI();//DTOR
        virtual void atualizar();//Fun��o virtual para atualizar a IA da entidade
        float condicaoFisica();
};


class aiJogador : public AI
{
    public:
        aiJogador(Entidade* self);//ctor
        void atualizar();
        void botaoAcao(int ascii);
        void mostrarPersonagem();

    protected:
        bool moverOuAtacar(int xalvo, int yalvo);//Retorna true se o jogador se mover, falso se n�o se mover
        Item* escolherDoInventario(Container*container, bool inventarioDoJogador = false);//Desenha a janela do inventario e permite o jogador escolher o item
};

class aiMonstro : public AI
{
    public:
        aiMonstro(Entidade *self, int inteligencia = 0);//ctor
        void atualizar();
        
    protected:
        void moverOuAtacar();//retorna true se a entidade se mover, falso se n�o

};
#endif // AI_H

