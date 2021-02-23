#ifndef AI_H
#define AI_H
#include<main.h>

enum Prioridade
{
    PRORIDADE_NULA = 0,
    PRIORIDADE_BAIXA = 50,
    PRIORIDADE_NROMAL = 100,
    PRIORIDADE_ALTA = 200,
    PRIORIDADE_MAXIMA = 400
};

class Entidade;
class Engine;

class AI
{
    public:

        float velocidade;//A proporção em que a barraTurno dessa entidade se preenche
        float barraTurno;//Se for 1 ou mais, a entidade pode agir, se não, pula o turno
        Entidade* alvo;
        AI();//CTOR
        virtual ~AI();//DTOR
        virtual void atualizar(Entidade *self)=0;//Função virtual para atualizar a IA da entidade
        
        float condicaoFisica(Entidade* self);//retorna um numero de 0 a 1 baseado na condição fisica da entidade 0 e morto, <1 é machucado, 1 é plena saude
        float forcaPercebida(Entidade* self);
        float perigoPercebido(Entidade* self);
        
        std::vector<Entidade*> entidadesProximas;
        
        int inteligencia = 1;

    protected:

    private:
};


class aiJogador : public AI
{
    public:
        aiJogador(float velocidade);//ctor
        void atualizar(Entidade *self);
        void botaoAcao(Entidade* self, int ascii);

    protected:
        bool moverOuAtacar(Entidade* self, int xalvo, int yalvo);//Retorna true se o jogador se mover, falso se não se mover
        Entidade* escolherDoInventario(Entidade* self);//Desenha a janela do inventario e permite o jogador escolher o item
};

class aiMonstro : public AI
{
    public:
        int ganancia;//A vontade da entidade de adquirir mais bens
        int poderPercebido;//A quantidade de poder que a entidade acredita que tem
        aiMonstro(float velocidade);//ctor
        void atualizar(Entidade* self);
        void acharAlvo(Entidade* self);
        
    protected:
        void moverOuAtacar(Entidade *self,Entidade *alvo);//retorna true se a entidade se mover, falso se não

};
#endif // AI_H

