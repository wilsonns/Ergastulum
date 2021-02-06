#ifndef DESTRUTIVEL_H
#define DESTRUTIVEL_H
#include <main.h>

class Destrutivel
{
    public:
        float hpMax;
        float hp;
        float defesa;
        const char *nomeCadaver;

        Destrutivel(float hpMax, float defesa, const char *nomeCadaver);
        inline bool morreu()
        {
            if(hp<=0)
            {
                return true;
            }
            return false;
        }

        float tomarDano(Entidade *owner, float dano);

        virtual void morrer(Entidade *owner);

        virtual ~Destrutivel();

    protected:

    private:
};

class destrutivelMonstro : public Destrutivel
{
    public:
        destrutivelMonstro(float hpMax, float defesa, const char *nomeCadaver);
        void morrer(Entidade *owner);
};

class destrutivelJogador : public Destrutivel
{
    public:
        destrutivelJogador(float hpMax, float defesa, const char *nomeCadaver);
        void morrer(Entidade *owner);
};

#endif // DESTRUTIVEL_H
