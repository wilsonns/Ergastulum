#ifndef AI_H
#define AI_H
#include<main.h>

class Entidade;
class Engine;

class AI
{
    public:
        AI();
        virtual ~AI();

        virtual void atualizar(Entidade *owner)=0;

    protected:

    private:
};


class aiJogador : public AI
{
    public:
        void atualizar(Entidade *owner);

    protected:
        bool moverOuAtacar(Entidade *owner, int xalvo, int yalvo);
};

class aiMonstro : public AI
{
    public:
        int z =0;
        void atualizar(Entidade *owner);
        
    protected:
        bool moverOuAtacar(Entidade *owner,int xalvo, int yalvo);

};
#endif // AI_H

