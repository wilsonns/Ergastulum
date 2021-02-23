#ifndef DESTRUTIVEL_H
#define DESTRUTIVEL_H
#include <main.h>

class Destrutivel
{
    public:
        int hpMax;//maximo de pontos de vida
        int hp;//pontos de vida atual
        
        /// Atributos
        int vigor; //A resistencia a doenças e a saúde geral do personagem
        int resistencia;//A quantidade de dano que o personagem subtrai do dano final
        int resistenciaBase; //
        int agilidade; //A capacidade de esquivar de um golpe
        int agilidadeBase;//
        
        const char *nomeCadaver;//o nome que a entidade terá quando morrer

        Destrutivel(int vigor, int resistencia, int agilidade, const char* nomeCadaver);//ctor
        inline bool morreu()
        {
            if(hp<=0)
            {
                return true;
            }
            return false;
        }//Retorna verdadeiro se tiver morrido, falso se não

        int tomarDano(Entidade *self, int dano);//subtrai o dano sofrido dos pontos de vida atuais e retorna a quantidade de dano que foi causada

        int curar(int valor);//recupera pontos de vida da entidade e retorna a quantidade de pvs curados

        virtual void morrer(Entidade *self);//Função virtual que mata a entidade, tirando-a do vetor entidades e enfiando-a no vetor mortos

        virtual ~Destrutivel();//dtor

    protected:

    private:
};

class destrutivelMonstro : public Destrutivel
{
    public:
        destrutivelMonstro(int vigor, int resistencia, int agilidade, const char* nomeCadaver);//ctor
        void morrer(Entidade *self);
};

class destrutivelJogador : public Destrutivel
{
    public:
        destrutivelJogador(int vigor, int resistencia, int agilidade, const char* nomeCadaver);//ctor
        void morrer(Entidade *self);
};

#endif // DESTRUTIVEL_H
