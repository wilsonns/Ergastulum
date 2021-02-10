#ifndef AI_H
#define AI_H
#include<main.h>

class Entidade;
class Engine;

class AI
{
    public:

        float velocidade;//A propor��o em que a barraTurno dessa entidade se preenche
        float barraTurno;//Se for 1 ou mais, a entidade pode agir, se n�o, pula o turno

        AI();//CTOR
        virtual ~AI();//DTOR
        virtual void atualizar(Entidade *owner)=0;//Fun��o virtual para atualizar a IA da entidade

    protected:

    private:
};


class aiJogador : public AI
{
    public:
        aiJogador(float velocidade);//ctor
        void atualizar(Entidade *owner);

    protected:
        bool moverOuAtacar(Entidade* owner, int xalvo, int yalvo);//Retorna true se o jogador se mover, falso se n�o se mover
        Entidade* escolherDoInventario(Entidade* owner);//Desenha a janela do inventario e permite o jogador escolher o item
};

class aiMonstro : public AI
{
    public:
        aiMonstro(float velocidade);//ctor
        void atualizar(Entidade *owner);
        
    protected:
        bool moverOuAtacar(Entidade *owner,Entidade *alvo);//retorna true se a entidade se mover, falso se n�o

};
#endif // AI_H

