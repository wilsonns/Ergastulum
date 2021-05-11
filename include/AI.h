#ifndef AI_H
#define AI_H
#include<main.h>

class ObjetoMapa;

class AI
{
    public:
        Entidade* self;//Um ponteiro para si mesmo
        Entidade* alvo;//o alvo do bicho no momento, podendo ser uma entidade, um objeto...
        int pa; //pontos de ação utilizados para agir, vou decidir se são baseados em destreza, agilidade ou nos dois
        AI();//CTOR
        virtual ~AI();//DTOR
        virtual void atualizar();//Função virtual para atualizar a IA da entidade
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
        bool moverOuAtacar(int xalvo, int yalvo);//Retorna true se o jogador se mover, falso se não se mover
        Item* escolherDoInventario(Container*container, bool inventarioDoJogador = false);//Desenha a janela do inventario e permite o jogador escolher o item
        Entidade* mirar(int alcance);
};


class aiMonstro : public AI
{
    public:
        aiMonstro(Entidade *self, int inteligencia = 0);//ctor
        void atualizar();
        
    protected:
        void moverOuAtacar();//retorna true se a entidade se mover, falso se não

};
#endif // AI_H

