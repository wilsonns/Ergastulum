#ifndef DESTRUTIVEL_H
#define DESTRUTIVEL_H
#include <main.h>

class Destrutivel
{
    public:
        float hpMax;//maximo de pontos de vida
        float hp;//pontos de vida atual
        float defesa;//a quantidade de dano que a entidade consegue tankar
        const char *nomeCadaver;//o nome que a entidade terá quando morrer

        Destrutivel(float hpMax, float defesa, const char *nomeCadaver);//ctor
        inline bool morreu()
        {
            if(hp<=0)
            {
                return true;
            }
            return false;
        }//Retorna verdadeiro se tiver morrido, falso se não

        float tomarDano(Entidade *owner, float dano);//subtrai o dano sofrido dos pontos de vida atuais e retorna a quantidade de dano que foi causada

        float curar(float valor);//recupera pontos de vida da entidade e retorna a quantidade de pvs curados

        virtual void morrer(Entidade *owner);//Função virtual que mata a entidade, tirando-a do vetor entidades e enfiando-a no vetor mortos

        virtual ~Destrutivel();//dtor

    protected:

    private:
};

class destrutivelMonstro : public Destrutivel
{
    public:
        destrutivelMonstro(float hpMax, float defesa, const char *nomeCadaver);//ctor
        void morrer(Entidade *owner);
};

class destrutivelJogador : public Destrutivel
{
    public:
        destrutivelJogador(float hpMax, float defesa, const char* nomeCadaver);//ctor
        void morrer(Entidade *owner);
};

#endif // DESTRUTIVEL_H
