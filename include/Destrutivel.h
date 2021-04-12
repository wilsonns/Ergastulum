#ifndef DESTRUTIVEL_H
#define DESTRUTIVEL_H
#include <main.h>

class Destrutivel
{
    public:
        Entidade* self;

        int hpMax;//maximo de pontos de vida
        int hp;//pontos de vida atual
        
        /// Atributos
        int vigor; //A resistencia a doen�as e a sa�de geral do personagem
        int resistencia;//A quantidade de dano que o personagem subtrai do dano final
        int resistenciaBase; //
        int agilidade; //A capacidade de esquivar de um golpe
        int agilidadeBase;//
        
        std::string nomeCadaver;//o nome que a entidade ter� quando morrer

        Destrutivel(Entidade *self,int vigor=1, int resistencia=1, int agilidade=1, std::string nomeCadaver = "Cadaver");//ctor
        inline bool morreu()
        {
            if(hp<=0)
            {
                return true;
            }
            return false;
        }//Retorna verdadeiro se tiver morrido, falso se n�o

        int tomarDano(int dano);//subtrai o dano sofrido dos pontos de vida atuais e retorna a quantidade de dano que foi causada

        int curar(int valor);//recupera pontos de vida da entidade e retorna a quantidade de pvs curados

        virtual void morrer();//Fun��o virtual que mata a entidade, tirando-a do vetor entidades e enfiando-a no vetor mortos

        virtual ~Destrutivel();//dtor

    protected:

    private:
};

class destrutivelMonstro : public Destrutivel
{
    public:
        destrutivelMonstro(Entidade *self, int vigor, int resistencia, int agilidade, std::string nomeCadaver);//ctor
        void morrer();
};

class destrutivelJogador : public Destrutivel
{
    public:
        destrutivelJogador(Entidade* self, int vigor, int resistencia, int agilidade, std::string nomeCadaver);//ctor
        void morrer();
};

class destrutivelTerreno : public Destrutivel
{
public:
    destrutivelTerreno(int resistencia);//ctor
    void destruir(Tile* self);
};
#endif // DESTRUTIVEL_H
